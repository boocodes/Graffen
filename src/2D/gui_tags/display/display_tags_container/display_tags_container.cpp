	#include "display_tags_container.h"


	DisplayTagsContainer::DisplayTagsContainer() {};

	DisplayTagsContainer::DisplayTagsContainer(std::vector<RootDisplayTag*> tags)
	{
		this->tags = tags;
	}

	void DisplayTagsContainer::add_tag(RootDisplayTag* tag)
	{

		auto pos = std::lower_bound(this->tags.begin(), this->tags.end(), tag,
			[](RootDisplayTag* a, RootDisplayTag* b) {
				return a->get_z_pos() < b->get_z_pos();
			});
		this->tags.insert(pos, tag);
		this->tags.insert(pos, tag);
	}

	void DisplayTagsContainer::run_click(int mouse_x, int mouse_y)
	{
		for (auto tag : this->tags)
		{
			tag->click_check(mouse_x, mouse_y);
		}
	}

	void DisplayTagsContainer::draw()
	{
		std::cout << "drawing container" << ". Size - " << this->tags.size() << std::endl;
		for (auto tag : this->tags)
		{
			tag->draw();
		}
	}

	void DisplayTagsContainer::log_inner_data()
	{
		std::cout << "Display tags container. " << std::endl;
		std::cout << "Tags list size: " << this->tags.size() << std::endl;
		for (auto tag : this->tags)
		{
			std::cout << "Tag: " << tag->get_tag_type() << std::endl;
			std::cout << "Z pos: " << tag->get_z_pos() << std::endl;
		}
	}