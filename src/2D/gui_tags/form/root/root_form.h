#pragma once
#include <string>

class RootFormTag
{
private:
	int x_pos;
	int y_pos;
	int z_pos;
	std::string tag_type;
public:
	std::string get_tag_type();
	int get_z_pos();
	void draw();
};