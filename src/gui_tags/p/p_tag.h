#pragma once
#pragma once
#include <gui_tags/root/root_tag.h>
#include <module/font/font_module.h>
#include <string>
#include <global/global.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class PTag: public RootTag
{
public:
	int fontSize;
	glm::vec3 color;
	std::string textDisplay;
	std::string fontName;
	float coords[12];
	FontModule font;
	bool visibility = true;
	PTag(int xPos, int yPos, glm::vec3 color, int fontSize, std::string fontName, std::string textDisplay, int zIndex);
	void draw();
	void changeText(std::string newText);
	void changeFont(std::string newFont);
	void changeFontSize(int newFontSize);
	bool hoverCheck(int mouseX, int mouseY);
	int getPositionToChildren() { return 0; };
	bool clickCheck(int mouseX, int mouseY);
	void center();
};