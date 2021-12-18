#include "include/VertexBuffer.h"

#include "GL/glew.h"

VertexBuffer::VertexBuffer()
{
}

void VertexBuffer::init(float vertices[], unsigned int numVertices)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
}

