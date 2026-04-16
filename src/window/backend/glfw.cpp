#include <glad/gl.h>
#include "glfw.h"

static Key glfwKeyToKey(int key) {
    switch (key) {
        case GLFW_KEY_A: return Key::A; case GLFW_KEY_B: return Key::B; case GLFW_KEY_C: return Key::C;
        case GLFW_KEY_D: return Key::D; case GLFW_KEY_E: return Key::E; case GLFW_KEY_F: return Key::F;
        case GLFW_KEY_G: return Key::G; case GLFW_KEY_H: return Key::H; case GLFW_KEY_I: return Key::I;
        case GLFW_KEY_J: return Key::J; case GLFW_KEY_K: return Key::K; case GLFW_KEY_L: return Key::L;
        case GLFW_KEY_M: return Key::M; case GLFW_KEY_N: return Key::N; case GLFW_KEY_O: return Key::O;
        case GLFW_KEY_P: return Key::P; case GLFW_KEY_Q: return Key::Q; case GLFW_KEY_R: return Key::R;
        case GLFW_KEY_S: return Key::S; case GLFW_KEY_T: return Key::T; case GLFW_KEY_U: return Key::U;
        case GLFW_KEY_V: return Key::V; case GLFW_KEY_W: return Key::W; case GLFW_KEY_X: return Key::X;
        case GLFW_KEY_Y: return Key::Y; case GLFW_KEY_Z: return Key::Z;

        case GLFW_KEY_0: return Key::Num0; case GLFW_KEY_1: return Key::Num1; case GLFW_KEY_2: return Key::Num2;
        case GLFW_KEY_3: return Key::Num3; case GLFW_KEY_4: return Key::Num4; case GLFW_KEY_5: return Key::Num5;
        case GLFW_KEY_6: return Key::Num6; case GLFW_KEY_7: return Key::Num7; case GLFW_KEY_8: return Key::Num8;
        case GLFW_KEY_9: return Key::Num9;

        case GLFW_KEY_F1: return Key::F1; case GLFW_KEY_F2: return Key::F2; case GLFW_KEY_F3: return Key::F3;
        case GLFW_KEY_F4: return Key::F4; case GLFW_KEY_F5: return Key::F5; case GLFW_KEY_F6: return Key::F6;
        case GLFW_KEY_F7: return Key::F7; case GLFW_KEY_F8: return Key::F8; case GLFW_KEY_F9: return Key::F9;
        case GLFW_KEY_F10: return Key::F10; case GLFW_KEY_F11: return Key::F11; case GLFW_KEY_F12: return Key::F12;
        case GLFW_KEY_F13: return Key::F13; case GLFW_KEY_F14: return Key::F14; case GLFW_KEY_F15: return Key::F15;
        case GLFW_KEY_F16: return Key::F16; case GLFW_KEY_F17: return Key::F17; case GLFW_KEY_F18: return Key::F18;
        case GLFW_KEY_F19: return Key::F19; case GLFW_KEY_F20: return Key::F20; case GLFW_KEY_F21: return Key::F21;
        case GLFW_KEY_F22: return Key::F22; case GLFW_KEY_F23: return Key::F23; case GLFW_KEY_F24: return Key::F24;

        case GLFW_KEY_LEFT_SHIFT: return Key::LShift; case GLFW_KEY_RIGHT_SHIFT: return Key::RShift;
        case GLFW_KEY_LEFT_CONTROL: return Key::LCtrl; case GLFW_KEY_RIGHT_CONTROL: return Key::RCtrl;
        case GLFW_KEY_LEFT_ALT: return Key::LAlt; case GLFW_KEY_RIGHT_ALT: return Key::RAlt;

        case GLFW_KEY_LEFT: return Key::Left; case GLFW_KEY_RIGHT: return Key::Right;
        case GLFW_KEY_UP: return Key::Up; case GLFW_KEY_DOWN: return Key::Down;

        case GLFW_KEY_SPACE: return Key::Space; case GLFW_KEY_ENTER: return Key::Enter;
        case GLFW_KEY_ESCAPE: return Key::Escape; case GLFW_KEY_TAB: return Key::Tab;
        case GLFW_KEY_BACKSPACE: return Key::Backspace; case GLFW_KEY_INSERT: return Key::Insert;
        case GLFW_KEY_DELETE: return Key::Delete; case GLFW_KEY_HOME: return Key::Home;
        case GLFW_KEY_END: return Key::End; case GLFW_KEY_PAGE_UP: return Key::PageUp;
        case GLFW_KEY_PAGE_DOWN: return Key::PageDown;

        case GLFW_KEY_MINUS: return Key::Minus; case GLFW_KEY_EQUAL: return Key::Equals;
        case GLFW_KEY_LEFT_BRACKET: return Key::LeftBracket; case GLFW_KEY_RIGHT_BRACKET: return Key::RightBracket;
        case GLFW_KEY_BACKSLASH: return Key::Backslash; case GLFW_KEY_SEMICOLON: return Key::Semicolon;
        case GLFW_KEY_APOSTROPHE: return Key::Apostrophe; case GLFW_KEY_GRAVE_ACCENT: return Key::Grave;
        case GLFW_KEY_COMMA: return Key::Comma; case GLFW_KEY_PERIOD: return Key::Period;
        case GLFW_KEY_SLASH: return Key::Slash;

        default: return Key::Other;
    }
}

