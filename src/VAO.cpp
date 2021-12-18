#include "include/VAO.h"

#include "GL/glew.h"

VAO::VAO()
{
}

void VAO::init()
{
    glGenVertexArrays(1, &m_vao);
}

void VAO::bind()
{
    glBindVertexArray(m_vao);
}

VAO::~VAO()
{
}
