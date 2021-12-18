#ifndef _INDEX_BUFFER_
#define _INDEX_BUFFER_

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void init(unsigned int indices[], unsigned int numIndices);
    void bind();

private:
    unsigned int m_ebo;
};

#endif