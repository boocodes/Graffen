#include "p_tag.h"


PTag::PTag(int xPos, int yPos, glm::vec3 color, int fontSize, std::string fontName, std::string textDisplay, int zIndex)
{
	this->tagType = "Text";
	this->xPos = xPos;
	this->yPos = yPos;
	this->color = color;
	this->fontSize = fontSize;
	this->fontName = fontName;
	this->textDisplay = textDisplay;
	this->zIndex = zIndex;
	this->visibility = true;

	this->font.init(this->fontName, this->fontSize);
}


void PTag::draw()
{
	if (this->visibility)
	{
		this->font.draw_text(this->textDisplay, this->xPos, this->yPos, this->color);
	}
}


bool PTag::hoverCheck(int mouseX, int mouseY)
{
	return true;
}
bool PTag::clickCheck(int mouseX, int mouseY)
{
	return true;
}
void PTag::changeText(std::string newText)
{
	this->textDisplay = newText;
}
void PTag::changeFontSize(int newFontSize)
{
	this->fontSize = newFontSize;
	FontModule buffFont;
	buffFont.init(this->fontName, this->fontSize);
	this->font = buffFont;
}
void PTag::changeFont(std::string newFont)
{
	this->fontName = newFont;
	FontModule buffFont;
	buffFont.init(this->fontName, this->fontSize);
	this->font = buffFont;
}


void PTag::center()
{
	if (this->parentTag == nullptr)
	{
		this->xPos = (WIDTH - this->width) / 2;

	}
	else
	{
		this->xPos = (parentTag->width - this->width) / 2;
	}
}

