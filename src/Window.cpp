#include "include/Window.h"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(/* args */)
: m_window(nullptr)
{
}

bool Window::init(float screenWidth, float screenHeight)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
    if (m_window == nullptr)
    {
        std::cout << "Failed to create GLFW window\n";
        return false;
    }
    glfwMakeContextCurrent(m_window);

    if (unsigned int glewStatus = glewInit() != GLEW_OK)
    {
        std::cout << "GLEW failed to initialise - status: " << glewStatus << '\n';
        const char* version = (const char*)glGetString(GL_VERSION);
        std::cout << "Supported OpenGl version: " << version << '\n';
        return false;
    }

    glViewport(0, 0, screenWidth, screenHeight);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    return true;
}

void Window::processInput()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
}

bool Window::windowShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

Window::~Window()
{
}

