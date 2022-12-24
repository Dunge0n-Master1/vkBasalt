#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib>

#include "json.hpp"
#include "vulkan_include.hpp"

namespace vkBasalt
{
    class Config
    {
    public:
        Config();
        Config(const Config& other);

        template<typename T>
        T getOption(const std::string& option, const T& defaultValue = {})
        {
            T result = defaultValue;
            if (isJson())
            {
                if (json.contains(option) && !json[option].is_null())
                {
                    result = json[option];
                }
            }
            else
                parseOption(option, result);
            return result;
        }

        std::string getReshadeEffectPath(const std::string& effectName);

        bool checkReshadeEffectOption(const std::string& effectName, const std::string& option);

        template<typename T>
        T getReshadeEffectOption(const std::string& effectName, const std::string& option, uint index, const T& defaultValue = {})
        {
            if (isJson())
            {
                try
                {
                    nlohmann::json value = json["reshade_effects"][effectName]["options"][option];
                    if (value.is_array())
                        return value[index].get<T>();
                    return value.get<T>();
                }
                catch (const nlohmann::json::exception& e)
                {
                    Logger::err(effectName + "[" + option + "] failed: " + e.what());
                    return defaultValue;
                }
            }
            else
                return getOption<T>(option, defaultValue);
        }

        std::map<std::string, std::string> getReshadeEffectDefines(const std::string& effectName);

        bool isJson()
        {
            return !json.empty();
        }

    private:
        std::unordered_map<std::string, std::string> options;
        nlohmann::json                               json;

        void readConfigLine(std::string line);
        void readConfigFile(std::ifstream& stream);

        void parseOption(const std::string& option, int32_t& result);
        void parseOption(const std::string& option, float& result);
        void parseOption(const std::string& option, bool& result);
        void parseOption(const std::string& option, std::string& result);
        void parseOption(const std::string& option, std::vector<std::string>& result);
    };
} // namespace vkBasalt

#endif // CONFIG_HPP_INCLUDED
