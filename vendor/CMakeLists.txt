message(STATUS "Configuring glad gl:core=4.1")
set(GLAD_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glad")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake)
glad_add_library(glad_gl_core_41 REPRODUCIBLE API gl:core=4.1)

message(STATUS "Configuring glm")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm)

message(STATUS "Configuring glfw")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
set(GLFW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)

# Make the IDE actually navigatable by humans
set_target_properties(glm PROPERTIES FOLDER "vendor/")
set_target_properties(glfw PROPERTIES FOLDER "vendor/")
set_target_properties(glad_gl_core_41 PROPERTIES FOLDER "vendor/")
