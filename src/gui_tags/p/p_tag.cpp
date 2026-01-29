#include "p_tag.h"


PTag::PTag(int xPos, int yPos, glm::vec3 color, int fontSize, std::string fontName, std::string textDisplay, int zIndex)
{
	this->tagType = "Text";
	this->xPos = xPos;
	this->yPos = yPos;
	this->color = color;
	this->fontSize = fontSize;
	this->fontName = fontName;
	this->textDisplay = textDisplay;
	this->zIndex = zIndex;
	this->line_height = 1.5f;
	this->visibility = true;
	this->max_width = 0.0f;
	this->word_wrap = false;

	this->font.init(this->fontName, this->fontSize);
}


void PTag::draw()
{
	if (!this->visibility || this->textDisplay.empty())
		return;

	if (!word_wrap || max_width <= 0)
	{
		this->font.draw_text(this->textDisplay, this->xPos, this->yPos, this->color);
		return;
	}

	auto lines = get_wrapped_lines(this->textDisplay);
	float actual_line_height = get_actual_line_height();
	float current_y = this->yPos;

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	fontShader.use();
	fontShader.setMat4("projection", fontProjection);
	fontShader.setVec3("textColor", this->color);
	fontShader.setFloat("z_index", 0.0);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->font.VAO);

	// Рендерим каждую строку
	for (size_t i = 0; i < lines.size(); i++)
	{
		const auto& line = lines[i];
		float current_x = this->xPos;

		// Рендерим символы строки
		for (char c : line)
		{
			if (c == ' ' && current_x == this->xPos)
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


void PTag::set_max_width(float width)
{
	this->max_width = width;
	this->word_wrap = (width > 0);
}

void PTag::set_word_wrap(bool flag)
{
	this->word_wrap = flag;
}

std::vector<std::string> PTag::get_wrapped_lines(const std::string& text)
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

float PTag::get_actual_line_height()
{
	return this->font.get_text_height() * this->line_height;
}

glm::vec2 PTag::get_wrapper_text_size(const std::string& text)
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





bool PTag::hoverCheck(int mouseX, int mouseY)
{
	return true;
}
bool PTag::clickCheck(int mouseX, int mouseY)
{
	return true;
}
void PTag::changeText(std::string newText)
{
	this->textDisplay = newText;
}
void PTag::changeFontSize(int newFontSize)
{
	this->fontSize = newFontSize;
	FontModule buffFont;
	buffFont.init(this->fontName, this->fontSize);
	this->font = buffFont;
}
void PTag::changeFont(std::string newFont)
{
	this->fontName = newFont;
	FontModule buffFont;
	buffFont.init(this->fontName, this->fontSize);
	this->font = buffFont;
}



void PTag::center_x(int parent_width)
{
	glm::vec2 textSize;

	if (word_wrap && max_width > 0)
	{
		textSize = get_wrapper_text_size(this->textDisplay);
	}
	else
	{
		textSize = glm::vec2(
			this->font.get_text_width(this->textDisplay),
			this->font.get_text_height()
		);
	}

	if (textSize.x >= parent_width)
	{
		return;
	}

	this->xPos = (parent_width - static_cast<int>(textSize.x)) / 2;
}


void PTag::center_y(int parent_height)
{

}