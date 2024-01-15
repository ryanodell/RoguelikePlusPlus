#ifndef MYIMPLEMENTATION_H_INCLUDED
#define MYIMPLEMENTATION_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

////////////////////////////////VERTEX BUFFER//////////////////////////////////
class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void Bind();
    void Unbind();
private:
    unsigned int m_VertexBufferId;
};
VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    glGenBuffers(1, &m_VertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_VertexBufferId);
}
void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
}
void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
////////////////////////////////VERTEX BUFFER//////////////////////////////////


////////////////////////////////GAME WINDOW//////////////////////////////////
class GameWindow {
public:
    GameWindow(unsigned int windowWidth, unsigned int windowHeight, const char* windowTitle);
    ~GameWindow();
    bool IsRunning();
    void Update();
    void SwapBuffers();
    void PollEvents();
    GLFWwindow* GetWindow() const { return m_window; };
private:
    GLFWwindow* m_window;
    unsigned int m_width;
    unsigned int m_height;
    const char* m_windowTitle;
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
GameWindow::GameWindow(unsigned int windowWidth, unsigned int windowHeight, const char* windowTitle) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_width = windowWidth;
    m_height = windowHeight;
    m_windowTitle = windowTitle;
    m_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
    if (m_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, GameWindow::framebuffer_size_callback);
}
GameWindow::~GameWindow() {
    glfwTerminate();
}
void GameWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    GameWindow* gameWindow = static_cast<GameWindow*>(glfwGetWindowUserPointer(window));
    if (gameWindow != nullptr) {
        gameWindow->m_width = width;
        gameWindow->m_height = height;
        glViewport(0, 0, width, height);
    }
}
void GameWindow::SwapBuffers() {
    glfwSwapBuffers(m_window);
}
void GameWindow::PollEvents() {
    glfwPollEvents();
}
void GameWindow::Update() {
   if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}
////////////////////////////////GAME WINDOW//////////////////////////////////


#endif // MYIMPLEMENTATION_H_INCLUDED
