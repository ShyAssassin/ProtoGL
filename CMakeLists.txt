cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(ProtoGL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(ProtoGL ${SOURCE_FILES})
target_link_libraries(ProtoGL PRIVATE glm)
target_link_libraries(ProtoGL PRIVATE glfw)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(ProtoGL PRIVATE glad_gl_core_41)

if(MSVC)
    target_compile_options(ProtoGL PRIVATE /W4 /WX)
else()
    target_compile_options(ProtoGL PRIVATE -Wall -Wextra -Fanalyzer -Fpedantic)
endif()

add_custom_command(TARGET ProtoGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${PROJECT_SOURCE_DIR}/src/shader" $<TARGET_FILE_DIR:ProtoGL>/shader
)
