#include "document_tag.h"


DocumentTag::DocumentTag()
{

}

void DocumentTag::add_tag(RootTag* tag)
{
	this->tagsList.push_back(tag);
}

void DocumentTag::render()
{

	for (auto i : this->tagsList)
	{
		i->draw();
	}
}

void DocumentTag::check_click(int mouseX, int mouseY)
{
	for (auto i : this->tagsList)
	{
		i->clickCheck(mouseX, mouseY);
	}
}