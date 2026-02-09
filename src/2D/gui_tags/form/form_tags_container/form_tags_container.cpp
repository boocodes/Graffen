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