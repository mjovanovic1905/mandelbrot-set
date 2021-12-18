#ifndef _WINDOW_
#define _WINDOW_

class GLFWwindow;

class Window
{
public:
    Window();
    bool init();
    void processInput();
    bool windowShouldClose() const;
    void swapBuffers();

    ~Window();
private:
    GLFWwindow* m_window;

};

#endif