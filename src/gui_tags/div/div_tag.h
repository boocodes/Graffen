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
	std::vector<RootTag*> children;
	float opacity = 1.0f;
	bool visibility = true;
	float borderRadius;
	glm::vec3 backgroundColor;
	unsigned int VAO, VBO, texture;
	std::string backgroundImage;
	DivTag(int xPos, int yPos, int zIndex, int width, int height);
	~DivTag();
	float coords[12];
	void draw();
	int getPositionToChildren();
	bool hoverCheck(int mouseX, int mouseY);
	bool clickCheck(int mouseX, int mouseY);
	void addChild(RootTag* tag);


	void center();


};