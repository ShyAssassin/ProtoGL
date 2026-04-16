#include "window.h"
#include <stdexcept>
#include "backend/glfw.h"

static std::unique_ptr<NativeWindow> createBackend(Backend backend) {
    switch (backend) {
        case Backend::Glfw: return std::make_unique<GlfwWindow>();
    }
    throw std::runtime_error("unknown window backend");
}

Window::Window(Backend backend, const std::string& title, uint32_t width, uint32_t height)
    : m_window(createBackend(backend)), m_title(title)
{
    m_window->setTitle(title);
    m_window->resize(width, height);
    auto [w, h] = m_window->getSize();

    m_width = w;
    m_height = h;
    m_focused = m_window->isFocused();
    m_scale = m_window->getContentScale();
    m_fbWidth = static_cast<uint32_t>(static_cast<float>(m_width) * m_scale.first);
    m_fbHeight = static_cast<uint32_t>(static_cast<float>(m_height) * m_scale.second);
}

Window::~Window() = default;

void Window::show() {
    m_window->show();
}

std::vector<WindowEvent> Window::poll() {
    m_mouseDelta = { 0.0, 0.0 };
    std::vector<WindowEvent> events;

    for (const auto& event : m_window->poll()) {
        switch (event.type) {
            case EventType::CloseRequested:
                m_closeRequested = true;
                break;
            case EventType::FocusGained:
                m_focused = true;
                break;
            case EventType::FocusLost:
                m_focused = false;
                m_activeKeys.clear();
                captureCursor(false);
                m_mouseDelta = { 0.0, 0.0 };
                break;
            case EventType::KeyboardInput:
                if (event.keyboard.action == Action::Pressed) {
                    m_activeKeys.insert(event.keyboard.key);
                } else {
                    m_activeKeys.erase(event.keyboard.key);
                }
                break;
            case EventType::Resize: {
                m_width = event.resize.width;
                m_height = event.resize.height;
                m_fbWidth = static_cast<uint32_t>(static_cast<float>(m_width) * m_scale.first);
                m_fbHeight = static_cast<uint32_t>(static_cast<float>(m_height) * m_scale.second);

                WindowEvent fb{};
                fb.type = EventType::FramebufferResize;
                fb.framebufferResize = { m_fbWidth, m_fbHeight };
                events.push_back(fb);
                break;
            }
            case EventType::ScaleFactorChanged: {
                m_scale = { event.scale.scale_x, event.scale.scale_y };
                m_fbWidth = static_cast<uint32_t>(static_cast<float>(m_width) * m_scale.first);
                m_fbHeight = static_cast<uint32_t>(static_cast<float>(m_height) * m_scale.second);

                WindowEvent fb{};
                fb.type = EventType::FramebufferResize;
                fb.framebufferResize = { m_fbWidth, m_fbHeight };
                events.push_back(fb);
                break;
            }
            case EventType::CursorPosition: {
                auto newX = event.cursor.mouse_x;
                auto newY = event.cursor.mouse_y;
                if (newX != m_mousePosition.first || newY != m_mousePosition.second) {
                    double dx = newX - m_mousePosition.first;
                    double dy = newY - m_mousePosition.second;

                    if (dx != -m_mouseDelta.first || dy != -m_mouseDelta.second) {
                        m_mouseDelta.first += dx;
                        m_mouseDelta.second += dy;
                    }
                    m_mousePosition = { newX, newY };
                }
                break;
            }
            default:
                break;
        }

        events.push_back(event);
    }

    return events;
}

void Window::resize(uint32_t width, uint32_t height) {
    if (width > 0 && height > 0 && (width != m_width || height != m_height)) {
        m_window->resize(width, height);
    }
}

void Window::moveCursor(uint32_t x, uint32_t y) {
    if (m_focused && m_captureCursor) {
        if (static_cast<double>(x) != m_mousePosition.first ||
            static_cast<double>(y) != m_mousePosition.second) {
            m_window->setCursorPosition(x, y);
            m_mousePosition = { static_cast<double>(x), static_cast<double>(y) };
        }
    }
}

void Window::captureCursor(bool capture) {
    if (m_focused || !capture) {
        m_captureCursor = capture;
        m_window->lockCursor(capture);
    }
}

void Window::rename(const std::string& title) {
    if (m_title != title) {
        m_title = title;
        m_window->setTitle(title);
    }
}

void Window::requestFocus() {
    if (!m_focused) {
        m_window->focus();
    }
}

void Window::close() {
    m_window->shutdown();
    m_activeKeys.clear();
    m_closeRequested = true;
}

void Window::swapBuffers() {
    m_window->swapBuffers();
}
