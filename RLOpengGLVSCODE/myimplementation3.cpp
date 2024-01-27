/*
#include "myimplementation.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    GameWindow gameWindow = GameWindow(SCR_WIDTH, SCR_HEIGHT, "Test");
    if(gameWindow.GetWindow() == nullptr) {
        return -1;
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader shader("shaders/texture_shader.vert", "shaders/texture_shader.frag");
    float vertices[] = {
        //Positions          //Colors           //Tex
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,     // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f      // top left
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    VertexArray va;
    IndexBuffer ib = IndexBuffer(indices, 6);
    VertexBuffer vb = VertexBuffer(vertices, 8 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.AddFloat(3);
    layout.AddFloat(3);
    layout.AddFloat(2);

    va.AddBuffer(vb, layout);
    Renderer renderer;
    Texture texture("images/wall.jpg");
    texture.Bind();
    shader.setInt("ourShader", texture.GetId());
    while (!glfwWindowShouldClose(gameWindow.GetWindow())) {
        gameWindow.Update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.Clear();
        renderer.Draw(va, ib, shader);
        gameWindow.SwapBuffers();
        gameWindow.PollEvents();
    }
    return 0;
}
*/