static MouseButton glfwMouseButtonToMouseButton(int button) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        default: return MouseButton::Other;
    }
}

static Action glfwActionToAction(int action) {
    switch (action) {
        case GLFW_PRESS: return Action::Pressed;
        case GLFW_REPEAT: return Action::Pressed;
        case GLFW_RELEASE: return Action::Released;
        default: return Action::Released;
    }
}

GlfwWindow::GlfwWindow() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(100, 100, "Monarch", nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetScrollCallback(m_window, scrollCallback);
    glfwSetCursorPosCallback(m_window, cursorPosCallback);
    glfwSetWindowSizeCallback(m_window, windowSizeCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetWindowCloseCallback(m_window, windowCloseCallback);
    glfwSetWindowFocusCallback(m_window, windowFocusCallback);
    glfwSetWindowMaximizeCallback(m_window, windowMaximizeCallback);
    glfwSetWindowContentScaleCallback(m_window, contentScaleCallback);

    glfwMakeContextCurrent(m_window);
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

GlfwWindow::~GlfwWindow() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

void GlfwWindow::show() {
    glfwShowWindow(m_window);
}

void GlfwWindow::focus() {
    glfwFocusWindow(m_window);
}

void GlfwWindow::shutdown() {
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void GlfwWindow::swapBuffers() {
    glfwSwapBuffers(m_window);
}

bool GlfwWindow::isFocused() const {
    return glfwGetWindowAttrib(m_window, GLFW_FOCUSED) != 0;
}

void GlfwWindow::lockCursor(bool lock) {
    glfwSetInputMode(m_window, GLFW_CURSOR, lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

std::vector<WindowEvent> GlfwWindow::poll() {
    glfwPollEvents();
    auto events = std::move(m_pendingEvents);
    m_pendingEvents.clear();
    return events;
}

void GlfwWindow::resize(uint32_t width, uint32_t height) {
    glfwSetWindowSize(m_window, static_cast<int>(width), static_cast<int>(height));
    glfwPollEvents();
}

std::pair<uint32_t, uint32_t> GlfwWindow::getSize() const {
    int w, h;
    glfwGetWindowSize(m_window, &w, &h);
    return { static_cast<uint32_t>(w), static_cast<uint32_t>(h) };
}

std::string GlfwWindow::getClipboard() const {
    const char* text = glfwGetClipboardString(m_window);
    return text ? std::string(text) : std::string{};
}

std::pair<float, float> GlfwWindow::getContentScale() const {
    float x, y;
    glfwGetWindowContentScale(m_window, &x, &y);
    return { x, y };
}

std::pair<uint32_t, uint32_t> GlfwWindow::getCursorPosition() const {
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);
    return { static_cast<uint32_t>(std::max(0.0, x)), static_cast<uint32_t>(std::max(0.0, y)) };
}

void GlfwWindow::setTitle(const std::string& title) {
    glfwSetWindowTitle(m_window, title.c_str());
}

void GlfwWindow::setClipboard(const std::string& text) {
    glfwSetClipboardString(m_window, text.c_str());
}

void GlfwWindow::setResizable(bool resizable) {
    glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
}

void GlfwWindow::setCursorVisible(bool visible) {
    glfwSetInputMode(m_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void GlfwWindow::setCursorPosition(uint32_t x, uint32_t y) {
    glfwSetCursorPos(m_window, static_cast<double>(x), static_cast<double>(y));
}

void GlfwWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int /*mods*/) {
    WindowEvent event = {};
    event.type = EventType::KeyboardInput;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    event.keyboard = { glfwKeyToKey(key), glfwActionToAction(action), static_cast<uint32_t>(scancode) };
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    WindowEvent event = {};
    event.type = EventType::MouseWheel;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    event.mouseWheel = { static_cast<float>(xoffset), static_cast<float>(yoffset) };
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    WindowEvent event = {};
    event.cursor = { xpos, ypos };
    event.type = EventType::CursorPosition;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::mouseButtonCallback(GLFWwindow* window, int button, int action, int /*mods*/) {
    WindowEvent event = {};
    event.type = EventType::MouseButtonInput;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    event.mouseButton = { glfwActionToAction(action), glfwMouseButtonToMouseButton(button) };
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
    WindowEvent event = {};
    event.type = EventType::Resize;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    event.resize = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::windowCloseCallback(GLFWwindow* window) {
    WindowEvent event = {};
    event.type = EventType::CloseRequested;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::windowFocusCallback(GLFWwindow* window, int focused) {
    WindowEvent event = {};
    event.type = focused ? EventType::FocusGained : EventType::FocusLost;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::windowMaximizeCallback(GLFWwindow* window, int maximized) {
    WindowEvent event = {};
    event.type = maximized ? EventType::Maximized : EventType::Minimized;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    self->m_pendingEvents.push_back(event);
}

void GlfwWindow::contentScaleCallback(GLFWwindow* window, float xscale, float yscale) {
    WindowEvent event = {};
    event.scale = { xscale, yscale };
    event.type = EventType::ScaleFactorChanged;
    auto* self = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    self->m_pendingEvents.push_back(event);
}
