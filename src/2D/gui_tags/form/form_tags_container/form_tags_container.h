#pragma once
#include <2D/gui_tags/form/root/root_form.h>
#include <vector>
#include <iostream>

class FormTagsContainer
{
private:
	std::vector<RootFormTag*> tags;
public:
	FormTagsContainer();
	void add_tag(RootFormTag* tag);
	void draw();
	void log_inner_data();
};