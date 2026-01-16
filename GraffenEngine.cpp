#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <global/global.h>
#include <gui_tags/p/p_tag.h>
#include <gui_tags/div/div_tag.h>
#include <gui_tags/img/img_tag.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        return -1;
    }
    
    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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

    DivTag* dive = new DivTag(100, 100, 1, 222, 222);
    ImgTag* imge = new ImgTag(0, 0, 1, "assets/login3.jpg");
    dive->borderRadius = glm::vec4(10, 10, 10, 10);
    imge->resize(308, 308);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        dive->draw();
        

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