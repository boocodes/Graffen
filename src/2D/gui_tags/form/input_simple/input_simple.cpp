#include "input_simple.h"

InputSimpleFormTag::~InputSimpleFormTag() {};
void InputSimpleFormTag::set_border_width(glm::vec4 new_border_width)
{
	this->border_width = new_border_width;
}
void InputSimpleFormTag::set_border_radius(glm::vec4 new_border_radius)
{
	this->border_radius = new_border_radius;
}
void InputSimpleFormTag::set_background_color(glm::vec4 new_background_color)
{
	this->background_color = new_background_color;
}
void InputSimpleFormTag::set_border_opacity(float border_opacity)
{
	this->border_opacity = border_opacity;
}
void InputSimpleFormTag::set_border_color(glm::vec4 new_border_color)
{
	this->border_color = new_border_color;
}
InputSimpleFormTag::InputSimpleFormTag(int x_pos, int y_pos, int z_pos, int width, int height)
{
	this->background_color = glm::vec4(1, 1, 1, 1);
	this->border_opacity = 1.0f;
	this->tag_type = "Input";
	this->border_color = glm::vec4(0, 0, 0, 0);
	this->border_width = glm::vec4(0, 0, 0, 0);
	this->self_id = IdGenerator::next();
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->z_pos = z_pos;
	this->width = width;
	this->height = height;
	this->background_img = "";
	this->border_radius = glm::vec4(0, 0, 0, 0);
	this->class_name = "";
	this->input_form_value = "hellow";
	this->is_active = false;
	this->opacity = 1.0f;
	this->visibility = true;
	this->self_id = 1;
	this->VAO = 0;
	this->VBO = 0;
	this->texture = 0;
	this->placeholder = "";
	this->active_cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
	this->text_tag = new TextDisplayTag(this->x_pos, this->y_pos, this->z_pos, "assets/fonts/JetBrainsMono-Regular.ttf", this->input_form_value);
	int text_tag_height = this->text_tag->get_wrapper_text_size(this->input_form_value).y;
	int text_tag_width = this->text_tag->get_wrapper_text_size(this->input_form_value).x;

	this->text_tag = new TextDisplayTag(this->x_pos + ((this->width - text_tag_width) / 2), this->y_pos + ((this->height - text_tag_height) / 2), this->text_tag->get_z_pos(), this->text_tag->get_font_name(), this->text_tag->get_text_display());
	this->rebuild_vertex_objects();
};

void InputSimpleFormTag::draw()
{
	if (!this->visibility) return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	input_simple_form_tag_shader.use();
	input_simple_form_tag_shader.set_mat4("projection", pixel_placement_projection);
	input_simple_form_tag_shader.set_vec2("size", glm::vec2(this->width, this->height));
	input_simple_form_tag_shader.set_vec2("position", glm::vec2(x_pos, y_pos));
	input_simple_form_tag_shader.set_vec4("color", this->background_color);
	input_simple_form_tag_shader.set_vec4("border_radius", this->border_radius);

	input_simple_form_tag_shader.set_int("border_size", 1);

	input_simple_form_tag_shader.set_float("border_opacity", this->border_opacity);
	input_simple_form_tag_shader.set_float("smoothing", 1.0f);
	input_simple_form_tag_shader.set_vec4("border_width", this->border_width);
	input_simple_form_tag_shader.set_vec4("border_color", this->border_color);
	

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
	glDisable(GL_BLEND);

	this->text_tag->draw();
}

bool InputSimpleFormTag::hover_check(int mouse_x, int mouse_y)
{
	if (((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) && ((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height)))
	{
		glfwSetCursor(root_window->get_window(), this->active_cursor);
		
		return true;
	}
	return false;
}

bool InputSimpleFormTag::click_check(int mouse_x, int mouse_y)
{
	if (((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) && ((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height)))
	{
		this->is_active = true;
		return true;
	}
	return false;
}


void InputSimpleFormTag::set_value(const std::string& new_value)
{
	if (new_value.length() > this->max_input_size) return;
	this->input_form_value = new_value;
	this->text_tag->change_text(this->input_form_value);
	this->rebuild_vertex_objects();
}

void InputSimpleFormTag::center_x(int root_container_width)
{
	this->x_pos = (root_container_width - this->width) / 2;
	this->rebuild_vertex_objects();
}

void InputSimpleFormTag::set_font_color(glm::vec3 new_font_color)
{
	this->text_tag->set_color(new_font_color);
}

void InputSimpleFormTag::set_height(int new_height)
{
	this->height = new_height;
	this->rebuild_vertex_objects();
}

void InputSimpleFormTag::set_width(int new_width)
{
	this->width = new_width;
	this->rebuild_vertex_objects();
}

void InputSimpleFormTag::set_size(int new_width, int new_height)
{
	this->width = new_width;
	this->height = new_height;
	this->rebuild_vertex_objects();
}

void InputSimpleFormTag::set_z(int z)
{
	this->z_pos = z;
	this->rebuild_vertex_objects();
}


void InputSimpleFormTag::rebuild_vertex_objects()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	float new_coords[12] = {
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

	if (this->text_align == "left")
	{
		this->text_tag->set_x_pos(this->x_pos);
	}
	else
	{
		this->text_tag->set_x_pos(this->x_pos + (this->width - this->text_tag->get_wrapper_text_size(this->text_tag->get_text_display()).x) / 2);
	}
	
}

void InputSimpleFormTag::set_text_align(const std::string& align)
{
	if (align == "left") this->text_align = "left";
	else if (align == "right") this->text_align = "right";
	else if (align == "top") this->text_align = "top";
	else if (align == "botton") this->text_align = "bottom";
	this->rebuild_vertex_objects();
}

void InputSimpleFormTag::set_x_pos(int new_x_pos)
{
	this->x_pos = new_x_pos;
	this->rebuild_vertex_objects();
}

void InputSimpleFormTag::set_max_input_size(int max_size)
{
	this->max_input_size = max_size;
}
