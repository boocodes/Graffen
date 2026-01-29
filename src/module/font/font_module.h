#pragma once
#include <string>
#include <vector>
#include <functional>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <GLFW/glfw3.h>
#include <map>
#include <random>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H


struct Character {
    unsigned int TextureID;
    glm::ivec2   Size;
    glm::ivec2   Bearing;
    unsigned int Advance;
};

class FontModule {
private:
    
public:
    int id;
    int pixel_size_px = 48;
    std::string font_name;

    std::map<GLchar, Character> Characters;
    FontModule();
    unsigned int VAO, VBO, texture;
    void draw_text(std::string text_display = "", float x_pos = 0, float y_pos = 20, glm::vec3 color = glm::vec3(0, 0, 0));
    void init(std::string font_name, int pixel_size_px = 48);
    float get_text_width(const std::string& text);
    float get_text_height();
    glm::vec2 get_text_size(const std::string& text);

};