#pragma once
#include <2D/gui_tags/form/root/root_form.h>
#include <2D/global/global.h>
#include <2D/gui_tags/display/text/text.h>


class InputSimpleFormTag : public RootFormTag
{
private:
	float coords[12];
	unsigned int VAO, VBO, texture;
	glm::vec4 border_width;
	glm::vec4 border_radius;
	float border_opacity;
	glm::vec4 border_color;
	glm::vec4 background_color;
	TextDisplayTag* text_tag;
	std::string placeholder;
	std::string background_img;

public:
	InputSimpleFormTag(int x_pos, int y_pos, int z_pos, int width, int height);
	~InputSimpleFormTag();
	void draw();
	bool hover_check(int mouse_x, int mouse_y);
	bool click_check(int mouse_x, int mouse_y);
	void set_value(const std::string& new_value);
	
};