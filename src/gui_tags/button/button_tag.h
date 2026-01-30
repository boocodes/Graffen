#pragma once
#include <gui_tags/root/root_tag.h>
#include <module/util/util_module.h>
#include <glm/gtc/matrix_transform.hpp>
#include <gui_tags/p/p_tag.h>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <global/global.h>
#include <glm/glm.hpp>
#include <vector>


class ButtonTag : public RootTag
{
private:
	void resize(int width, int height);
public:
	float opacity = 1.0f;
	bool visibility = true;
	glm::vec4 borderRadius;
	glm::vec4 backgroundColor;
	unsigned int VAO, VBO, texture, EBO;
	std::string backgroundImage;
	PTag* button_text = NULL;
	std::string text;
	glm::vec4 borderWidth;
	glm::vec4 write_bar_color;
	std::string placeholder;
	int write_bar_height;
	int write_bar_width;
	int borderSize;
	float borderOpacity;
	glm::vec4 borderColor;


	ButtonTag(int xPos, int yPos, int zIndex, int width, int height, const std::string& text);
	~ButtonTag();
	float coords[20];
	void draw();
	bool hoverCheck(int mouseX, int mouseY);
	bool clickCheck(int mouseX, int mouseY);
	void setBorder(int size, glm::vec4 color);
	void setBorderOpacity(float opacity);
	void centred_x(int parent_width);
	void centred_y(int parent_height);


	void set_button_text(const std::string& value);


	void margin_top(int margin);
	void margin_left(int margin);
	void margin_right(int margin);
	void margin_bottom(int margin);

	// text 
	void change_font(const std::string& new_font);
	void change_font_size(int font_size);
	void change_font_color(glm::vec3 font_color);
};