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

int Game::WIDTH = 1;
int Game::HEIGHT = 1;
GLFWwindow* Game::window;


Game::Game(int width, int height, const char *title) : timer()
{

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Initialize the library */
    if (!glfwInit()){
        printf("Failed glfw init\n");
        exit(0);
        return;
    }
        
    Game::HEIGHT = height;
    Game::WIDTH = width;
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


	glfwSetWindowSizeCallback(window, WindowResizeCallBack);

	AddResizeCallback([this](int width, int height){
        this->ResizeCallBack(width, height);
    });

	glfwSetScrollCallback(window, MouseWheelCallBack);

	GLDEBUGCALL(glViewport(0, 0, WIDTH, HEIGHT));

	GLDEBUGCALL(glEnable(GL_DEPTH_TEST));
	GLDEBUGCALL(glEnable(GL_BLEND));
	GLDEBUGCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
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

void Game::ResizeCallBack(int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	GLDEBUGCALL(glViewport(0, 0, WIDTH, HEIGHT));
}

Game::~Game()
{
	GLDEBUGCALL(glDisable(GL_DEPTH_TEST));
	GLDEBUGCALL(glDisable(GL_BLEND));
    glfwTerminate();
}
