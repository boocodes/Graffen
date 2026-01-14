#include "global.h"

int WIDTH = 900;
int HEIGHT = 600;

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
	static_cast<float>(HEIGHT), 0.0f
);

ShaderModule imageShader;
ShaderModule fontShader;
ShaderModule pixelPlacementShader;

void initShaders()
{
	try
	{
		imageShader.generate("src/shaders/image/image.vs", "src/shaders/image/image.fs");
		fontShader.generate("src/shaders/font/font.vs", "src/shaders/font/font.fs");
		pixelPlacementShader.generate("src/shaders/pixelPlacement/pixelPlacement.vs", "src/shaders/pixelPlacement/pixelPlacement.fs");

	}
	catch (const std::exception& e)
	{

	}
}