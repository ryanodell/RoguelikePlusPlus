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
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    VertexBuffer vert = VertexBuffer(vertices, 4 * 2 * sizeof(float));
    while (!glfwWindowShouldClose(gameWindow.GetWindow())) {
        gameWindow.Update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        gameWindow.SwapBuffers();
        gameWindow.PollEvents();
    }
    return 0;
}
