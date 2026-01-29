#pragma once
#include <gui_tags/input/input_tag.h>
#include <vector>


class FormTag
{
public:
	FormTag();
	int id;
	std::vector<InputTag*> input_list;
	void render();
	void add_element(InputTag* tag);
	void check_click(int mouseX, int mouseY);
	void disable_all_inputs();
};