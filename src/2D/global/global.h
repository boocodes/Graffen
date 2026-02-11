	#pragma once
#include <2D/modules/window/window.h>
#include <glm/glm.hpp>
#include <2D/modules/shader/shader.h>
#include <glm/gtc/matrix_transform.hpp>

extern WindowModule* root_window;


extern glm::mat4 pixel_placement_projection;
extern glm::mat4 font_projection;

// ------------------------------------------------------------

extern ShaderModule pixel_placement_shader;

extern ShaderModule img_display_tag_shader;
extern ShaderModule div_display_tag_shader;

extern ShaderModule text_display_tag_shader;
extern ShaderModule button_display_tag_shader;

extern ShaderModule input_simple_form_tag_shader;

void init_shaders();