#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>



class WindowModule
{
private:
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);


	std::string window_title;
	GLFWwindow* window;
	int mouse_x,
		mouse_y;
	int width,
		height;
public:
	// setters
	void set_window_width(int width);
	void set_window_height(int height);
	void set_mouse_pos(int mouse_x, int mouse_y);
	void set_window_title(const std::string& window_title);
	// 
	// getters
	int get_window_width();
	int get_window_height();
	int get_mouse_x();
	int get_mouse_y();
	std::string get_window_title();
	//
	WindowModule();
	~WindowModule();
	void render();
};