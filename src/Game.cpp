#include "Game.h"

Game::Game(int WIDTH, int HEIGHT, const char *title)
{

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Initialize the library */
    if (!glfwInit()){
        printf("Failed glfw init\n");
        exit(0);
        return;
    }
        

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        printf("Failed creating window\n");
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    // vsync
    glfwSwapInterval(1);

    this->HEIGHT = HEIGHT;
    this->WIDTH = WIDTH;

    glViewport(0, 0, WIDTH, HEIGHT);

}

void Game::HandleBufferAndEvent()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Game::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Game::SetDebug(GLDEBUGPROC callback)
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(callback, 0);
}

GLFWwindow *Game::GetWindow()
{
    return window;
}

Game::~Game()
{
    glfwTerminate();
}
