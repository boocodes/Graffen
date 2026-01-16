#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <../stb_image.h>
#include <glm/glm.hpp>
#include <string>

class UtilModule
{
public:
	static glm::vec3 hexToVec3(const std::string& hexColor);
};