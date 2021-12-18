#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "include/Window.h"
#include "include/Utils.h"
#include "include/VAO.h"
#include "include/VertexBuffer.h"
#include "include/IndexBuffer.h"
#include "include/ShaderProgram.h"

static constexpr float SCREEN_WIDTH = 800.f;
static constexpr float SCREEN_HEIGHT = 600.f;

std::string read_file(std::string_view path)
{
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
    if (!mainWindow.init(SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        releaseLibraryData();
        return -1;
    }

    std::vector<float> vertices =
    {
        1.0f,  1.0f, 0.0f,  // top right
        1.0f, -1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f,  // bottom left
        -1.0f,  1.0f, 0.0f   // top left 
    };

    std::vector<unsigned int> indices =
    { 
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    VAO vao;
    vao.init();
    vao.bind();

    VertexBuffer vb;
    vb.init(vertices.data(), vertices.size());

    IndexBuffer ebo;
    ebo.init(indices.data(), indices.size()); 
    
    ShaderProgram shaderProgram;
    if (!shaderProgram.init(read_file("./shaders/basic.vs").c_str(), read_file("./shaders/basic.fs").c_str()))
    {
        releaseLibraryData();
        return -1;
    }
    shaderProgram.addVertexAtributeDescription(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    float screenSize[2] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    shaderProgram.setUniformValue("screenSize", screenSize);

    while(!mainWindow.windowShouldClose())
    {
        mainWindow.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.useProgram();
        vao.bind();
        ebo.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        mainWindow.swapBuffers();
        glfwPollEvents();    
    }  

    glfwTerminate();
    return 0;
}