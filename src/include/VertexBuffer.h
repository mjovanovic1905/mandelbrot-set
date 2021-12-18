#ifndef _VERTEX_BUFFER_
#define _VERTEX_BUFFER_

#include <vector>

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void init(float vertices[], unsigned int numVertices);
    inline unsigned int getId() const { return m_vbo; }

private:
    unsigned int m_vbo;
};

#endif