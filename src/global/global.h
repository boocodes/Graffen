#pragma once
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <module/shader/shader_module.h>
#include <string>

extern int WIDTH;
extern int HEIGHT;
extern std::string WINDOW_TITLE;

extern int MOUSE_X_POS;
extern int MOUSE_Y_POS;

extern glm::mat4 imageProjection;
extern glm::mat4 fontProjection;
extern glm::mat4 pixelPlacementProjection;



extern ShaderModule imageShader;
extern ShaderModule fontShader;
extern ShaderModule pixelPlacementShader;

void initShaders();