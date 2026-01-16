#include "global.h"

int WIDTH = 600;
int HEIGHT = 800;

int MOUSE_X_POS = 0;
int MOUSE_Y_POS = 0;
std::string WINDOW_TITLE = "Graffen";



glm::mat4 fontProjection = glm::ortho(
	0.0f, static_cast<float>(WIDTH),
	static_cast<float>(HEIGHT), 0.0f
);
glm::mat4 imageProjection = glm::ortho(
	0.0f, static_cast<float>(WIDTH),
	static_cast<float>(HEIGHT), 0.0f
);
glm::mat4 pixelPlacementProjection = glm::ortho(
	0.0f, static_cast<float>(WIDTH),
	static_cast<float>(HEIGHT), 0.0f,
	100.0f, -100.0f
);

ShaderModule fontShader;
ShaderModule pixelPlacementShader;
ShaderModule divGuiShader;
ShaderModule imgGuiShader;

void initShaders()
{
	try
	{
		fontShader.generate("src/shaders/font/font.vs", "src/shaders/font/font.fs");
		pixelPlacementShader.generate("src/shaders/pixelPlacement/pixelPlacement.vs", "src/shaders/pixelPlacement/pixelPlacement.fs");
		divGuiShader.generate("src/shaders/gui_tags_shaders/div/div.vs", "src/shaders/gui_tags_shaders/div/div.fs");
		imgGuiShader.generate("src/shaders/gui_tags_shaders/img/img.vs", "src/shaders/gui_tags_shaders/img/img.fs");
	}
	catch (const std::exception& e)
	{

	}
}