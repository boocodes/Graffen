#pragma once
#include <gui_tags/root/root_tag.h>
#include <module/util/util_module.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <global/global.h>
#include <glm/glm.hpp>
#include <vector>


class DivTag : public RootTag
{
public:
	float opacity = 1.0f;
	bool visibility = true;
	glm::vec4 borderRadius;
	glm::vec4 backgroundColor;
	unsigned int VAO, VBO, texture, EBO;
	std::string backgroundImage;

	int borderSize;
	float borderOpacity;
	glm::vec4 borderColor;

	
	DivTag(int xPos, int yPos, int zIndex, int width, int height);
	~DivTag();
	float coords[20];
	void draw();
	bool hoverCheck(int mouseX, int mouseY);
	bool clickCheck(int mouseX, int mouseY);
	
	void setBorder(int size, glm::vec4 color);
	void setBorderOpacity(float opacity);


};