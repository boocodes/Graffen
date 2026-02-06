#include "window.h"
#include <iostream>



WindowModule::~WindowModule() {};

WindowModule::WindowModule()
{
	this->mouse_x = 0;
	this->mouse_y = 0;
	this->window = NULL;
	this->window_title = "OpenGL";
	if(!glfwInit())
	{
		return;
	}
	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

	this->window = glfwCreateWindow(500, 600, window_title.c_str(), NULL, NULL);
	this->width = 500;
	this->height = 600;
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);	
	if (!window)
	{
		glfwTerminate();
		return;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}
}


void WindowModule::render()
{
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		std::cout << "x - " << this->mouse_x << ", y - " << this->mouse_y << std::endl;
		glfwPollEvents();
		
	}
}


void WindowModule::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	void* ptr = glfwGetWindowUserPointer(window);
	if (ptr)
	{
		WindowModule* instance = static_cast<WindowModule*>(ptr);
		instance->set_mouse_pos(static_cast<int>(xpos), static_cast<int>(ypos));
	}
}

// setters
void WindowModule::set_mouse_pos(int mouse_x, int mouse_y)
{
	this->mouse_x = mouse_x;
	this->mouse_y = mouse_y;
}
void WindowModule::set_window_title(const std::string& window_title)
{
	this->window_title = window_title;
}
void WindowModule::set_window_width(int width)
{
	this->width = width;
}
void WindowModule::set_window_height(int height)
{
	this->height = height;
}
//
int WindowModule::get_mouse_x()
{
	return this->mouse_x;
}
int WindowModule::get_mouse_y()
{
	return this->mouse_y;
}
std::string WindowModule::get_window_title()
{
	return this->window_title;
}
int WindowModule::get_window_width()
{
	return this->width;
}
int WindowModule::get_window_height()
{
	return this->height;
}

