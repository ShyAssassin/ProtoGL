#include <print>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::print("Failed to initialize GLFW");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "ProtoGL", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::print("Failed to initialize GLAD");
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
