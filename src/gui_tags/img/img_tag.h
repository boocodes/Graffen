#pragma once
#include <gui_tags/root/root_tag.h>
#include <glm/glm.hpp>
#include <global/global.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <../stb_image.h>


class ImgTag : public RootTag
{
public:
	float opacity;
	bool visibility;
	glm::vec4 border_radius;
	unsigned int VAO, VBO, texture;
	std::string image;




	ImgTag(int xPos, int yPos, int zIndex, const char* image);
	~ImgTag();
	float coords[32];
	void draw();
	bool hoverCheck(int mouse_x, int mouse_y);
	bool clickCheck(int mouse_x, int mouse_y);
	void resize(int new_width, int new_height);
	void centred_x(int parent_width);
	void centred_y(int parent_height);
	


	void margin_top(int margin);
	void margin_left(int margin);
	void margin_right(int margin);
	void margin_bottom(int margin);
};