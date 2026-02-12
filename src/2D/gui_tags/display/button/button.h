#pragma once
#include <2D/gui_tags/display/root/root_display.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <2D/gui_tags/display/text/text.h>
#include <GLFW/glfw3.h>
#include <future>
#include <chrono>

class ButtonDisplayTag : public RootDisplayTag
{
private:
	float coords[12];

	// top - right - bottom - left
	glm::vec4 padding;
	
	GLFWcursor* active_cursor;

	TextDisplayTag* button_text;
	std::string display_text;

	glm::vec4 border_radius;
	glm::vec4 background_color;
	glm::vec4 border_width;
	glm::vec4 border_color;

	unsigned int VAO, VBO, texture, EBO;
	std::string background_image;

	float border_opacity;

	void rebuild_vertex_objects();

public:

	ButtonDisplayTag(int x_pos, int y_pos, int z_pos, const std::string& text);
	~ButtonDisplayTag();
	void draw();
	bool hover_check(int mouse_x, int mouse_y);
	bool click_check(int mouse_x, int mouse_y);

	// border
	void set_border_radius(glm::vec4 new_border_radius);
	void set_background_color(glm::vec4 new_background_color);
	void set_border_width(glm::vec4 new_border_width);
	void set_border_color(glm::vec4 new_border_color);
	void set_border_opacity(float border_opacity);


	void set_background_image(const std::string& new_image);
	void set_padding(glm::vec4 new_padding);
	void set_height(int new_height);
	void set_width(int new_width);
	void set_size(int new_width, int new_height);
	void set_z(int z);
};