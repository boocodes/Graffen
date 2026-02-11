#include "text.h"


TextDisplayTag::TextDisplayTag() {};
TextDisplayTag::TextDisplayTag(int x_pos, int y_pos, int z_pos, std::string font_name, std::string text_display)
{
	this->tag_type = "Text";
	this->x_pos = x_pos;
	this->y_pos = y_pos;
	this->z_pos = z_pos;
	this->color = color;
	this->font_size = 16;
	this->color = glm::vec3(0, 0, 0);
	this->font_name = font_name;
	this->text_display = text_display;
	this->line_height = 1.5f;
	this->visibility = true;
	this->max_width = 0.0f;
	this->word_wrap = false;

	this->font.init(this->font_name, this->font_size);
}

void TextDisplayTag::draw()
{
	if (!this->visibility || this->text_display.empty())
		return;
	if (!word_wrap || max_width <= 0)
	{
		this->font.draw_text(this->text_display, this->x_pos, this->y_pos, this->color);
		return;
	}
	auto lines = get_wrapped_lines(this->text_display);
	float actual_line_height = get_actual_line_height();
	float current_y = this->y_pos;

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	text_display_tag_shader.use();
	text_display_tag_shader.set_mat4("projection", font_projection);
	text_display_tag_shader.set_vec3("text_color", this->color);
	text_display_tag_shader.set_float("z_index", 0.0);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->font.VAO);

	for (size_t i = 0; i < lines.size(); i++)
	{
		const auto& line = lines[i];
		float current_x = this->x_pos;

		// Ðåíäåðèì ñèìâîëû ñòðîêè
		for (char c : line)
		{
			if (c == ' ' && current_x == this->x_pos)
				continue;

			Character ch = this->font.Characters[c];
			float x_pos = current_x + ch.Bearing.x;

			float y_pos;
			if (i == 0)
			{
				y_pos = current_y + (this->font.Characters['H'].Bearing.y - ch.Bearing.y);
			}
			else
			{
				y_pos = current_y + (this->font.Characters['H'].Bearing.y - ch.Bearing.y);
			}

			float w = ch.Size.x;
			float h = ch.Size.y;

			float vertices[6][4] = {
				{ x_pos,     y_pos + h,   0.0f, 1.0f },
				{ x_pos + w, y_pos,       1.0f, 0.0f },
				{ x_pos,     y_pos,       0.0f, 0.0f },
				{ x_pos,     y_pos + h,   0.0f, 1.0f },
				{ x_pos + w, y_pos + h,   1.0f, 1.0f },
				{ x_pos + w, y_pos,       1.0f, 0.0f }
			};

			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			glBindBuffer(GL_ARRAY_BUFFER, this->font.VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			current_x += (ch.Advance >> 6);
		}

		if (i == 0)
		{
			current_y += actual_line_height;
		}
		else
		{
			current_y += actual_line_height;
		}
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

std::string TextDisplayTag::get_font_name()
{
	return this->font_name;
}

std::string TextDisplayTag::get_text_display()
{
	return this->text_display;
}

void TextDisplayTag::change_text(std::string new_text)
{
	this->text_display = new_text;
}

void TextDisplayTag::change_font(std::string new_font)
{
	this->font_name = new_font;
	FontModule buffFont;
	buffFont.init(this->font_name, this->font_size);
	this->font = buffFont;
}

void TextDisplayTag::change_font_size(int new_font_size)
{
	this->font_size = new_font_size;
	FontModule buffFont;
	buffFont.init(this->font_name, this->font_size);
	this->font = buffFont;
}

bool TextDisplayTag::hover_check(int mouse_x, int mouse_y)
{
	return false;
	if (
		((mouse_x >= this->x_pos) && (mouse_x <= this->x_pos + this->width)) &&
		((mouse_y >= this->y_pos) && (mouse_y <= this->y_pos + this->height))
		)
	{
		std::cout << "hovered from text!" << std::endl;
		this->on_hover();
		return true;
	}
	
}

bool TextDisplayTag::click_check(int mouse_x, int mouse_y)
{
	return false;
}

void TextDisplayTag::set_max_width(float width)
{
	this->max_width = width;
	this->word_wrap = (width > 0);
}

void TextDisplayTag::set_word_wrap(bool wrap)
{
	this->word_wrap = wrap;
}

float TextDisplayTag::get_actual_line_height()
{
	return this->font.get_text_height() * this->line_height;
}

std::vector<std::string> TextDisplayTag::get_wrapped_lines(const std::string& text)
{
	std::vector<std::string> lines;
	if (!word_wrap || max_width <= 0)
	{
		lines.push_back(text);
		return lines;
	}
	else
	{
		std::stringstream ss(text);
		std::string word;
		std::string current_lines;
		float current_line_width = 0.0f;

		while (ss >> word)
		{
			float word_width = font.get_text_width(word + " ");
			if (current_line_width + word_width <= max_width || current_lines.empty())
			{
				current_lines += word + " ";
				current_line_width += word_width;
			}
			else
			{
				if (!current_lines.empty())
				{
					lines.push_back(current_lines);
				}
				current_lines = word + " ";
				current_line_width = word_width;
			}
		}

		if (!current_lines.empty())
		{
			lines.push_back(current_lines);
		}
		if (lines.empty() && !text.empty())
		{
			std::string current_word;
			float char_width = 0.0f;
			for (char c : text)
			{
				if (font.get_text_width(current_word + c) > max_width && !current_word.empty())
				{
					lines.push_back(current_word);
					current_word = "";
				}
				current_word += c;
			}
			if (!current_word.empty())
			{
				lines.push_back(current_word);
			}
		}
		return lines;
	}
}

glm::vec2 TextDisplayTag::get_wrapper_text_size(const std::string& text)
{
	auto lines = this->get_wrapped_lines(text);
	float max_line_width = 0.0f;
	float actual_line_height = get_actual_line_height();

	for (const auto& line : lines)
	{
		float line_width = font.get_text_width(line);
		if (line_width > max_line_width)
		{
			max_line_width = line_width;
		}
	}

	float total_height = 0.0f;
	if (!lines.empty())
	{
		total_height = font.get_text_height() + (lines.size() - 1) * actual_line_height;
	}
	return glm::vec2(max_line_width, total_height);
}

FontModule::FontModule()
{
}

void FontModule::draw_text(std::string text_display, float x_pos, float y_pos, glm::vec3 color)
{
	int scale = 1;
	if (text_display.size() == 0)
		text_display = std::to_string(this->id);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	text_display_tag_shader.use();
	text_display_tag_shader.set_mat4("projection", font_projection);
	text_display_tag_shader.set_vec3("text_color", color);
	text_display_tag_shader.set_float("z_index", 0.0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);
	std::string::const_iterator c;
	for (c = text_display.begin(); c != text_display.end(); c++)
	{
		Character ch = Characters[*c];
		float xpos = x_pos + ch.Bearing.x * scale;
		float ypos = y_pos + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 0.0f },

			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x_pos += (ch.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void FontModule::init(std::string font_name, int pixel_size_px)
{
	this->pixel_size_px = pixel_size_px;
	this->font_name = font_name;
	text_display_tag_shader.use();
	text_display_tag_shader.set_mat4("projection", font_projection);
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}

	if (this->font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
		return;
	}

	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	else {
		FT_Set_Pixel_Sizes(face, 0, this->pixel_size_px);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (unsigned int c = 0; c < 256; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			glGenTextures(1, &this->texture);
			glBindTexture(GL_TEXTURE_2D, this->texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

float FontModule::get_text_width(const std::string& text)
{
	float result_width = 0.0f;

	for (char c : text)
	{
		if (Characters.find(c) != Characters.end())
		{
			Character ch = Characters.at(c);
			result_width += (ch.Advance >> 6);
		}
	}

	return result_width;
}

float FontModule::get_text_height()
{
	if (Characters.find('H') != Characters.end())
	{
		return Characters.at('H').Size.y;
	}
	else if (Characters.find('A') != Characters.end())
	{
		return Characters.at('A').Size.y;
	}

	if (!Characters.empty())
	{
		return Characters.begin()->second.Size.y;
	}
	return this->pixel_size_px;
}

glm::vec2 FontModule::get_text_size(const std::string& text)
{
	return glm::vec2(get_text_width(text), get_text_height());
}
