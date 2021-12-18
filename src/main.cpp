#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "include/Window.h"
#include "include/Utils.h"
#include "include/VAO.h"
#include "include/VertexBuffer.h"
#include "include/IndexBuffer.h"
#include "include/ShaderProgram.h"

std::string read_file(std::string_view path) {
    constexpr auto read_size = std::size_t{4096};
    auto stream = std::ifstream{path.data()};
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string{};
    auto buf = std::string(read_size, '\0');
    while (stream.read(& buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

int main()
{
    if (!initLibraries())
    {
        releaseLibraryData();
        return -1;
    }

    Window mainWindow;
    if (!mainWindow.init())
    {
        releaseLibraryData();
        return -1;
    }

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };    

    VAO vao;
    vao.init();
    vao.bind();

    VertexBuffer vb;
    vb.init(vertices, 12);

    IndexBuffer ebo;
    ebo.init(indices, 6); 
    
    ShaderProgram shaderProgram;
    if (!shaderProgram.init(read_file("./shaders/basic.vs").c_str(), read_file("./shaders/basic.fs").c_str()))
    {
        releaseLibraryData();
        return -1;
    }
    shaderProgram.addVertexAtributeDescription(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    while(!mainWindow.windowShouldClose())
    {
        mainWindow.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.useProgram();
        vao.bind();
        ebo.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        mainWindow.swapBuffers();
        glfwPollEvents();    
    }  

    glfwTerminate();
    return 0;
}