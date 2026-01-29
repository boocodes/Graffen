#include "form_tag.h"




FormTag::FormTag()
{

}

void FormTag::render()
{
	for (auto i : this->input_list)
	{
		i->draw();
	}
}

void FormTag::add_element(InputTag* tag)
{
	this->input_list.push_back(tag);
}


void FormTag::check_click(int mouseX, int mouseY)
{
	for (auto i : this->input_list)
	{
		i->clickCheck(mouseX, mouseY);
	}
}

void FormTag::disable_all_inputs()
{
	for (auto i : this->input_list)
	{
		i->is_active = false;
	}
}