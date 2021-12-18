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