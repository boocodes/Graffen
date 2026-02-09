#pragma once
#include <string>
#include <functional>

class RootDisplayTag
{
protected:
	bool visibility;
	float opacity;
	int self_id;
	std::string tag_type;
	int z_pos,
		x_pos,
		y_pos;
	int width,
		height;
	std::string class_name;
	std::function<void()> on_click = 0;
	std::function<void()> on_hover = 0;
	virtual ~RootDisplayTag() = default;
public:
	std::string get_tag_type();
	int get_z_pos();
	int get_y_pos();
	int get_x_pos();
	virtual void draw() = 0;
	int get_self_id();
	virtual bool hover_check(int mouse_x, int mouse_y) = 0;
	virtual bool click_check(int mouse_x, int mouse_y) = 0;
};