#include "include/ShaderProgram.h"

#include <iostream>

#include "GL/glew.h"

ShaderProgram::ShaderProgram(/* args */)
{
}

unsigned int ShaderProgram::createShader(const char* shaderSoruce, unsigned int shaderType)
{
    unsigned int shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSoruce, NULL);
    glCompileShader(shaderId);

    int  success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << '\n';
        return INVALID_SHADER_ID;
    }

    return shaderId;
}

bool ShaderProgram::init(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vertexShader = createShader(vertexSource, GL_VERTEX_SHADER);
    if (vertexShader == INVALID_SHADER_ID)
    {
        return false;
    }

    unsigned int fragmentShader = createShader(fragmentSource, GL_FRAGMENT_SHADER);
    if (fragmentShader == INVALID_SHADER_ID)
    {
        return false;
    }

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    int  success;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::CREATION_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void ShaderProgram::addVertexAtributeDescription(unsigned int index, unsigned int numElements,
 	                                  unsigned int elementType, bool normalized,
 	                                  int stride, const void * pointer)
{
    glVertexAttribPointer(index, numElements, elementType, normalized ? GL_TRUE : GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}

void ShaderProgram::setUniformValue(const char* uniformName, float value[2])
{
    int uniformLocation = glGetUniformLocation(m_shaderProgram, uniformName);
    glUniform2f(uniformLocation, value[0], value[1]);
}

void ShaderProgram::useProgram()
{
    glUseProgram(m_shaderProgram);
}

ShaderProgram::~ShaderProgram()
{
}
