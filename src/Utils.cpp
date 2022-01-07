#include "include/Utils.h"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

bool initLibraries()
{
    glfwInit();
    return true;
}

void releaseLibraryData()
{
    glfwTerminate();
}

void draw(int numIndices)
{
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

void pollEvents()
{
    glfwPollEvents();
}