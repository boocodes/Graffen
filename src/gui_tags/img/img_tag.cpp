#include "img_tag.h"
#include <iostream>


ImgTag::~ImgTag() {};


ImgTag::ImgTag(int xPos, int yPos, int zIndex, const char* image)
{

	int nrChannels;
	stbi_set_flip_vertically_on_load(false);
	unsigned char* data = stbi_load(image, &this->width, &this->height, &nrChannels, 0);


	this->xPos = xPos;
	this->yPos = yPos;
	this->zIndex = zIndex;
	std::cout << this->width << ", " << this->height << std::endl;
	this->border_radius = glm::vec4(0, 0, 0, 0);
	this->opacity = 1.0f;
	this->visibility = true;
	
	float coords[32] =
	{
		this->xPos,               this->yPos + this->height, this->zIndex,  0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
		this->xPos + this->width, this->yPos + this->height, this->zIndex,	0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		this->xPos + this->width, this->yPos,                this->zIndex,  0.0f, 0.0f, 0.0f,    1.0f, 0.0f,
		this->xPos,               this->yPos,                this->zIndex,  0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	};
	for (size_t i = 0; i < 32; i++)
	{
		this->coords[i] = coords[i];
	}

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

	// Координатные атрибуты
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цветовые атрибуты
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Атрибуты текстурных координат
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	
	if (data)
	{
		GLenum format;

		switch (nrChannels)
		{
		case 1: format = GL_RED; break;
		case 2: format = GL_RG; break;
		case 3: format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
		default: 
			std::cout << "Unsupported number of loading image channels: " << nrChannels << std::endl;
			stbi_image_free(data);
			return;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error loading texture from file - " << image << std::endl;
		exit(0);
	}
	stbi_image_free(data);


	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void ImgTag::draw()
{
	
	if (this->visibility)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glBindTexture(GL_TEXTURE_2D, this->texture);
		imgGuiShader.use();
		imgGuiShader.setMat4("projection", pixelPlacementProjection);
		
		glBindVertexArray(this->VAO);
		

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void ImgTag::resize(int new_width, int new_height)
{
	this->width = new_width;
	this->height = new_height;

	float coords[32] =
	{
		this->xPos,               this->yPos + this->height, this->zIndex,  0.0f, 0.0f, 0.0f,    0.0f, 1.0f,
		this->xPos + this->width, this->yPos + this->height, this->zIndex,	0.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		this->xPos + this->width, this->yPos,                this->zIndex,  0.0f, 0.0f, 0.0f,    1.0f, 0.0f,
		this->xPos,               this->yPos,                this->zIndex,  0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	};
	for (size_t i = 0; i < 32; i++)
	{
		this->coords[i] = coords[i];
	}

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

	// Координатные атрибуты
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цветовые атрибуты
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Атрибуты текстурных координат
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	

}


bool ImgTag::hoverCheck(int mouseX, int mouseY)
{
	return 1;
}

bool ImgTag::clickCheck(int mouseX, int mouseY)
{
	if (((mouseX >= this->xPos) && (mouseX <= this->xPos + this->width)) && ((mouseY >= this->yPos) && (mouseY <= this->yPos + this->height)))
	{
		std::cout << "from IMG!" << std::endl;
		return true;
	}
	return false;
}