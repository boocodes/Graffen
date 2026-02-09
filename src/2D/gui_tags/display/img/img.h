#pragma once
#include "2D/gui_tags/display/root/root_display.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <2D/modules/utils/utils.h>
#include <2D/global/global.h>

class ImgDisplayTag : public RootDisplayTag
{
private:
	glm::vec4 border_radius;
	unsigned int VAO, VBO;
	std::string image;
	TextureEntity texture_entity;
	float coords[32];
	void rebuild_vertex_objects();
public:
	ImgDisplayTag(int x_pos, int y_pos, int z_index, const std::string& image);
	~ImgDisplayTag();

	void draw();
	bool hover_check(int mouse_x, int mouse_y);
	bool click_check(int mouse_x, int mouse_y);

	void change_image(const std::string& new_image);
	void resize(int new_width, int new_height);
};