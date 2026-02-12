#pragma once
#include <string>
#include <functional>

class RootFormTag
{
protected:
	bool is_active;
	bool visibility;
	float opacity;
	int self_id;
	std::string input_form_value;
	std::string tag_type;
	int z_pos,
		x_pos,	
		y_pos;
	int width,
		height;
	std::string class_name;
	std::function<void()> on_click = 0;
	std::function<void()> on_hover = 0;
public: 
	virtual ~RootFormTag() = default;
	std::string get_tag_type();
	int get_z_pos();
	virtual void draw() = 0;
	int get_self_id();
	virtual bool hover_check(int mouse_x, int mouse_y) = 0;
	virtual bool click_check(int mouse_x, int mouse_y) = 0;
	std::string get_input_value();
	virtual void set_value(const std::string& new_value) = 0;
	bool get_active_flag();
	void set_active_flag(bool active_flag);
};