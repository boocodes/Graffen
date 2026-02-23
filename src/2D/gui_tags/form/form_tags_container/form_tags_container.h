#pragma once
#include <2D/gui_tags/form/root/root_form.h>
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>


class FormTagsContainer
{
private:
	std::vector<RootFormTag*> tags;
public:
	FormTagsContainer();
	void add_tag(RootFormTag* tag);
	void draw();
	void log_inner_data();
	void get_keyboard_char(char input_char);
	std::vector<RootFormTag*> get_tags() { return this->tags; };
	void get_special_key(int action, int key);
	void update_value(char new_char, RootFormTag* active_form_elem);
	void run_click(int mouse_x, int mouse_y);
	void run_hover(int mouse_x, int mouse_y);
	void disable_all_form_tags();
	std::vector<RootFormTag*> get_tags_list;
};