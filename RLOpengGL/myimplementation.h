#ifndef MYIMPLEMENTATION_H_INCLUDED
#define MYIMPLEMENTATION_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "shader.h"

#define INT2VOIDP(i) (void*)(uintptr_t)(i)

///////////////////////////VERTEX BUFFER ELEMENT///////////////////////////////
struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT         : return sizeof(GLfloat);
            case GL_UNSIGNED_INT  : return sizeof(GLuint);
            case GL_UNSIGNED_BYTE : return sizeof(GLbyte);
        }
        return 0;
    }
};
///////////////////////////VERTEX BUFFER ELEMENT///////////////////////////////

////////////////////////////////BUFFER LAYOUT//////////////////////////////////
class VertexBufferLayout {
    private:
        unsigned int m_Stride;
        std::vector<VertexBufferElement> m_Elements;

    public:
        VertexBufferLayout() :
            m_Stride(0) { }

        void AddFloat(unsigned int count)        { Push(GL_FLOAT, count, GL_FALSE);        }
        void AddUnsignedInt(unsigned int count)  { Push(GL_UNSIGNED_INT, count, GL_FALSE); }
        void AddUnsignedByte(unsigned int count) { Push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

        inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; };
        inline unsigned int GetStride() const { return m_Stride; };

    private:
        void Push(unsigned int type, unsigned int count, unsigned char normalized) {
            struct VertexBufferElement vbe = {type, count, normalized};
            m_Elements.push_back(vbe);
            m_Stride += count * VertexBufferElement::GetSizeOfType(type);
        };
};
////////////////////////////////BUFFER LAYOUT//////////////////////////////////

////////////////////////////////VERTEX BUFFER//////////////////////////////////
class VertexBuffer {
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;
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
void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
}
void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
////////////////////////////////VERTEX BUFFER//////////////////////////////////

/////////////////////////////////INDEX BUFFER//////////////////////////////////

class IndexBuffer {
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;

    public:
        IndexBuffer(const unsigned int* indices, unsigned int count);
        ~IndexBuffer();
        void Bind() const;
        void Unbind() const;
        inline unsigned int GetCount() const { return m_Count; }
};
IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count) : m_Count(count) {
    glGenBuffers(1, &m_RendererID) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
/////////////////////////////////INDEX BUFFER//////////////////////////////////

///////////////////////////VERTEX ARRAY///////////////////////////////////////
class VertexArray {
    private:
        unsigned int m_RendererID;

    public:
        VertexArray();
        ~VertexArray();
        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void Bind() const;
        void Unbind() const;
};
VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const std::vector<VertexBufferElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size() ; i++)
    {
        const VertexBufferElement element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                      layout.GetStride(), INT2VOIDP(offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
};
///////////////////////////VERTEX ARRAY//////////////////////////////////////

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

////////////////////////////////RENDERER/////////////////////////////////////
class Renderer {
    public:
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
void Renderer::Clear() const {
        glClear( GL_COLOR_BUFFER_BIT );
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
        shader.use();
        va.Bind();
        ib.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
////////////////////////////////RENDERER////////////////////////////////////

#endif // MYIMPLEMENTATION_H_INCLUDED
