#include "Game.h"

std::string GLErrorToString(GLenum err)
{
	switch (err)
	{
	case GL_NO_ERROR:
		return "GL_NO_ERROR";
	case GL_INVALID_ENUM:
		return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE:
		return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION:
		return "GL_INVALID_OPERATION";
	case GL_STACK_OVERFLOW:
		return "GL_STACK_OVERFLOW";
	case GL_STACK_UNDERFLOW:
		return "GL_STACK_UNDERFLOW";
	case GL_OUT_OF_MEMORY:
		return "GL_OUT_OF_MEMORY";
	case 0x8031: /* not core */
		return "GL_TABLE_TOO_LARGE_EXT";
	case 0x8065: /* not core */
		return "GL_TEXTURE_TOO_LARGE_EXT";
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		return "GL_INVALID_FRAMEBUFFER_OPERATION";
	default:

		char dat[100];

		sprintf(dat, "%d", err);

		std::string ret = dat;
		return ret;
	}
}

const char *severitytostring(GLenum severity)
{

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		return "High";
	case GL_DEBUG_SEVERITY_MEDIUM:
		return "Medium";
	case GL_DEBUG_SEVERITY_LOW:
		return "Low";
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		return "Notification";
	default:
		return "Unknown Enum";
	}
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	const char *s = severitytostring(severity);

	std::cout << "[OpenGL (" << s << ")](" << GLErrorToString(type) << ") " << message << std::endl;
}

Game::Game(int WIDTH, int HEIGHT, const char *title) : timer()
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

void Game::EnableDebug()
{
	GLDEBUGCALL(glEnable(GL_DEBUG_OUTPUT));
	GLDEBUGCALL(glDebugMessageCallback(MessageCallback, 0));
}

float Game::Step()
{
    return timer.Step();
}

float Game::GetTime()
{
    return timer.GetTime();
}

GLFWwindow *Game::GetWindow()
{
    return window;
}

Game::~Game()
{
    glfwTerminate();
}
