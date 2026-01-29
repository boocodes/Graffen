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


class InputTag : public RootTag
{
private:

public:
	float opacity = 1.0f;
	bool visibility = true;
	glm::vec4 borderRadius;
	glm::vec4 backgroundColor;
	unsigned int VAO, VBO, texture, EBO;
	std::string backgroundImage;
	PTag *value_text = NULL;
	glm::vec4 borderWidth;
	glm::vec4 write_bar_color;
	std::string placeholder;
	int write_bar_height;
	int write_bar_width;
	int borderSize;
	float borderOpacity;
	glm::vec4 borderColor;


	InputTag(int xPos, int yPos, int zIndex, int width, int height);
	~InputTag();
	float coords[20];
	void draw();
	bool hoverCheck(int mouseX, int mouseY);
	bool clickCheck(int mouseX, int mouseY);
	std::string value;
	bool is_active;
	void setBorder(int size, glm::vec4 color);
	void setBorderOpacity(float opacity);
	void centred_x(int parent_width);
	void centred_y(int parent_height);


	void set_value(const std::string& value);
	void delete_last_char();
};