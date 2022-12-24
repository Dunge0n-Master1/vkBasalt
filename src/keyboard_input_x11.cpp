#include "keyboard_input_x11.hpp"

#include "logger.hpp"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>

#include <memory>
#include <functional>

#include <unistd.h>
#include <cstring>

namespace vkBasalt
{
    uint32_t convertToKeySymX11(const std::string& key)
    {
        // TODO what if X11 isn't loaded?
        uint32_t result = (uint32_t) XStringToKeysym(key.c_str());
        if (!result)
        {
            Logger::err("invalid key");
        }
        return result;
    }

    uint32_t convertToKeySymX11(uint32_t winKeyCode)
    {
        switch (winKeyCode)
        {
            case 0x08: return XK_BackSpace;
            case 0x09: return XK_Tab;
            case 0x0C: return XK_Clear;
            case 0x0D: return XK_Return;
            case 0x10: return XK_Shift_L;
            case 0x11: return XK_Control_L;
            case 0x12: return XK_Alt_L;
            case 0x13: return XK_Pause;
            case 0x14: return XK_Caps_Lock;
            case 0x1B: return XK_Escape;
            case 0x20: return XK_space;
            case 0x21: return XK_Page_Up;
            case 0x22: return XK_Page_Down;
            case 0x23: return XK_End;
            case 0x24: return XK_Begin;
            case 0x25: return XK_Left;
            case 0x26: return XK_Up;
            case 0x27: return XK_Right;
            case 0x28: return XK_Down;
            case 0x29: return XK_Select;
            case 0x2A: return XK_Print;
            case 0x2B: return XK_Execute;
            case 0x2C: return XK_Print;
            case 0x2D: return XK_Insert;
            case 0x2E: return XK_Delete;
            case 0x2F: return XK_Help;
            case 0x30: return XK_0;
            case 0x31: return XK_1;
            case 0x32: return XK_2;
            case 0x33: return XK_3;
            case 0x34: return XK_4;
            case 0x35: return XK_5;
            case 0x36: return XK_6;
            case 0x37: return XK_7;
            case 0x38: return XK_8;
            case 0x39: return XK_9;
            case 0x41: return XK_A;
            case 0x42: return XK_B;
            case 0x43: return XK_C;
            case 0x44: return XK_D;
            case 0x45: return XK_E;
            case 0x46: return XK_F;
            case 0x47: return XK_G;
            case 0x48: return XK_H;
            case 0x49: return XK_I;
            case 0x4A: return XK_J;
            case 0x4B: return XK_K;
            case 0x4C: return XK_L;
            case 0x4D: return XK_M;
            case 0x4E: return XK_N;
            case 0x4F: return XK_O;
            case 0x50: return XK_P;
            case 0x51: return XK_Q;
            case 0x52: return XK_R;
            case 0x53: return XK_S;
            case 0x54: return XK_T;
            case 0x55: return XK_U;
            case 0x56: return XK_V;
            case 0x57: return XK_W;
            case 0x58: return XK_X;
            case 0x59: return XK_Y;
            case 0x5A: return XK_Z;
            case 0x5B: return XK_Super_L;
            case 0x5C: return XK_Super_R;
            case 0x5F: return XF86XK_Sleep;
            case 0x60: return XK_KP_0;
            case 0x61: return XK_KP_1;
            case 0x62: return XK_KP_2;
            case 0x63: return XK_KP_3;
            case 0x64: return XK_KP_4;
            case 0x65: return XK_KP_5;
            case 0x66: return XK_KP_6;
            case 0x67: return XK_KP_7;
            case 0x68: return XK_KP_8;
            case 0x69: return XK_KP_9;
            case 0x6A: return XK_KP_Multiply;
            case 0x6B: return XK_KP_Add;
            case 0x6C: return XK_KP_Separator;
            case 0x6D: return XK_KP_Subtract;
            case 0x6E: return XK_KP_Decimal;
            case 0x6F: return XK_KP_Divide;
            case 0x70: return XK_F1;
            case 0x71: return XK_F2;
            case 0x72: return XK_F3;
            case 0x73: return XK_F4;
            case 0x74: return XK_F5;
            case 0x75: return XK_F6;
            case 0x76: return XK_F7;
            case 0x77: return XK_F8;
            case 0x78: return XK_F9;
            case 0x79: return XK_F10;
            case 0x7A: return XK_F11;
            case 0x7B: return XK_F12;
            case 0x7C: return XK_F13;
            case 0x7D: return XK_F14;
            case 0x7E: return XK_F15;
            case 0x7F: return XK_F16;
            case 0x80: return XK_F17;
            case 0x81: return XK_F18;
            case 0x82: return XK_F19;
            case 0x83: return XK_F20;
            case 0x84: return XK_F21;
            case 0x85: return XK_F22;
            case 0x86: return XK_F23;
            case 0x87: return XK_F24;
            case 0x90: return XK_Num_Lock;
            case 0x91: return XK_Scroll_Lock;
            case 0xA0: return XK_Shift_L;
            case 0xA1: return XK_Shift_R;
            case 0xA2: return XK_Control_L;
            case 0xA3: return XK_Control_R;
            case 0xA4: return XK_Alt_L;
            case 0xA5: return XK_Alt_R;
            case 0xA6: return XF86XK_Back;
            case 0xA7: return XF86XK_Forward;
            case 0xA8: return XF86XK_Refresh;
            case 0xA9: return XF86XK_Stop;
            case 0xAA: return XF86XK_Search;
            case 0xAB: return XF86XK_Favorites;
            case 0xAC: return XF86XK_HomePage;
            case 0xAD: return XF86XK_AudioMute;
            case 0xAE: return XF86XK_AudioLowerVolume;
            case 0xAF: return XF86XK_AudioRaiseVolume;
            case 0xB0: return XF86XK_AudioNext;
            case 0xB1: return XF86XK_AudioPrev;
            case 0xB2: return XF86XK_AudioStop;
            case 0xB3: return XF86XK_AudioPlay;
            case 0xB4: return XF86XK_Mail;
            case 0xB5: return XF86XK_AudioMedia;
            case 0xB6: return XF86XK_Launch0;
            case 0xB7: return XF86XK_Launch1;
            case 0xBA: return XK_semicolon;
            case 0xBB: return XK_plus;
            case 0xBC: return XK_comma;
            case 0xBD: return XK_minus;
            case 0xBE: return XK_period;
            case 0xBF: return XK_slash;
            case 0xC0: return XK_grave;
            case 0xDB: return XK_bracketleft;
            case 0xDC: return XK_backslash;
            case 0xDD: return XK_bracketright;
            case 0xDE: return XK_apostrophe;
            case 0xFB: return XF86XK_ZoomIn;
            case 0xFA: return XF86XK_AudioPlay;
            case 0xFE: return XF86XK_Clear;
            default: return 0;
        }
    }

