#include "div.h"



DivDisplayTag::~DivDisplayTag() 
{
	if (VAO != 0) glDeleteVertexArrays(1, &VAO);
	if (VBO != 0) glDeleteBuffers(1, &VBO);
	if (texture != 0) glDeleteTextures(1, &texture);
};

DivDisplayTag::DivDisplayTag(int x_pos, int y_pos, int z_pos, int width, int height)
{
	this->EBO = 0;
	this->VAO = 0;
	this->VBO = 0;
	this->border_opacity = 1.0f;
	this->border_radius = glm::vec4(0, 0, 0, 0);
	this->texture = 0;
	this->visibility = true;

	this->tag_type = "Div";
	this->self_id = 1; // temporary replacement of ID issuance
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->z_pos = z_pos;
	this->width = width;
	this->height = height;

	this->border_width = glm::vec4(0, 0, 0, 0);
	this->border_color = glm::vec4(0, 0, 0, 0);
	this->background_color = glm::vec4(0, 0, 0, 1);

	this->rebuild_vertex_objects();
	
}


void DivDisplayTag::rebuild_vertex_objects()
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
}

bool DivDisplayTag::click_check(int mouse_x, int mouse_y)
{
	if (
		((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) && 
		((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height))
		)
	{
		std::cout << "clicked from div!" << std::endl;
		this->on_click();
		return true;
	}
	return false;
}

bool DivDisplayTag::hover_check(int mouse_x, int mouse_y)
{
	if (
		((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) &&
		((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height))
		)
	{
		std::cout << "hovered from div!" << std::endl;
		this->on_hover();
		return true;
	}
	return false;
}

void DivDisplayTag::draw()
{
	
	if (!this->visibility) return;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	div_display_tag_shader.use();
	div_display_tag_shader.set_mat4("projection", pixel_placement_projection);
	div_display_tag_shader.set_vec2("size", glm::vec2(this->width, this->height));
	div_display_tag_shader.set_vec2("position", glm::vec2(x_pos, y_pos));
	div_display_tag_shader.set_vec4("color", this->background_color);
	div_display_tag_shader.set_vec4("border_radius", this->border_radius);

	div_display_tag_shader.set_int("border_size", 1);

	div_display_tag_shader.set_float("border_opacity", this->border_opacity);
	div_display_tag_shader.set_float("smoothing", 1.0f);
	div_display_tag_shader.set_vec4("border_width", this->border_width);
	div_display_tag_shader.set_vec4("border_color", this->border_color);


	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
}


void DivDisplayTag::set_border_radius(glm::vec4 new_border_radius)
{
	this->border_radius = new_border_radius;
}

void DivDisplayTag::set_background_color(glm::vec4 new_background_color)
{
	this->background_color = new_background_color;
}

void DivDisplayTag::set_border_width(glm::vec4 new_border_width)
{
	this->border_width = new_border_width;
}

void DivDisplayTag::set_border_color(glm::vec4 new_border_color)
{
	this->border_color = new_border_color;
}

void DivDisplayTag::set_border_opacity(float border_opacity)
{
	this->border_opacity = border_opacity;
}

void DivDisplayTag::set_background_image(const std::string& new_image)
{
	this->background_image = new_image;
}

