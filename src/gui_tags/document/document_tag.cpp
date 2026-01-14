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