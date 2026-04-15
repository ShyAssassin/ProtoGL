message(STATUS "Configuring glad gl:core=4.1")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake)
set(GLAD_SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/glad/")
glad_add_library(glad_gl_core_41 REPRODUCIBLE API gl:core=4.1)

message(STATUS "Configuring glfw")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
set(GLFW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)


set_target_properties(glfw PROPERTIES FOLDER "vendor/")
set_target_properties(glad_gl_core_41 PROPERTIES FOLDER "vendor/")
