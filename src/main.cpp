#include <print>
#include <iostream>
#include <glad/gl.h>
#include "window/window.h"

#include "gfx/shader.h"

int main() {
    Window window(preferredBackend(), "Monarch", 800, 800);

    Shader shader("shader/tri.glsl");

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    while (!window.shouldClose()) {
        auto events = window.poll();
        for (const auto& event : events) {
            if (event.type == EventType::CloseRequested) {
                window.close();
            }
            if (event.type == EventType::KeyboardInput) {
                if (event.keyboard.key == Key::Escape && event.keyboard.action == Action::Pressed) {
                    window.close();
                }
            }
        }

        glClearColor(0.62f, 0.03f, 0.27f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.swapBuffers();
    }

    return 0;
}
