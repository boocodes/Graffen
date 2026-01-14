#pragma once
#pragma once
#include <string>
#include <functional>
#include <vector>


class RootTag
{
public:
	int innerId;
	std::string tagType;
	int zIndex;
	int width, height;
	std::string className = "";
	int xPos, yPos;
	bool hovered;
	std::function<void()> onClick = 0;
	std::function<void()> onHover = 0;
	RootTag* parentTag;
	virtual ~RootTag() = default;
	virtual void draw() = 0;
	int getInnerId() { return this->innerId; };
	virtual bool hoverCheck(int mouseX, int mouseY) = 0;
	/*virtual int getPositionToChildren() = 0;*/
	virtual bool clickCheck(int mouseX, int mouseY) = 0;
};