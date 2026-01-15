#pragma once
#pragma once
#include <string>
#include <tinyxml2.h>
#include <vector>
#include <gui_tags/root/root_tag.h>
#include <module/util/util_module.h>
#include <gui_tags/p/p_tag.h>
#include <gui_tags/img/img_tag.h>
#include <gui_tags/div/div_tag.h>


class XmlModule
{
public:
	XmlModule();
	static void parseXml(const std::string& xmlPath, std::vector<RootTag*>& tagsList, std::string& cssFilePath);
};