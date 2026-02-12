#include "button.h"
#include <Windows.h>

ButtonDisplayTag::~ButtonDisplayTag() {};


bool ButtonDisplayTag::hover_check(int mouse_x, int mouse_y)
{
	if (
		((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) &&
		((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height))
		)
	{
		glfwSetCursor(root_window->get_window(), this->active_cursor);
		//std::cout << "hovered from button!" << std::endl;
		this->on_hover();
		return true;
	}
	glfwSetCursor(root_window->get_window(), NULL);
	return false;
};
bool ButtonDisplayTag::click_check(int mouse_x, int mouse_y)
{
	int time_delation_debounce = 10;

	static auto last_call = std::chrono::steady_clock::now();
	auto now = std::chrono::steady_clock::now();

	if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_call).count() < time_delation_debounce) {
		return false;
	}
	if (
		((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) &&
		((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height))
		)
	{
		std::thread([this]()
			{
				if (this->on_click)
				{
					this->on_click();
				}
				
			}).detach();
	}
	return false;
};


ButtonDisplayTag::ButtonDisplayTag(int x_pos, int y_pos, int z_pos, const std::string& text)
{
	this->tag_type = "Button";
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->z_pos = z_pos;
	this->display_text = text;
	this->border_color = glm::vec4(0.9, 0.9, 0.9, 1);
	this->border_width = glm::vec4(2, 2, 2, 2);
	this->background_color = glm::vec4(1, 1, 1, 1);
	this->button_text = new TextDisplayTag(this->x_pos, this->y_pos, this->z_pos, "assets/fonts/JetBrainsMono-Regular.ttf", this->display_text);
	this->visibility = true;
	this->padding = glm::vec4(0, 0, 0, 0);
	this->on_click = []()
		{
			std::cout << "clicked from inner function onclick\n";
			return;
		};
	this->on_hover = []()
		{
			return;
		};

	active_cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

	int button_text_height = this->button_text->get_wrapper_text_size(this->display_text).y;
	int button_text_width = this->button_text->get_wrapper_text_size(this->display_text).x;

	this->width = button_text_width;
	this->height = button_text_height;

	this->rebuild_vertex_objects();
}


void ButtonDisplayTag::draw()
{
	if (!this->visibility) return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	button_display_tag_shader.use();
	button_display_tag_shader.set_mat4("projection", pixel_placement_projection);
	button_display_tag_shader.set_vec2("size", glm::vec2(this->width, this->height));
	button_display_tag_shader.set_vec2("position", glm::vec2(this->x_pos, this->y_pos));
	button_display_tag_shader.set_vec4("color", this->background_color);
	button_display_tag_shader.set_vec4("border_radius", this->border_radius);
	button_display_tag_shader.set_int("border_size", 1);
	button_display_tag_shader.set_float("border_opacity", this->border_opacity);
	button_display_tag_shader.set_float("smoothing", 1.0f);
	button_display_tag_shader.set_vec4("border_width", this->border_width);
	button_display_tag_shader.set_vec4("border_color", this->border_color);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
	glDisable(GL_BLEND);

	this->button_text->draw();
}


void ButtonDisplayTag::rebuild_vertex_objects()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	float new_coords[12] =
	{
		this->x_pos,               this->y_pos + this->height, this->z_pos,
		this->x_pos + this->width, this->y_pos + this->height, this->z_pos,
		this->x_pos + this->width, this->y_pos,                this->z_pos,
		this->x_pos,               this->y_pos,                this->z_pos,
	};

	for (size_t i = 0; i < 12; i++)
	{
		this->coords[i] = new_coords[i];
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coords), this->coords, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	int button_text_height = this->button_text->get_wrapper_text_size(this->display_text).y;
	int button_text_width = this->button_text->get_wrapper_text_size(this->display_text).x;

	this->button_text = new TextDisplayTag(this->x_pos + ((this->width - button_text_width) / 2), this->y_pos + ((this->height - button_text_height) / 2), this->button_text->get_z_pos(), this->button_text->get_font_name(), this->button_text->get_text_display());
}




void ButtonDisplayTag::set_border_radius(glm::vec4 new_border_radius)
{
	this->border_radius = new_border_radius;
}
void ButtonDisplayTag::set_background_color(glm::vec4 new_background_color)
{
	this->background_color = new_background_color;
}

void ButtonDisplayTag::set_border_width(glm::vec4 new_border_width)
{
	this->border_width = new_border_width;
}

void ButtonDisplayTag::set_border_color(glm::vec4 new_border_color)
{
	this->border_color = new_border_color;
}

void ButtonDisplayTag::set_border_opacity(float border_opacity)
{
	this->border_opacity = border_opacity;
}

void ButtonDisplayTag::set_background_image(const std::string& new_image)
{
	this->background_image = new_image;
}

void ButtonDisplayTag::set_padding(glm::vec4 new_padding)
{
	this->padding = new_padding;
}

void ButtonDisplayTag::set_height(int new_height)
{
	this->height = new_height;
	this->rebuild_vertex_objects();
}

void ButtonDisplayTag::set_width(int new_width)
{
	this->width = new_width;
	this->rebuild_vertex_objects();
}

void ButtonDisplayTag::set_size(int new_width, int new_height)
{
	this->width = new_width;
	this->height = new_height;
	this->rebuild_vertex_objects();
}

void ButtonDisplayTag::set_z(int z)
{
	this->z_pos = z;
	this->rebuild_vertex_objects();
}


