#ifndef _VAO_
#define _VAO_

class VAO
{
public:
    VAO();
    
    void init();
    void bind();

    ~VAO();
private:
    unsigned int m_vao;
};

#endif
