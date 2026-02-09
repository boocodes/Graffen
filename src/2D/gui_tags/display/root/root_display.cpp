#include "root_display.h"



int RootDisplayTag::get_self_id()
{
	return this->self_id;
}

int RootDisplayTag::get_z_pos()
{
	return this->z_pos;
}
int RootDisplayTag::get_x_pos()
{
	return this->x_pos;
}
int RootDisplayTag::get_y_pos()
{
	return this->y_pos;
}
std::string RootDisplayTag::get_tag_type()
{
	return this->tag_type;
}