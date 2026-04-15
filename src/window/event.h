#pragma once

#include <cstdint>

enum class Action : uint8_t {
    Pressed,
    Released,
};

enum class Key : uint32_t {
    // Arrow keys
    Left, Right, Up, Down,
    // ASCII keys
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    // Modifier keys
    LShift, RShift, LCtrl, RCtrl, LAlt, RAlt,
    // Function keys
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
    // Numbers
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    // "Action" keys
    Space, Enter, Escape, Tab, Backspace, Insert, Delete, Home, End, PageUp, PageDown,
    // "Operation" keys
    Minus, Equals, LeftBracket, RightBracket, Backslash, Semicolon, Apostrophe, Grave, Comma, Period, Slash,
    // Any key that doesn't have a specific enum yet
    Other,
};

enum class MouseButton : uint32_t {
    Left,
    Right,
    Middle,
    Other,
};

enum class EventType : uint8_t {
    Resize,
    Destroyed,
    FocusLost,
    Minimized,
    Maximized,
    MouseWheel,
    FocusGained,
    KeyboardInput,
    CloseRequested,
    CursorPosition,
    MouseButtonInput,
    FramebufferResize,
    ScaleFactorChanged,
};

struct WindowEvent {
    EventType type;

    union {
        struct {
            Key key;
            Action action;
            uint32_t scancode;
        } keyboard;

        struct {
            Action action;
            MouseButton button;
        } mouseButton;

        struct {
            float scroll_x;
            float scroll_y;
        } mouseWheel;

        struct {
            double mouse_x;
            double mouse_y;
        } cursor;

        struct {
            float scale_x;
            float scale_y;
        } scale;

        struct {
            uint32_t width;
            uint32_t height;
        } resize;

        struct {
            uint32_t width;
            uint32_t height;
        } framebufferResize;
    };
};
