#pragma once
#include <2D/gui_tags/display/root/root_display.h>
#include <vector>
#include <algorithm>
#include <iostream>


class DisplayTagsContainer
{
private:
	std::vector<RootDisplayTag*> tags;
public:
	DisplayTagsContainer(std::vector<RootDisplayTag*> tags);
	DisplayTagsContainer();
	void draw();
	void add_tag(RootDisplayTag* tag);
	void run_click(int mouse_x, int mouse_y);
	void log_inner_data();
};