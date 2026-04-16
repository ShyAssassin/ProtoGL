#pragma once

#include <GLFW/glfw3.h>
#include "window/window.h"

class GlfwWindow : public NativeWindow {
public:
    GlfwWindow();
    ~GlfwWindow() override;

    GlfwWindow(const GlfwWindow&) = delete;
    GlfwWindow& operator=(const GlfwWindow&) = delete;

    void show() override;
    void focus() override;
    void shutdown() override;
    void swapBuffers() override;
    bool isFocused() const override;
    void lockCursor(bool lock) override;
    std::vector<WindowEvent> poll() override;
    std::string getClipboard() const override;
    void resize(uint32_t width, uint32_t height) override;
    std::pair<uint32_t, uint32_t> getSize() const override;
    std::pair<float, float> getContentScale() const override;
    std::pair<uint32_t, uint32_t> getCursorPosition() const override;

    void setResizable(bool resizable) override;
    void setCursorVisible(bool visible) override;
    void setTitle(const std::string& title) override;
    void setClipboard(const std::string& text) override;
    void setCursorPosition(uint32_t x, uint32_t y) override;

    GLFWwindow* handle() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
    std::vector<WindowEvent> m_pendingEvents = {};

    static void windowCloseCallback(GLFWwindow* window);
    static void windowFocusCallback(GLFWwindow* window, int focused);
    static void windowMaximizeCallback(GLFWwindow* window, int maximized);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void contentScaleCallback(GLFWwindow* window, float xscale, float yscale);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
