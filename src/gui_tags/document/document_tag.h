#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <gui_tags/root/root_tag.h>



class DocumentTag {
public:
	std::string xmlFilePath;
	std::string cssFilePath;
	int layoutRowsCount;
	int pxLayoutLastRow;
	std::vector<RootTag*> tagsList;
	void render();
	void add_tag(RootTag* tag);
	void check_click(int mouseX, int mouseY);
	DocumentTag();
};