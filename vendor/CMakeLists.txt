message(STATUS "Now configuring glad gl:core=4.1...")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake)
set(GLAD_SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/glad/")
glad_add_library(glad_gl_core_41 REPRODUCIBLE API gl:core=4.1)
