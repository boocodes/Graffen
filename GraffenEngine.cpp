#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        return -1;
    }
    window = glfwCreateWindow(900, 600, "WINDOW_TITLE.c_str()", NULL, NULL);
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
   

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}