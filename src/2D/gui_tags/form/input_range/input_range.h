#pragma once
#include <2D/gui_tags/form/root/root_form.h>

class InputRangeFormTag : public RootFormTag
{
private:
	float coords[12];
	unsigned int VAO, VBO, texture;
	
};