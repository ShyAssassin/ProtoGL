#pragma once

#ifdef _WIN32
	#ifdef _WIN64
        #define PLATFORM_WINDOWS
        #define PLATFORM "Windows x64"
	#else
		#define PLATFORM_WINDOWS
        #define PLATFORM "Windows x86"
	#endif
#elif defined(__APPLE__) && defined(__MACH__)
	#include <TargetConditionals.h>
	// TARGET_OS_MAC exists on all the platforms
	// so we must check all of them in this order to determine the platform.
	#if TARGET_OS_SIMULATOR
        #define PLATFORM_IOS_SIMULATOR
        #define PLATFORM "IOS Simulator"
	#elif TARGET_OS_MACCATALYST
        #define PLATFORM_IPADOS
        #define PLATFORM "iPadOS"
	#elif TARGET_OS_IPHONE
        #define PLATFORM_IOS
        #define PLATFORM "IOS"
	#elif TARGET_OS_MAC
        #define PLATFORM_MACOS
        #define PLATFORM "MacOS"
	#else // tvOS, watchOS, etc...
		#error "Unknown Apple platform!"
	#endif
#elif defined(__linux__)
    #if defined(__ANDROID__)
        #define PLATFORM_ANDROID
        #define PLATFORM "Android"
    #else
        #define PLATFORM_LINUX
        #define PLATFORM "Linux"
    #endif
#else
	#error "Unknown platform!"
#endif

#if defined(_M_ARM64) || defined(__aarch64__)
    #define ARCH_ARM64
    #define ARCH "ARM64"
#elif defined(_M_ARM) || defined(__arm__) || defined(__arm)
    #define ARCH_ARM
    #define ARCH "ARM"
#elif defined(_M_IX86) || defined(__i386__) || defined(__i386) || defined(i386)
    #define ARCH_X86
    #define ARCH "x86"
#elif defined(_M_X64) || defined(__x86_64__) || defined(__x86_64) || defined(__amd64__) || defined(__amd64)
    #define ARCH_X86_64
    #define ARCH "x86_64"
#else
    #define ARCH_UNKNOWN
    #define ARCH "Unknown"
#endif

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
    #if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define ENDIAN_BIG
        #define ENDIAN "Big Endian"
    #elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define ENDIAN_LITTLE
        #define ENDIAN "Little Endian"
    #else
        #define ENDIAN_UNKNOWN
        #define ENDIAN "Unknown Endian"
        #warning "Could not determine endianness"
    #endif
#elif defined(_WIN32)
    #define ENDIAN_LITTLE
    #define ENDIAN "Little Endian"
#else
    #define ENDIAN_UNKNOWN
    #define ENDIAN "Unknown Endian"
    #warning "Could not determine endianness"
#endif

#if defined(_WIN64) || defined(__LP64__) || defined(_M_X64) || defined(__x86_64__) || defined(__aarch64__)
    #define POINTER_SIZE 8
    #define POINTER_SIZE_STR "64-bit"
#else
    #define POINTER_SIZE 4
    #define POINTER_SIZE_STR "32-bit"
#endif
