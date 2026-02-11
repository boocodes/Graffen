#include "input_simple.h"

InputSimpleFormTag::~InputSimpleFormTag() {};
InputSimpleFormTag::InputSimpleFormTag(int x_pos, int y_pos, int z_pos, int width, int height)
{
	this->tag_type = "Input";
	this->border_color = glm::vec4(0, 0, 0, 0);
	this->border_width = glm::vec4(0, 0, 0, 0);
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

	this->text_tag = new TextDisplayTag(this->x_pos, this->y_pos, this->z_pos, "assets/fonts/JetBrainsMono-Regular.ttf", this->input_form_value);
	int text_tag_height = this->text_tag->get_wrapper_text_size(this->input_form_value).y;
	int text_tag_width = this->text_tag->get_wrapper_text_size(this->input_form_value).x;

	this->text_tag = new TextDisplayTag(this->x_pos + ((this->width - text_tag_width) / 2), this->y_pos + ((this->height - text_tag_height) / 2), this->text_tag->get_z_pos(), this->text_tag->get_font_name(), this->text_tag->get_text_display());

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
	input_simple_form_tag_shader.set_vec4("borderRadius", this->border_radius);

	input_simple_form_tag_shader.set_int("borderSize", 1);

	input_simple_form_tag_shader.set_float("borderOpacity", this->border_opacity);
	input_simple_form_tag_shader.set_float("smoothing", 1.0f);
	input_simple_form_tag_shader.set_vec4("borderWidth", this->border_width);
	input_simple_form_tag_shader.set_vec4("borderColor", this->border_color);
	

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
		std::cout << "from input!" << std::endl;
		this->is_active = true;
		return true;
	}
	return false;
}

bool InputSimpleFormTag::click_check(int mouse_x, int mouse_y)
{
	return false;
}




