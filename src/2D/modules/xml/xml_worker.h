#pragma once
#include <2D/gui_tags/display/display_tags_container/display_tags_container.h>
#include <2D/gui_tags/form/form_tags_container/form_tags_container.h>
#include <tinyxml2.h>


class XMLWorker
{
private:
	DisplayTagsContainer displayContainer;
	FormTagsContainer formContainer;
public:
	XMLWorker();
	void parse_xml(const std::string& xml_path);
};