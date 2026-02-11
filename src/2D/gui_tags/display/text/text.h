#pragma once
#include <glad/glad.h>
#include <2D/global/global.h>
#include <2D/gui_tags/display/root/root_display.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
	unsigned int TextureID;
	glm::ivec2   Size;
	glm::ivec2   Bearing;
	unsigned int Advance;
};
class FontModule
{
public:
	int id;
	int pixel_size_px = 48;
	std::string font_name;

	std::map<GLchar, Character> Characters;
	FontModule();
	unsigned int VAO, VBO, texture;
	void draw_text(std::string text_display = "", float x_pos = 0, float y_pos = 0, glm::vec3 color = glm::vec3(0, 0, 0));
	void init(std::string font_name, int pixel_size_px = 48);
	float get_text_width(const std::string& text);
	float get_text_height();
	glm::vec2 get_text_size(const std::string& text);
};

class TextDisplayTag : public RootDisplayTag
{
private:
	float line_height;
	float max_width;
	bool word_wrap;

	int font_size;
	glm::vec3 color;
	std::string text_display;
	std::string font_name;

	float coords[12];
	FontModule font;
public:
	TextDisplayTag();
	TextDisplayTag(int x_pos, int y_pos, int z_pos, std::string font_name, std::string text_display);
	void draw();
	std::string get_font_name();
	std::string get_text_display();
	void change_text(std::string new_text);
	void change_font(std::string new_font);
	void change_font_size(int new_font_size);
	bool hover_check(int mouse_x, int mouse_y);
	bool click_check(int mouse_x, int mouse_y);

	void set_max_width(float width);
	void set_word_wrap(bool wrap);
	float get_actual_line_height();

	std::vector<std::string> get_wrapped_lines(const std::string& text);
	glm::vec2 get_wrapper_text_size(const std::string& text);
};

