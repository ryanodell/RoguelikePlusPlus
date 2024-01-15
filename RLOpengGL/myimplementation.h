#ifndef MYIMPLEMENTATION_H_INCLUDED
#define MYIMPLEMENTATION_H_INCLUDED

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

void Init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

#endif // MYIMPLEMENTATION_H_INCLUDED
