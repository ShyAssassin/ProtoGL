#pragma once

#include <string>
#include <cstdint>
#include <cstdlib>
#include "core/platform.h"

enum class Backend : uint8_t {
    Glfw,
};

consteval Backend preferredBackend() {
    #if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX) || defined(PLATFORM_MACOS)
        return Backend::Glfw;
    #else
        static_assert(false, "platform has no preferred window backend");
    #endif
}

inline Backend backendFromEnv() {
    const char* env = std::getenv("WINDOW_BACKEND");
    if (!env) return preferredBackend();
    std::string value(env);
    if (value == "glfw") return Backend::Glfw;
    return preferredBackend();
}
