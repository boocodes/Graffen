#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <global/global.h>
#include <gui_tags/p/p_tag.h>
#include <gui_tags/div/div_tag.h>
#include <gui_tags/img/img_tag.h>
#include <gui_tags/document/document_tag.h>
#include <gui_tags/input/input_tag.h>
#include <gui_tags/form/form_tag.h>



void character_callback(GLFWwindow* window, unsigned int codepoint);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


std::string input_text = "";


DocumentTag* dc = new DocumentTag();
FormTag* ftag = new FormTag();



int main()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        return -1;
    }

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
    
    window = glfwCreateWindow(mode->width, mode->height, WINDOW_TITLE.c_str(), primaryMonitor, NULL);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCharCallback(window, character_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);


   

    int monitorX, monitorY, monitorWidth, monitorHeight;
    glfwGetMonitorWorkarea(primaryMonitor, &monitorX, &monitorY, &monitorWidth, &monitorHeight);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    int windowPosX = monitorX + (monitorWidth - windowWidth) / 2;
    int windowPosY = monitorY + (monitorHeight - windowHeight) / 2;

    glfwSetWindowPos(window, windowPosX, windowPosY);

    glfwMakeContextCurrent(window);


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


   
    ImgTag* background_image = new ImgTag(0, 0, 1, "assets/main_menu.png");
    dc->add_tag(background_image);
    ImgTag* background_menu_logo = new ImgTag(50, 50, 1, "assets/main_menu_logo.png");
    dc->add_tag(background_menu_logo);


    
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
            ftag->disable_all_inputs();
            ftag->check_click(MOUSE_X_POS, MOUSE_Y_POS);
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


void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    for (auto input : ftag->input_list)
    {
        if (input->is_active)
        {
            input->set_value(input->value + static_cast<char>(codepoint));
        }
    }
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (auto input : ftag->input_list)
    {
        if (input->is_active)
        {
            if (action == GLFW_PRESS || action == GLFW_REPEAT)
            {
                switch (key)
                {
                case GLFW_KEY_BACKSPACE:
                    if (!input->value.empty())
                    {
                        input->delete_last_char();
                    }
                }
            }
        }
    }


   
}