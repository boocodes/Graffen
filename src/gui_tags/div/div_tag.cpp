#include "div_tag.h"



void initStyle();



DivTag::DivTag(int xPos, int yPos, int zIndex, int width, int height)
{
	this->tagType = "Div";
	this->borderRadius = glm::vec4(50, 50, 50, 50);
	this->xPos = xPos;
	this->yPos = yPos;
	this->zIndex = zIndex;
	this->width = width;
	this->visibility = true;
	this->height = height;
	this->backgroundColor = glm::vec3(0, 0, 0);

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

void DivTag::draw()
{
	if (this->visibility)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		divGuiShader.use();
		divGuiShader.setMat4("projection", pixelPlacementProjection);
		divGuiShader.setVec2("size", glm::vec2(this->width, this->height));
		divGuiShader.setVec2("position", glm::vec2(xPos, yPos));
		divGuiShader.setVec3("color", this->backgroundColor);
		divGuiShader.setVec4("borderRadius", this->borderRadius);

		divGuiShader.setInt("borderSize", this->borderSize);
		divGuiShader.setVec3("borderColor", this->borderColor);
		divGuiShader.setFloat("borderOpacity", this->borderOpacity);
		divGuiShader.setFloat("smoothing", 1.0f);
			
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindVertexArray(0);
		glDisable(GL_BLEND);
	}
}


bool DivTag::clickCheck(int mouseX, int mouseY)
{
	return true;
}

bool DivTag::hoverCheck(int mouseX, int mouseY)
{
	return true;
}


void DivTag::setBorder(int size, glm::vec3 color)
{
	this->borderSize = size;
	this->borderColor = color;
}

void DivTag::setBorderOpacity(float opacity)
{
	this->borderOpacity = opacity;
}


DivTag::~DivTag()
{

}



