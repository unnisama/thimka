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



int main(void)
{
	Game game(WIDTH, HEIGHT, "Start");
	game.EnableDebug();

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
		ImGui::SetNextWindowSize({-1,110});
		ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
		if(ImGui::SliderFloat("Freq", &freq, 0.0f, 3.0f)){
			glUniform1f(freqid, freq);
		}
		ImGui::Text("UpTime: %.3f", game.GetTime());
		ImGui::Text("FrameTime: %.3f", dt);
		ImGui::Text("FPS: %.3f", 1.0f/dt);

		ImGui::End();
		
		gui.DrawFrame();
		game.HandleBufferAndEvent();
		dt = game.Step();
	}
	shader.Delete();
	vb.UnBind();
	ib.UnBind();

	return 0;
}