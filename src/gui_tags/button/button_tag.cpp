#include "button_tag.h"
#include <iostream>



void ButtonTag::resize(int width, int height)
{ 
	this->width = width;
	this->height = height;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	float coords[12] = {
		this->xPos,               this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos,                this->zIndex,
		this->xPos,               this->yPos,                this->zIndex,
	};
	for (size_t i = 0; i < 12; i++)
	{
		this->coords[i] = coords[i];
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coords), this->coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	int button_text_height = this->button_text->get_wrapper_text_size(this->text).y;
	int button_text_width = this->button_text->get_wrapper_text_size(this->text).x;

	this->button_text = new PTag(this->xPos + ((this->width - button_text_width) / 2), this->yPos + ((this->height - button_text_height) / 2), this->button_text->color, this->button_text->fontSize, this->button_text->fontName, this->button_text->textDisplay, this->button_text->zIndex);
}



ButtonTag::ButtonTag(int xPos, int yPos, int zIndex, int width, int height, const std::string& text)
{
	this->tagType = "Input";
	this->borderRadius = glm::vec4(0, 0, 0, 0);
	this->xPos = xPos;
	this->yPos = yPos;
	this->zIndex = zIndex;
	this->width = width;
	this->text = text;
	this->borderWidth = glm::vec4(2, 2, 2, 2);
	this->borderColor = glm::vec4(0.9, 0.9, 0.9, 1);
	this->visibility = true;
	this->height = height;
	this->backgroundColor = glm::vec4(1, 1, 1, 1);

	this->button_text = new PTag(this->xPos, this->yPos, glm::vec3(0, 0, 1), 14, "assets/fonts/JetBrainsMono-Medium.ttf", this->text, 1);
	int button_text_height = this->button_text->get_wrapper_text_size(this->text).y;
	int button_text_width = this->button_text->get_wrapper_text_size(this->text).x;

	this->button_text = new PTag(this->xPos + ((this->width - button_text_width) / 2) , this->yPos + ((this->height - button_text_height) / 2), glm::vec3(0, 0, 1), 14, "assets/fonts/JetBrainsMono-Medium.ttf", this->text, 1);


	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	float coords[12] = {
		this->xPos,               this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos,                this->zIndex,
		this->xPos,               this->yPos,                this->zIndex,
	};
	for (size_t i = 0; i < 12; i++)
	{
		this->coords[i] = coords[i];
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coords), this->coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
}

void ButtonTag::draw()
{
	if (this->visibility)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		divGuiShader.use();
		divGuiShader.setMat4("projection", pixelPlacementProjection);
		divGuiShader.setVec2("size", glm::vec2(this->width, this->height));
		divGuiShader.setVec2("position", glm::vec2(xPos, yPos));
		divGuiShader.setVec4("color", this->backgroundColor);
		divGuiShader.setVec4("borderRadius", this->borderRadius);

		divGuiShader.setInt("borderSize", this->borderSize);

		divGuiShader.setFloat("borderOpacity", this->borderOpacity);
		divGuiShader.setFloat("smoothing", 1.0f);
		divGuiShader.setVec4("borderWidth", this->borderWidth);
		divGuiShader.setVec4("borderColor", this->borderColor);

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
		glDisable(GL_BLEND);

		this->button_text->draw();

	}
}


bool ButtonTag::clickCheck(int mouseX, int mouseY)
{
	if (((mouseX >= this->xPos) && (mouseX <= this->xPos + this->width)) && ((mouseY >= this->yPos) && (mouseY <= this->yPos + this->height)))
	{
		std::cout << "from button!" << std::endl;
		return true;
	}
	return false;
}


bool ButtonTag::hoverCheck(int mouseX, int mouseY)
{
	return true;
}


void ButtonTag::centred_x(int parent_width)
{
	if (parent_width <= this->width)
	{
		return;
	}
	this->xPos = (parent_width - this->width) / 2;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	float coords[12] = {
		this->xPos,               this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos,                this->zIndex,
		this->xPos,               this->yPos,                this->zIndex,
	};
	for (size_t i = 0; i < 12; i++)
	{
		this->coords[i] = coords[i];
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coords), this->coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
}

void ButtonTag::centred_y(int parent_height)
{
	if (parent_height <= this->height)
	{
		return;
	}
	this->yPos = (parent_height - this->height) / 2;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	float coords[12] = {
		this->xPos,               this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos + this->height, this->zIndex,
		this->xPos + this->width, this->yPos,                this->zIndex,
		this->xPos,               this->yPos,                this->zIndex,
	};
	for (size_t i = 0; i < 12; i++)
	{
		this->coords[i] = coords[i];
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coords), this->coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
}



void ButtonTag::setBorder(int size, glm::vec4 color)
{
	this->borderSize = size;
	this->borderColor = color;
}

void ButtonTag::setBorderOpacity(float opacity)
{
	this->borderOpacity = opacity;
}


ButtonTag::~ButtonTag()
{

}


void ButtonTag::set_button_text(const std::string& value)
{
	this->text = value;
	this->button_text = new PTag(this->button_text->xPos, this->button_text->yPos, this->button_text->color, this->button_text->fontSize, this->button_text->fontName, this->text, this->button_text->zIndex);
}



void ButtonTag::change_font(const std::string& new_font)
{
	this->button_text = new PTag(this->button_text->xPos, this->button_text->yPos, this->button_text->color, this->button_text->fontSize, new_font, this->button_text->textDisplay, this->button_text->zIndex);
}
void ButtonTag::change_font_size(int font_size)
{
	this->button_text = new PTag(this->button_text->xPos, this->button_text->yPos, this->button_text->color, font_size, this->button_text->fontName, this->button_text->textDisplay, this->button_text->zIndex);
}
void ButtonTag::change_font_color(glm::vec3 font_color)
{
	this->button_text = new PTag(this->button_text->xPos, this->button_text->yPos, font_color, this->button_text->fontSize, this->button_text->fontName, this->button_text->textDisplay, this->button_text->zIndex);
}



void ButtonTag::margin_top(int margin)
{
	this->yPos = xPos + margin;
	this->resize(this->width, this->height);
}

void ButtonTag::margin_left(int margin)
{
	this->xPos = xPos + margin;
	this->resize(this->width, this->height);
}

void ButtonTag::margin_right(int margin)
{
	this->xPos = xPos - margin;
	this->resize(this->width, this->height);
}

void ButtonTag::margin_bottom(int margin)
{
	this->yPos = yPos - margin;
	this->resize(this->width, this->height);
}