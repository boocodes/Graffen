#include "form_tags_container.h"

void FormTagsContainer::add_tag(RootFormTag* tag)
{
	auto pos = std::lower_bound(this->tags.begin(), this->tags.end(), tag,
		[](RootFormTag* a, RootFormTag* b) {
			return a->get_z_pos() < b->get_z_pos();
		});
	this->tags.insert(pos, tag);
}

FormTagsContainer::FormTagsContainer() {};


void FormTagsContainer::draw()
{
	for (auto elem : this->tags)
	{
		elem->draw();
	}
}


void FormTagsContainer::log_inner_data()
{
	std::cout << "Form tags container. " << std::endl;
	std::cout << "Tags list size: " << this->tags.size() << std::endl;
	for (auto tag : this->tags)
	{
		std::cout << "Tag: " << tag->get_tag_type() << std::endl;
		std::cout << "Z pos: " << tag->get_z_pos() << std::endl;
	}
}

void FormTagsContainer::update_value(char new_char, RootFormTag* active_form_elem)
{
	active_form_elem->set_value(std::to_string(new_char));
}

void FormTagsContainer::run_click(int mouse_x, int mouse_y)
{
	this->disable_all_form_tags();
	for (auto tag : this->tags)
	{
		tag->click_check(mouse_x, mouse_y);
	}
}
void FormTagsContainer::run_hover(int mouse_x, int mouse_y)
{
	for (auto tag : this->tags)
	{
		tag->hover_check(mouse_x, mouse_y);
	}
}

void FormTagsContainer::disable_all_form_tags()
{
	for (auto elem : this->tags)
	{
		elem->set_active_flag(false);
	}
}

void FormTagsContainer::get_keyboard_char(char input_char)
{
	for (auto elem : this->tags)
	{
		if (elem->get_active_flag())
		{
			elem->set_value(elem->get_input_value() + input_char);
		}
	}
}

void FormTagsContainer::get_special_key(int action, int key)
{
	for (auto elem : this->tags)
	{
		if (!elem->get_active_flag()) continue;

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
				case GLFW_KEY_BACKSPACE:
					
					if (!elem->get_input_value().empty())
					{
						elem->set_value(elem->get_input_value().substr(0, elem->get_input_value().size() - 1));
					}
			}
		}
	}
}
