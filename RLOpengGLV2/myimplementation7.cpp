
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
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,     // top right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,     // bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f      // top left
    };

    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    VertexArray va;
    IndexBuffer ib = IndexBuffer(indices, 6);
    VertexBuffer vb = VertexBuffer(sizeof(Vertex) * 4);
    VertexBufferLayout layout;
    layout.AddFloat(3);
    layout.AddFloat(3);
    layout.AddFloat(2);
    va.AddBuffer(vb, layout);

    glm::mat4 proj = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, -1.0f, 1.0f);

    // view matrix
    glm::mat4 ident = glm::mat4(1.0f);
    glm::vec3 trvec = glm::vec3(0, 0, 0);
    glm::mat4 view = glm::translate(ident, trvec);

    Renderer renderer;
    Texture texture("images/kruggsmash.png");
    texture.Bind();
    SpriteRenderer sRenderer;
    sRenderer.Init();
    shader.setInt("ourShader", texture.GetId());

    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);

    while (!glfwWindowShouldClose(gameWindow.GetWindow())) {
        gameWindow.Update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        renderer.Clear();
        sRenderer.TempDraw(shader, texture);
        gameWindow.SwapBuffers();
        gameWindow.PollEvents();
    }
    return 0;
}

