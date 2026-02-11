#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <2D/gui_tags/display/root/root_display.h>
#include <2D/gui_tags/form/root/root_form.h>
#include <2D/gui_tags/display/display_tags_container/display_tags_container.h>
#include <2D/gui_tags/form/form_tags_container/form_tags_container.h>

class WindowModule
{
private:
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	FormTagsContainer form_tags_container;
	DisplayTagsContainer display_tags_container;
	std::string window_title;
	GLFWwindow* window;
	int mouse_x,
		mouse_y;
	int width,
		height;
public:
	// setters
	void set_form_tags_container(FormTagsContainer container);
	void set_display_tags_container(DisplayTagsContainer container);
	void set_window_width(int width);
	void set_window_height(int height);
	void set_mouse_pos(int mouse_x, int mouse_y);
	void set_window_title(const std::string& window_title);
	// 
	// getters
	GLFWwindow* get_window();
	FormTagsContainer get_form_tags_container();
	DisplayTagsContainer get_display_tags_container();
	int get_window_width();
	int get_window_height();
	int get_mouse_x();
	int get_mouse_y();
	std::string get_window_title();
	void add_form_tag(RootFormTag* tag);
	void add_display_tag(RootDisplayTag* tag);
	//
	WindowModule();
	~WindowModule();
	void render();

	void launch_click_check();
	void launch_hover_check();
};