#include "vertexbuffer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include "Game.h"
#include <iostream>
#include <string>
#include "Gui.h"
#include "shader.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "timer.h"

int WIDTH = 640;
int HEIGHT = 480;

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

int main(void)
{
	Game game(WIDTH, HEIGHT, "Start");
	game.SetDebug(MessageCallback);

	Gui gui(game.GetWindow());

	Timer timer;

	float positions[8] = {
		0.5f, 0.5f,
		-0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f};

	uint32_t indexes[6] = {
		0, 1, 2,
		2, 3, 0};

	VertexBuffer vb(positions, sizeof(float) * 8);

	ArrayLayout aly;
	aly.AddFloat(2);

	VertexArray va(&vb, &aly);
	IndexBuffer ib(indexes, 6);

	va.Enable();

	Shader shader("../shaders/fragment.glsl", "../shaders/vertex.glsl");

	GLuint deltatime = shader.GetUniformLocation("dt");
	GLuint time_ = shader.GetUniformLocation("time");
	GLuint freqid = shader.GetUniformLocation("freq");
	shader.Use();

	float color[3] = {};

	bool menuopen = true;

	float freq = 1.0f;
	glUniform1f(freqid, freq);

    float dt = timer.Step();
	while (!game.ShouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		GLDEBUGCALL(glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, nullptr));

		glUniform1f(deltatime, dt);
		glUniform1f(time_, timer.GetTime());
		gui.NewFrame();

		ImGui::SetNextWindowPos({0,0});
		ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
		if(ImGui::SliderFloat("Freq", &freq, 0.0f, 3.0f)){
			glUniform1f(freqid, freq);
		}
		ImGui::Text("Time: %f", timer.GetTime());
		ImGui::Text("DT: %f", dt);

		ImGui::End();
		dt = timer.Step();
		gui.DrawFrame();
		game.HandleBufferAndEvent();
		
	}
	shader.Delete();
	vb.UnBind();
	ib.UnBind();

	return 0;
}