    bool isKeyPressedX11(uint32_t ks)
    {
        static int usesX11 = -1;

        static std::unique_ptr<Display, std::function<void(Display*)>> display;

        if (usesX11 < 0)
        {
            const char* disVar = getenv("DISPLAY");
            if (!disVar || !std::strcmp(disVar, ""))
            {
                usesX11 = 0;
                Logger::debug("no X11 support");
            }
            else
            {
                display = std::unique_ptr<Display, std::function<void(Display*)>>(XOpenDisplay(disVar), [](Display* d) { XCloseDisplay(d); });
                usesX11 = 1;
                Logger::debug("X11 support");
            }
        }

        if (!usesX11)
            return false;

        char keys_return[32];

        XQueryKeymap(display.get(), keys_return);

        const KeyCode kc2 = XKeysymToKeycode(display.get(), (KeySym) ks);

        return !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
    }

    MouseData getMouseDataX11()
    {
        static int usesX11 = -1;

        static std::unique_ptr<Display, std::function<void(Display*)>> display;

        if (usesX11 < 0)
        {
            const char* disVar = getenv("DISPLAY");
            if (!disVar || !std::strcmp(disVar, ""))
            {
                usesX11 = 0;
                Logger::debug("no X11 support");
            }
            else
            {
                display = std::unique_ptr<Display, std::function<void(Display*)>>(XOpenDisplay(disVar), [](Display* d) { XCloseDisplay(d); });
                usesX11 = 1;
                Logger::debug("X11 support");
            }
        }

        if (!usesX11)
            return MouseData();

        Window       root_return, child_return;
        int          root_x_return, root_y_return, win_x_return, win_y_return;
        unsigned int mask_return;

        XQueryPointer(display.get(),
                      RootWindow(display.get(), XDefaultScreen(display.get())),
                      &root_return,
                      &child_return,
                      &root_x_return,
                      &root_y_return,
                      &win_x_return,
                      &win_y_return,
                      &mask_return);

        return MouseData{root_x_return,
                         root_y_return,
                         win_x_return,
                         win_y_return,
                         bool(mask_return & Button1Mask),
                         bool(mask_return & Button2Mask),
                         bool(mask_return & Button3Mask),
                         bool(mask_return & Button4Mask),
                         bool(mask_return & Button5Mask)};
    }
} // namespace vkBasalt
