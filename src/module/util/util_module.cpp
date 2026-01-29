#include "util_module.h"


glm::vec3 UtilModule::hex_to_vec3(const std::string& hexColor)
{
    glm::vec3 defaultColor = glm::vec3(0.0f, 0.0f, 0.0f);

    if (hexColor.empty())
    {
        return defaultColor;
    }

    std::string hex = hexColor;

    if (hex[0] == '#')
    {
        hex = hex.substr(1);
    }
    if (hex.length() == 3)
    {
        hex = std::string(2, hex[0]) +
            std::string(2, hex[1]) +
            std::string(2, hex[2]);
    }

    if (hex.length() != 6)
    {
        return defaultColor;
    }

    auto hexCharToInt = [](char c) -> int {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
        if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
        return 0;
        };

    for (char c : hex)
    {
        if (!((c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'f') ||
            (c >= 'A' && c <= 'F')))
        {
            return defaultColor;
        }
    }

    int r = hexCharToInt(hex[0]) * 16 + hexCharToInt(hex[1]);
    int g = hexCharToInt(hex[2]) * 16 + hexCharToInt(hex[3]);
    int b = hexCharToInt(hex[4]) * 16 + hexCharToInt(hex[5]);

    return glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}