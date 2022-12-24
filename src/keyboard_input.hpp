#pragma once

#include <cstdint>
#include <string>

namespace vkBasalt
{
    uint32_t convertToKeySym(const std::string& key);
    uint32_t convertToKeySym(uint32_t winKeyCode);
    bool     isKeyPressed(uint32_t ks);

    struct MouseData
    {
        int  root_x_return       = 0;
        int  root_y_return       = 0;
        int  win_x_return        = 0;
        int  win_y_return        = 0;
        bool buttonLeftPressed   = false;
        bool buttonMiddlePressed = false;
        bool buttonRightPressed  = false;
        bool button4Pressed      = false;
        bool button5Pressed      = false;
    };
    MouseData getMouseData();
} // namespace vkBasalt
