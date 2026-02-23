#pragma once
#include <2D/gui_tags/form/root/root_form.h>
#include <2D/global/global.h>
#include <2D/gui_tags/display/text/text.h>
#include <2D/modules/IdGenerator/IdGenerator.h>

class InputSimpleFormTag : public RootFormTag
{
private:
	float coords[12];
	unsigned int VAO, VBO, texture;
	glm::vec4 border_width;
	int max_input_size;
	GLFWcursor* active_cursor;
	glm::vec4 border_radius;
	float border_opacity;
	glm::vec4 border_color;
	glm::vec4 background_color;
	TextDisplayTag* text_tag;
	std::string placeholder;
	std::string background_img;
	std::string text_align;
	void rebuild_vertex_objects();
public:
	void set_text_align(const std::string& align);
	void set_x_pos(int new_x_pos);
	void set_max_input_size(int max_size);
	void set_border_width(glm::vec4 new_border_width);
	void set_border_radius(glm::vec4 new_border_radius);
	void set_background_color(glm::vec4 new_background_color);
	void set_border_opacity(float border_opacity);
	void set_border_color(glm::vec4 new_border_color);
	InputSimpleFormTag(int x_pos, int y_pos, int z_pos, int width, int height);
	~InputSimpleFormTag();
	void draw();
	bool hover_check(int mouse_x, int mouse_y);
	bool click_check(int mouse_x, int mouse_y);
	void set_value(const std::string& new_value);
	void center_x(int root_container_width);

	void set_font_color(glm::vec3 new_font_color);
	void set_height(int new_height);
	void set_width(int new_width);
	void set_size(int new_width, int new_height);
	void set_z(int z);
	
};