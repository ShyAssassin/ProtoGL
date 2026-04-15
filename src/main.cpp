#include <print>
#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "window/window.h"

int main() {

    Window window(preferredBackend(), "Monarch", 800, 800);

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
        window.swapBuffers();
    }

    return 0;
}
