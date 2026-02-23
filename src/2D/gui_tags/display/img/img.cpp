#include "img.h"

ImgDisplayTag::~ImgDisplayTag() {};

ImgDisplayTag::ImgDisplayTag(int x_pos, int y_pos, int z_pos, const std::string& image)
{
	this->image = image;
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->self_id = IdGenerator::next();
	this->z_pos = z_pos;
	this->self_id = 1;
	this->tag_type = "Img";
	this->visibility = true;

	this->border_radius = glm::vec4(0, 0, 0, 0);
	this->texture_entity = UtilModule::get_texture(image.c_str());
	this->width = texture_entity.width;
	this->height = texture_entity.height;
	this->rebuild_vertex_objects();
}


void ImgDisplayTag::rebuild_vertex_objects()
{
	
	float new_coords[32] =
	{
		this->x_pos,               this->y_pos + this->height, this->z_pos, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		this->x_pos + this->width, this->y_pos + this->height, this->z_pos, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		this->x_pos + this->width, this->y_pos,                this->z_pos, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		this->x_pos,               this->y_pos,                this->z_pos, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

	};
	for (size_t i = 0; i < 32; i++)
	{
		this->coords[i] = new_coords[i];
	}

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->coords), this->coords, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void ImgDisplayTag::draw()
{
	if (!this->visibility) return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture_entity.texture);
	img_display_tag_shader.use();
	img_display_tag_shader.set_mat4("projection", pixel_placement_projection);
	img_display_tag_shader.set_int("texture1", 0);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void ImgDisplayTag::change_image(const std::string& new_image)
{
	this->texture_entity = UtilModule::get_texture(new_image.c_str());
	this->width = texture_entity.width;
	this->height = texture_entity.height;
	this->rebuild_vertex_objects();
}

void ImgDisplayTag::set_height(int new_height)
{
	this->height = new_height;
	this->rebuild_vertex_objects();
}

void ImgDisplayTag::set_width(int new_width)
{
	this->width = new_width;
	this->rebuild_vertex_objects();
}

void ImgDisplayTag::set_size(int new_width, int new_height)
{
	this->width = new_width;
	this->height = new_height;
	this->rebuild_vertex_objects();
}

void ImgDisplayTag::set_z(int z)
{
	this->z_pos = z;
	this->rebuild_vertex_objects();
}

bool ImgDisplayTag::hover_check(int mouse_x, int mouse_y)
{
	if (((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) && ((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height)))
	{
		return true;
	}
	return false;
}

bool ImgDisplayTag::click_check(int mouse_x, int mouse_y)
{
	if (((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) && ((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height)))
	{
		return true;
	}
	return false;
}