#ifndef _WINDOW_
#define _WINDOW_

#include <glm/glm.hpp>

class GLFWwindow;

class Window
{
public:
    Window();
    bool init(float screenWidth, float screenHeight, int iterations);
    void processInput();
    bool windowShouldClose() const;
    void swapBuffers();
    float getZoom() const;
    void getOffset(glm::vec2& offset) const;
    GLFWwindow* getGLFWwindow() const { return m_window; }
    int getIterations() const { return m_iterations; }


    ~Window();
private:
    static constexpr float ZOOM_OFFSET = 0.1f;
    void updateMousePos();
    void setStartDrag();
    void handleScroll();

    GLFWwindow* m_window;
    float m_fov;
    float m_zoom;
    float m_xoffset;
    float m_yoffset;
    float m_xStartDrag = 0.f;
    float m_yStartDrag = 0.f;
    unsigned int m_width;
    unsigned int m_height;
    int m_iterations;
};

#endif