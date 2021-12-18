#include "include/IndexBuffer.h"

#include "GL/glew.h"

IndexBuffer::IndexBuffer()
{
}

void IndexBuffer::init(unsigned int indices[], unsigned int numIndices)
{
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indices, GL_STATIC_DRAW); 
}

void IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

IndexBuffer::~IndexBuffer()
{
}
