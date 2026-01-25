#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <global/global.h>
#include <gui_tags/p/p_tag.h>
#include <gui_tags/div/div_tag.h>
#include <gui_tags/img/img_tag.h>
#include <gui_tags/document/document_tag.h>
#include <gui_tags/input/input_tag.h>

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
DocumentTag* dc = new DocumentTag();
int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        return -1;
    }
    
    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return 1;
    }
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    DivTag* dive = new DivTag(150, 400, 1, 100, 100);
    ImgTag* imge = new ImgTag(0, 0, 5, "assets/login3.jpg");
    dive->backgroundColor = glm::vec4(0, 0, 0, 0);
    dive->borderWidth = glm::vec4(5, 5, 5, 5);
    dive->borderRadius = glm::vec4(0, 5, 15, 20);
    dive->borderColor = glm::vec4(1, 0, 0, 1);
    imge->resize(308, 308);
    PTag* pt = new PTag(300, 50, glm::vec3(0, 0, 0), 16, "assets/fonts/Roboto-Bold.ttf", "Graffen", 1);
    InputTag* inpt = new InputTag(250, 400, 1, 150, 150);
    inpt->backgroundColor = glm::vec4(0, 0, 0, 0);
    inpt->borderRadius = glm::vec4(10, 10, 10, 10);
    inpt->borderColor = glm::vec4(0, 1, 1, 1);
    inpt->borderWidth = glm::vec4(5, 5, 5, 5);

    
    dc->add_tag(dive);
    dc->add_tag(imge);
    dc->add_tag(pt);
    dc->add_tag(inpt);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        dc->render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    MOUSE_X_POS = static_cast<int>(xpos);
    MOUSE_Y_POS = static_cast<int>(ypos);
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            dc->check_click(MOUSE_X_POS, MOUSE_Y_POS);
            std::cout << "Left mouse button pressed at x: " << MOUSE_X_POS << ", y: " << MOUSE_Y_POS << std::endl;
        }
        else if (action == GLFW_RELEASE)
            std::cout << "Left mouse button released" << std::endl;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {

    }
}