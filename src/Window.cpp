#include "include/Window.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

enum ZoomDir { NONE, IN, OUT };

static ZoomDir zoomDir = ZoomDir::NONE;
static bool viewportChanged = false;

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    viewportChanged = true;
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset < 0)
    {
        zoomDir = ZoomDir::OUT;
    }
    else if (yoffset > 0)
    {
        zoomDir = ZoomDir::IN;
    }
}

Window::Window()
: m_window(nullptr)
, m_fov(0.0f)
, m_zoom(100.f)
, m_xoffset(0.0f)
, m_yoffset(0.0f)
, m_xStartDrag(0.0f)
, m_yStartDrag(0.0f)
, m_width(0)
, m_height(0)
{
}

bool Window::init(float screenWidth, float screenHeight, int iterations)
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
    glfwSetScrollCallback(m_window, scrollCallback);

    m_width = screenWidth;
    m_height = screenHeight;
    m_iterations = iterations;

    return true;
}

void Window::processInput()
{
    static bool mousePressed = false;
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }

    if (viewportChanged)
    {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        m_width = viewport[2];
        m_height = viewport[3];
        
        viewportChanged = false;
    }

    if (zoomDir != ZoomDir::NONE)
    {
        handleScroll();
    }

    if(glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && !mousePressed)
    {
        setStartDrag();
        mousePressed = true;
    }

    if(glfwGetKey(m_window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE && mousePressed)
    {
        mousePressed = false;
    }

    if(mousePressed)
    {
        updateMousePos();   
    }

    if(glfwGetKey(m_window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
    {
        m_iterations++;
    }

    if(glfwGetKey(m_window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    {
        if (m_iterations > 1)
        {
            m_iterations--;
        }
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

float Window::getZoom() const
{
    return m_zoom;
}

void Window::updateMousePos()
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    m_xoffset += (xpos - m_xStartDrag) / m_zoom;
    m_yoffset += (ypos - m_yStartDrag) / m_zoom;

    m_xStartDrag = xpos;
    m_yStartDrag = ypos;
}

void Window::setStartDrag()
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    m_xStartDrag = xpos;
    m_yStartDrag = ypos;
}

void Window::handleScroll()
{
    double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);

    double dx = (xpos - m_width / 2) / m_zoom - m_xoffset;
    double dy = (m_height - ypos - m_height / 2) / m_zoom - m_yoffset;
    m_xoffset = -dx;
    m_yoffset = -dy;
    
    if (zoomDir == ZoomDir::OUT)
    {
        m_zoom /= 1.1;
    }
    else if (zoomDir == ZoomDir::IN)
    {
        m_zoom *= 1.1;
    }

    dx = (xpos - m_width / 2) / m_zoom;
    dy = (m_height - ypos - m_height / 2) / m_zoom;
    m_xoffset += dx;
    m_yoffset += dy;

    zoomDir = ZoomDir::NONE;
}

void Window::getOffset(glm::vec2& offset) const
{
    offset.x = m_xoffset;
    offset.y = m_yoffset;
}


Window::~Window()
{
}

