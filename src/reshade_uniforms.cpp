#include "reshade_uniforms.hpp"

#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cmath>

#include <algorithm>

#include "logger.hpp"
#include "keyboard_input.hpp"

namespace vkBasalt
{
    void enumerateReshadeUniforms(reshadefx::module module)
    {
        for (auto& uniform : module.uniforms)
        {
            auto source = std::find_if(uniform.annotations.begin(), uniform.annotations.end(), [](const auto& a) {
                              return a.name == "source";
                          })->value.string_data;
            Logger::debug(source);
            Logger::debug("size: " + std::to_string(uniform.size));
            Logger::debug("offset: " + std::to_string(uniform.offset));
        }
    }

    void get_annotation(const reshadefx::uniform_info& uniformInfo, const std::string& name, int& value)
    {
        if (auto annotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [name](const auto& a) { return a.name == name; });
            annotation != uniformInfo.annotations.end())
        {
            value = annotation->type.is_integral() ? annotation->value.as_int[0] : static_cast<int>(annotation->value.as_float[0]);
        }
    }
    void get_annotation(const reshadefx::uniform_info& uniformInfo, const std::string& name, uint& value)
    {
        if (auto annotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [name](const auto& a) { return a.name == name; });
            annotation != uniformInfo.annotations.end())
        {
            value = annotation->type.is_integral() ? annotation->value.as_uint[0] : static_cast<int>(annotation->value.as_float[0]);
        }
    }
    void get_annotation(const reshadefx::uniform_info& uniformInfo, const std::string& name, float& value)
    {
        if (auto annotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [name](const auto& a) { return a.name == name; });
            annotation != uniformInfo.annotations.end())
        {
            value = annotation->type.is_floating_point() ? annotation->value.as_float[0] : static_cast<float>(annotation->value.as_int[0]);
        }
    }
    void get_annotation(const reshadefx::uniform_info& uniformInfo, const std::string& name, std::string& value)
    {
        if (auto annotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [name](const auto& a) { return a.name == name; });
            annotation != uniformInfo.annotations.end())
        {
            value = annotation->value.string_data;
        }
    }

    std::vector<std::shared_ptr<ReshadeUniform>> createReshadeUniforms(reshadefx::module module)
    {
        std::vector<std::shared_ptr<ReshadeUniform>> uniforms;
        for (auto& uniform : module.uniforms)
        {
            auto source = std::find_if(uniform.annotations.begin(), uniform.annotations.end(), [](const auto& a) {
                              return a.name == "source";
                          })->value.string_data;
            if (source == "frametime")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new FrameTimeUniform(uniform)));
            }
            else if (source == "framecount")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new FrameCountUniform(uniform)));
            }
            else if (source == "date")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new DateUniform(uniform)));
            }
            else if (source == "timer")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new TimerUniform(uniform)));
            }
            else if (source == "pingpong")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new PingPongUniform(uniform)));
            }
            else if (source == "random")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new RandomUniform(uniform)));
            }
            else if (source == "key")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new KeyUniform(uniform)));
            }
            else if (source == "mousebutton")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new MouseButtonUniform(uniform)));
            }
            else if (source == "mousepoint")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new MousePointUniform(uniform)));
            }
            else if (source == "mousedelta")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new MouseDeltaUniform(uniform)));
            }
            else if (source == "bufready_depth")
            {
                uniforms.push_back(std::shared_ptr<ReshadeUniform>(new DepthUniform(uniform)));
            }
        }
        return uniforms;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    FrameTimeUniform::FrameTimeUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "frametime")
        {
            Logger::err("Tried to create a FrameTimeUniform from a non frametime uniform_info");
        }
        lastFrame = std::chrono::high_resolution_clock::now();
        offset    = uniformInfo.offset;
        size      = uniformInfo.size;
    }
    void FrameTimeUniform::update(void* mapedBuffer)
    {
        auto                                     currentFrame = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration     = currentFrame - lastFrame;
        lastFrame                                             = currentFrame;
        float frametime                                       = duration.count();
        std::memcpy((uint8_t*) mapedBuffer + offset, &(frametime), sizeof(float));
    }
    FrameTimeUniform::~FrameTimeUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    FrameCountUniform::FrameCountUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "framecount")
        {
            Logger::err("Tried to create a FrameCountUniform from a non framecount uniform_info");
        }
        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void FrameCountUniform::update(void* mapedBuffer)
    {
        std::memcpy((uint8_t*) mapedBuffer + offset, &(count), sizeof(int32_t));
        count++;
    }
    FrameCountUniform::~FrameCountUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    DateUniform::DateUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "date")
        {
            Logger::err("Tried to create a DateUniform from a non date uniform_info");
        }
        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void DateUniform::update(void* mapedBuffer)
    {
        auto        now         = std::chrono::system_clock::now();
        std::time_t nowC        = std::chrono::system_clock::to_time_t(now);
        struct tm*  currentTime = std::localtime(&nowC);
        float       year        = 1900.0f + static_cast<float>(currentTime->tm_year);
        float       month       = 1.0f + static_cast<float>(currentTime->tm_mon);
        float       day         = static_cast<float>(currentTime->tm_mday);
        float       seconds     = static_cast<float>((currentTime->tm_hour * 60 + currentTime->tm_min) * 60 + currentTime->tm_sec);
        float       date[]      = {year, month, day, seconds};
        std::memcpy((uint8_t*) mapedBuffer + offset, date, sizeof(float) * 4);
    }
    DateUniform::~DateUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    TimerUniform::TimerUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "timer")
        {
            Logger::err("Tried to create a TimerUniform from a non timer uniform_info");
        }
        start  = std::chrono::high_resolution_clock::now();
        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void TimerUniform::update(void* mapedBuffer)
    {
        auto                                     currentFrame = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration     = currentFrame - start;
        float                                    timer        = duration.count();
        std::memcpy((uint8_t*) mapedBuffer + offset, &(timer), sizeof(float));
    }
    TimerUniform::~TimerUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    PingPongUniform::PingPongUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "pingpong")
        {
            Logger::err("Tried to create a PingPongUniform from a non pingpong uniform_info");
        }
        if (auto minAnnotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "min"; });
            minAnnotation != uniformInfo.annotations.end())
        {
            min = minAnnotation->type.is_floating_point() ? minAnnotation->value.as_float[0] : static_cast<float>(minAnnotation->value.as_int[0]);
        }
        if (auto maxAnnotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "max"; });
            maxAnnotation != uniformInfo.annotations.end())
        {
            max = maxAnnotation->type.is_floating_point() ? maxAnnotation->value.as_float[0] : static_cast<float>(maxAnnotation->value.as_int[0]);
        }
        if (auto smoothingAnnotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "smoothing"; });
            smoothingAnnotation != uniformInfo.annotations.end())
        {
            smoothing = smoothingAnnotation->type.is_floating_point() ? smoothingAnnotation->value.as_float[0]
                                                                      : static_cast<float>(smoothingAnnotation->value.as_int[0]);
        }
        if (auto stepAnnotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "step"; });
            stepAnnotation != uniformInfo.annotations.end())
        {
            stepMin =
                stepAnnotation->type.is_floating_point() ? stepAnnotation->value.as_float[0] : static_cast<float>(stepAnnotation->value.as_int[0]);
            stepMax =
                stepAnnotation->type.is_floating_point() ? stepAnnotation->value.as_float[1] : static_cast<float>(stepAnnotation->value.as_int[1]);
        }

        lastFrame = std::chrono::high_resolution_clock::now();

        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void PingPongUniform::update(void* mapedBuffer)
    {
        auto currentFrame = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float, std::ratio<1>> frameTime = currentFrame - lastFrame;

        float increment = stepMax == 0 ? stepMin : (stepMin + std::fmod(static_cast<float>(std::rand()), stepMax - stepMin + 1.0f));
        if (currentValue[1] >= 0)
        {
            increment = std::max(increment - std::max(0.0f, smoothing - (max - currentValue[0])), 0.05f);
            increment *= frameTime.count();

            if ((currentValue[0] += increment) >= max)
            {
                currentValue[0] = max, currentValue[1] = -1.0f;
            }
        }
        else
        {
            increment = std::max(increment - std::max(0.0f, smoothing - (currentValue[0] - min)), 0.05f);
            increment *= frameTime.count();

            if ((currentValue[0] -= increment) <= min)
            {
                currentValue[0] = min, currentValue[1] = 1.0f;
            }
        }
        std::memcpy((uint8_t*) mapedBuffer + offset, currentValue, sizeof(float) * 2);
    }
    PingPongUniform::~PingPongUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    RandomUniform::RandomUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "random")
        {
            Logger::err("Tried to create a RandomUniform from a non random uniform_info");
        }
        if (auto minAnnotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "min"; });
            minAnnotation != uniformInfo.annotations.end())
        {
            min = minAnnotation->type.is_integral() ? minAnnotation->value.as_int[0] : static_cast<int>(minAnnotation->value.as_float[0]);
        }
        if (auto maxAnnotation =
                std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "max"; });
            maxAnnotation != uniformInfo.annotations.end())
        {
            max = maxAnnotation->type.is_integral() ? maxAnnotation->value.as_int[0] : static_cast<int>(maxAnnotation->value.as_float[0]);
        }
        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void RandomUniform::update(void* mapedBuffer)
    {
        int32_t value = min + (std::rand() % (max - min + 1));
        std::memcpy((uint8_t*) mapedBuffer + offset, &(value), sizeof(int32_t));
    }
    RandomUniform::~RandomUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    KeyUniform::KeyUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "key")
        {
            Logger::err("Tried to create a KeyUniform from a non key uniform_info");
        }

        std::string modeStr;
        int         toggle;

        get_annotation(uniformInfo, "keycode", keySym);
        get_annotation(uniformInfo, "mode", modeStr);
        get_annotation(uniformInfo, "toggle", toggle);

        keySym = convertToKeySym(keySym);

        if (modeStr == "toggle" || toggle)
            mode = TOGGLE;
        else
            mode = PRESS;

        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void KeyUniform::update(void* mapedBuffer)
    {
        VkBool32 keyDown = VK_FALSE;

        if (keySym != 0)
        {
            if (mode == TOGGLE)
            {
                std::memcpy(&(keyDown), (uint8_t*) mapedBuffer + offset, sizeof(VkBool32));
                keyDown = keyDown != isKeyPressed(keySym);
            }
            else
                keyDown = isKeyPressed(keySym);
        }

        std::memcpy((uint8_t*) mapedBuffer + offset, &(keyDown), sizeof(VkBool32));
    }
    KeyUniform::~KeyUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    MouseButtonUniform::MouseButtonUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "mousebutton")
        {
            Logger::err("Tried to create a MouseButtonUniform from a non mousebutton uniform_info");
        }

        std::string modeStr;
        int         toggle;
        int         keycode;

        get_annotation(uniformInfo, "keycode", keycode);
        get_annotation(uniformInfo, "mode", modeStr);
        get_annotation(uniformInfo, "toggle", toggle);

        switch (keycode)
        {
            case 0: button = MB_LEFT; break;
            case 1: button = MB_RIGHT; break;
            case 2: button = MB_MIDDLE; break;
            case 3: button = MB_4; break;
            case 4: button = MB_5; break;
            default: button = INVALID; break;
        }

        if (modeStr == "toggle" || toggle)
            mode = TOGGLE;
        else
            mode = PRESS;

        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void MouseButtonUniform::update(void* mapedBuffer)
    {
        VkBool32 keyDown = VK_FALSE;

        const MouseData md = getMouseData();

        if (mode == TOGGLE)
        {
            std::memcpy(&(keyDown), (uint8_t*) mapedBuffer + offset, sizeof(VkBool32));
            switch (button)
            {
                case MB_LEFT: keyDown = keyDown != md.buttonLeftPressed; break;
                case MB_RIGHT: keyDown = keyDown != md.buttonRightPressed; break;
                case MB_MIDDLE: keyDown = keyDown != md.buttonMiddlePressed; break;
                case MB_4: keyDown = keyDown != md.button4Pressed; break;
                case MB_5: keyDown = keyDown != md.button5Pressed; break;
                case INVALID: break;
            }
        }
        else
        {
            switch (button)
            {
                case MB_LEFT: keyDown = md.buttonLeftPressed; break;
                case MB_RIGHT: keyDown = md.buttonRightPressed; break;
                case MB_MIDDLE: keyDown = md.buttonMiddlePressed; break;
                case MB_4: keyDown = md.button4Pressed; break;
                case MB_5: keyDown = md.button5Pressed; break;
                case INVALID: break;
            }
        }

        std::memcpy((uint8_t*) mapedBuffer + offset, &(keyDown), sizeof(VkBool32));
    }
    MouseButtonUniform::~MouseButtonUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    MousePointUniform::MousePointUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "mousepoint")
        {
            Logger::err("Tried to create a MousePointUniform from a non mousepoint uniform_info");
        }
        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void MousePointUniform::update(void* mapedBuffer)
    {
        const MouseData md       = getMouseData();
        const float     point[2] = {static_cast<float>(md.win_x_return), static_cast<float>(md.win_y_return)};
        std::memcpy((uint8_t*) mapedBuffer + offset, point, sizeof(int32_t) * 2);
    }
    MousePointUniform::~MousePointUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    MouseDeltaUniform::MouseDeltaUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "mousedelta")
        {
            Logger::err("Tried to create a MouseDeltaUniform from a non mousedelta uniform_info");
        }
        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void MouseDeltaUniform::update(void* mapedBuffer)
    {
        float delta[2] = {0.0f, 0.0f}; // TODO
        std::memcpy((uint8_t*) mapedBuffer + offset, delta, sizeof(float) * 2);
    }
    MouseDeltaUniform::~MouseDeltaUniform()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    DepthUniform::DepthUniform(reshadefx::uniform_info uniformInfo)
    {
        auto source = std::find_if(uniformInfo.annotations.begin(), uniformInfo.annotations.end(), [](const auto& a) { return a.name == "source"; });
        if (source->value.string_data != "bufready_depth")
        {
            Logger::err("Tried to create a DepthUniform from a non bufready_depth uniform_info");
        }
        offset = uniformInfo.offset;
        size   = uniformInfo.size;
    }
    void DepthUniform::update(void* mapedBuffer)
    {
        VkBool32 hasDepth = VK_FALSE; // TODO
        std::memcpy((uint8_t*) mapedBuffer + offset, &(hasDepth), sizeof(VkBool32));
    }
    DepthUniform::~DepthUniform()
    {
    }
} // namespace vkBasalt
