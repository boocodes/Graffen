#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <../stb_image.h>
#include <glm/glm.hpp>
#include <string>
#include <httplib.h>



class UtilModule
{
public:
	static glm::vec3 hex_to_vec3(const std::string& hexColor);
};