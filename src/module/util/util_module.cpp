#include "util_module.h"


glm::vec3 UtilModule::hexToVec3(const std::string& hexColor)
{
	glm::vec3 defaultColor = glm::vec3(0.0f, 0.0f, 0.0f);
	if (hexColor.empty() || hexColor[0] != '#')
	{
		return defaultColor;
	}
	std::string hex = hexColor.substr(1);
	if (hex.length() == 3)
	{
		hex = std::string(2, hex[0]) + std::string(2, hex[1]) + std::string(2, hex[2]);
	}
	if (hex.length() != 6)
	{
		return defaultColor;
	}
	int r, g, b;
	sscanf_s(hex.c_str(), "%02x%02x%02x", &r, &g, &b);
	return glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}