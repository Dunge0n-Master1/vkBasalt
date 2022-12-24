#pragma once

#include <cstdint>
#include <string>

#include "keyboard_input.hpp"

namespace vkBasalt
{
    uint32_t convertToKeySymX11(const std::string& key);
    uint32_t convertToKeySymX11(uint32_t winKeyCode);
    bool     isKeyPressedX11(uint32_t ks);

    MouseData getMouseDataX11();
} // namespace vkBasalt
