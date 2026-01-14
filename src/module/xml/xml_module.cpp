#include "xml_module.h"


XmlModule::XmlModule()
{

}


void XmlModule::parseXml(const std::string& xmlPath, std::vector<RootTag*>& tagsListRoot, std::string& cssFilePath)
{
    std::vector<RootTag*> tagsList;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile(xmlPath.c_str());

    if (result != tinyxml2::XML_SUCCESS)
    {
        return;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("Document");
    if (!root)
    {
        return;
    }

    cssFilePath = root->Attribute("style");

    std::function<void(tinyxml2::XMLElement*, DivTag*)> processElement;
    processElement = [&](tinyxml2::XMLElement* element, DivTag* parent) {
            const char* tagName = element->Value();
            if (strcmp(tagName, "Document") == 0)
            {

            }
            else if (strcmp(tagName, "p") == 0)
            {
           
            }
            else if (strcmp(tagName, "div") == 0)
            {
            
            }
            else if (strcmp(tagName, "img") == 0)
            {
            
            }
        };
    for (tinyxml2::XMLElement* element = root->FirstChildElement();
        element != nullptr;
        element = element->NextSiblingElement())
    {
        processElement(element, nullptr);
    }

    tagsListRoot = tagsList;


}