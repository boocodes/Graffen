#include "font_module.h"
#include <global/global.h>



void FontModule::draw_text(std::string text_display, float x_pos, float y_pos, glm::vec3 color)
{
	int scale = 1;
	if (text_display.size() == 0)
		text_display = std::to_string(this->id);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	fontShader.use();
	fontShader.setMat4("projection", fontProjection);
	fontShader.setVec3("textColor", color);
	fontShader.setFloat("z_index", 0.0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);
	std::string::const_iterator c;
	int simple_text_counter = 0;
	for (c = text_display.begin(); c != text_display.end(); c++, simple_text_counter++)
	{
		/*std::cout << (*c == '\n') << std::endl;*/
		Character ch = Characters[*c];	
		float xpos = x_pos + ch.Bearing.x * scale;
		float ypos = y_pos + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		// Обновляем VBO для каждого символа
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 0.0f },

			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f }
		};

		// Рендерим на прямоугольник текстуру глифа
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Обновляем содержимое памяти VBO
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // обязательно используйте glBufferSubData, а не glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Рендерим прямоугольник
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Теперь смещаем курсор к следующему глифу
		x_pos += (ch.Advance >> 6) * scale; // битовый сдвиг на 6, чтобы получить значение в пикселя (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}
FontModule::FontModule()
{

}

void FontModule::init(std::string font_name, int pixel_size_px)
{
	this->pixel_size_px = pixel_size_px;
	this->font_name = font_name;
	fontShader.use();
	fontShader.setMat4("projection", fontProjection);
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