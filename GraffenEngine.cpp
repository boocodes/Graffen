#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <global/global.h>
#include <gui_tags/p/p_tag.h>
#include <gui_tags/div/div_tag.h>

int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        return -1;
    }
    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE.c_str(), NULL, NULL);
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

    DivTag* dive = new DivTag(10, 10, 1, 100, 100);


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        dive->draw();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}