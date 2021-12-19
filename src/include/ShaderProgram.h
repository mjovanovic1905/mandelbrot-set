#ifndef _SHADER_PROGRAM_
#define _SHADER_PROGRAM_

#include <climits>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    bool init(const char* vertexSource, const char* fragmentSource);
    void addVertexAtributeDescription(unsigned int index, unsigned int numElements,
 	                                  unsigned int elementType, bool normalized,
 	                                  int stride, const void * pointer);
    void setUniformValue(const char* uniformName, const glm::vec2& value);
    void setUniformValue(const char* uniformName, int value);
    void setUniformValue(const char* uniformName, float value);
    void useProgram();
    
private:
    static constexpr unsigned int INVALID_SHADER_ID = UINT_MAX;

    unsigned int createShader(const char* shaderSoruce, unsigned int shaderType);

    unsigned int m_shaderProgram;
};

#endif