#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

#include "event.h"
#include "backend.h"

struct NativeWindow {
    virtual ~NativeWindow() = default;

    virtual void show() = 0;
    virtual void focus() = 0;
    virtual void shutdown() = 0;
    virtual void swapBuffers() = 0;
    virtual bool isFocused() const = 0;
    virtual void lockCursor(bool lock) = 0;
    virtual std::vector<WindowEvent> poll() = 0;
    virtual std::string getClipboard() const = 0;
    virtual void setResizable(bool resizable) = 0;
    virtual void setCursorVisible(bool visible) = 0;
    virtual void setTitle(const std::string& title) = 0;
    virtual void setClipboard(const std::string& text) = 0;
    virtual void resize(uint32_t width, uint32_t height) = 0;
    virtual std::pair<uint32_t, uint32_t> getSize() const = 0;
    virtual void setCursorPosition(uint32_t x, uint32_t y) = 0;
    virtual std::pair<float, float> getContentScale() const = 0;
    virtual std::pair<uint32_t, uint32_t> getCursorPosition() const = 0;
};

struct KeyHash {
    std::size_t operator()(Key k) const noexcept {
        return std::hash<uint32_t>{}(static_cast<uint32_t>(k));
    }
};

class Window {
public:
    ~Window();
    Window(Backend backend, const std::string& title, uint32_t width, uint32_t height);

    Window(const Window&) = delete;
    Window(Window&&) noexcept = default;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) noexcept = default;

    void show();
    void close();
    void swapBuffers();
    void requestFocus();
    std::vector<WindowEvent> poll();
    void captureCursor(bool capture);
    void rename(const std::string& title);
    void moveCursor(uint32_t x, uint32_t y);
    void resize(uint32_t width, uint32_t height);

    [[nodiscard]]
    bool focused() const { return m_focused; }

    [[nodiscard]]
    uint32_t width() const { return m_width; }

    [[nodiscard]]
    float dpi() const { return m_scale.first; }

    [[nodiscard]]
    NativeWindow& native() { return *m_window; }

    [[nodiscard]]
    const NativeWindow& native() const { return *m_window; }

    [[nodiscard]]
    uint32_t height() const { return m_height; }

    [[nodiscard]]
    const std::string& title() const { return m_title; }

    [[nodiscard]]
    bool shouldClose() const { return m_closeRequested; }

    [[nodiscard]]
    bool cursorCaptured() const { return m_captureCursor; }

    [[nodiscard]]
    uint32_t framebufferWidth() const { return m_fbWidth; }

    [[nodiscard]]
    uint32_t framebufferHeight() const { return m_fbHeight; }

    [[nodiscard]]
    std::pair<double, double> mouseDelta() const { return m_mouseDelta; }

    [[nodiscard]]
    bool keyPressed(Key key) const { return m_activeKeys.contains(key); }

    [[nodiscard]]
    std::pair<uint32_t, uint32_t> size() const { return { m_width, m_height }; }

    [[nodiscard]]
    std::pair<uint32_t, uint32_t> framebufferSize() const { return { m_fbWidth, m_fbHeight }; }

    [[nodiscard]]
    float aspectRatio() const { return static_cast<float>(m_width) / static_cast<float>(m_height); }
private:
    std::unique_ptr<NativeWindow> m_window;

    std::string m_title;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
    bool m_focused = false;
    uint32_t m_fbWidth = 0;
    uint32_t m_fbHeight = 0;
    bool m_captureCursor = false;
    bool m_closeRequested = false;
    std::unordered_set<Key, KeyHash> m_activeKeys;
    std::pair<float, float> m_scale = { 1.0f, 1.0f };
    std::pair<double, double> m_mouseDelta = { 0.0, 0.0 };
    std::pair<double, double> m_mousePosition = { 0.0, 0.0 };
};
