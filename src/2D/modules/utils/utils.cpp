#include "utils.h"


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

TextureEntity UtilModule::get_texture(const char* image_path)
{
    TextureEntity result_texture;
    unsigned char* data = stbi_load(image_path, &result_texture.width, &result_texture.height, &result_texture.nr_channels, 0);

    glGenTextures(1, &result_texture.texture);
    glBindTexture(GL_TEXTURE_2D, result_texture.texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data)
    {
        GLenum format;
        switch (result_texture.nr_channels)
        {
        case 1: format = GL_RED; break;
        case 2: format = GL_RG; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: 
            std::cout << "Unsupported number of loading image channels: " << result_texture.nr_channels << std::endl;
            stbi_image_free(data);
            return;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, result_texture.width, result_texture.height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Error loading texture from file - " << image_path << std::endl;
        exit(0);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return result_texture;
}