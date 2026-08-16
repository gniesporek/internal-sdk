#pragma once
#include <Windows.h>
#include <string>

class InputManager {
public:

    static bool IsInputBlocked(const std::string& widgetId = "") {
        if (ActivePopup.empty())
            return false;

        if (ActivePopup == widgetId)
            return false;

        return true;
    }

    static std::string KeyToString(int key)
    {
        if (key < 1 || key > 254)
            return "";

        if (key >= 'A' && key <= 'Z') {
            std::string s(1, (char)key);
            s[0] = std::tolower(s[0]);
            return s;
        }

        if (key >= '0' && key <= '9') return std::string(1, (char)key);

        if (key >= VK_F1 && key <= VK_F12)
            return "f" + std::to_string(key - VK_F1 + 1);

        switch (key)
        {
        case VK_LBUTTON: return "mouse 1";
        case VK_RBUTTON: return "mouse 2";
        case VK_MBUTTON: return "mouse 3";
        case VK_XBUTTON1: return "mouse 4";
        case VK_XBUTTON2: return "mouse 5";

        case VK_ESCAPE:   return "escape";
        case VK_SPACE:    return "space";
        case VK_RETURN:   return "enter";
        case VK_BACK:     return "backspace";
        case VK_TAB:      return "tab";
        case VK_SHIFT:    return "shift";
        case VK_CONTROL:  return "control";
        case VK_MENU:     return "alt";
        case VK_CAPITAL:  return "caps lock";

        case VK_INSERT:   return "insert";
        case VK_DELETE:   return "delete";
        case VK_HOME:     return "home";
        case VK_END:      return "end";
        case VK_PRIOR:    return "page up";
        case VK_NEXT:     return "page down";

        case VK_LEFT:     return "left arrow";
        case VK_RIGHT:    return "right arrow";
        case VK_UP:       return "up arrow";
        case VK_DOWN:     return "down arrow";

        case VK_NUMPAD0:  return "numpad 0";
        case VK_NUMPAD1:  return "numpad 1";
        case VK_NUMPAD2:  return "numpad 2";
        case VK_NUMPAD3:  return "numpad 3";
        case VK_NUMPAD4:  return "numpad 4";
        case VK_NUMPAD5:  return "numpad 5";
        case VK_NUMPAD6:  return "numpad 6";
        case VK_NUMPAD7:  return "numpad 7";
        case VK_NUMPAD8:  return "numpad 8";
        case VK_NUMPAD9:  return "numpad 9";
        case VK_DECIMAL:  return "numpad .";
        case VK_ADD:      return "numpad +";
        case VK_SUBTRACT: return "numpad -";
        case VK_MULTIPLY: return "numpad *";
        case VK_DIVIDE:   return "numpad /";

        default:
            return "unknown";
        }
    }
    static int GetPressedKey()
    {
        for (int i = 1; i < 255; i++)
        {
            if (GetAsyncKeyState(i) & 0x8000)
                return i;
        }
        return 0;
    }

    static inline std::string ActivePopup = "";
};