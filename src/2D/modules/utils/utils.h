#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <glad/glad.h>
#include <../stb_image.h>
#include <glm/glm.hpp>
#include <string>
#include <httplib.h>


class TextureEntity
{
public:
	TextureEntity() {};
	unsigned int texture;
	int width;
	int height;
	int nr_channels;
};



class UtilModule
{
public:
	static TextureEntity get_texture(const char* image_path);
	static glm::vec3 hex_to_vec3(const std::string& hexColor);
};