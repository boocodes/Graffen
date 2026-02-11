#include "global.h"


WindowModule* root_window = new WindowModule();

glm::mat4 font_projection = glm::ortho(
	0.0f, static_cast<float>(root_window->get_window_width()),
	static_cast<float>(root_window->get_window_height()), 0.0f
);

glm::mat4 pixel_placement_projection = glm::ortho(
	0.0f, static_cast<float>(root_window->get_window_width()),
	static_cast<float>(root_window->get_window_height()), 0.0f,
	-100.0f, 100.0f
);

ShaderModule img_display_tag_shader;
ShaderModule div_display_tag_shader;
ShaderModule text_display_tag_shader;
ShaderModule pixel_placement_shader;
ShaderModule button_display_tag_shader;
ShaderModule input_simple_form_tag_shader;

void init_shaders()
{
	try
	{
		std::cout << "init\n";
		img_display_tag_shader.generate("src/2D/static/shaders/gui_display_shaders/img/img.vs", "src/2D/static/shaders/gui_display_shaders/img/img.fs");
		div_display_tag_shader.generate("src/2D/static/shaders/gui_display_shaders/div/div.vs", "src/2D/static/shaders/gui_display_shaders/div/div.fs");
		text_display_tag_shader.generate("src/2D/static/shaders/gui_display_shaders/text/text.vs", "src/2D/static/shaders/gui_display_shaders/text/text.fs");
		button_display_tag_shader.generate("src/2D/static/shaders/gui_display_shaders/button/button.vs", "src/2D/static/shaders/gui_display_shaders/button/button.fs");
		input_simple_form_tag_shader.generate("src/2D/static/shaders/gui_form_shaders/input_simple/input_simple.vs", "src/2D/static/shaders/gui_form_shaders/input_simple/input_simple.fs");
	}
	catch (const std::exception& e)
	{
		
	}
}