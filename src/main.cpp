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
#include "renderer.h"

int WIDTH = 640;
int HEIGHT = 480;



int main(void)
{
	Game game(WIDTH, HEIGHT, "Start");
	// game.EnableDebug();

	Gui gui(game.GetWindow(), &game);

	Renderer renderer;
	float positions[8] = {
		0.5f, 0.5f,
		-0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};

	uint32_t indexes[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer vb(positions, sizeof(float) * 8);

	ArrayLayout aly;
	aly.AddFloat(2);

	VertexArray va(&vb, &aly);
	IndexBuffer ib(indexes, 6);

	va.Enable();

	Shader shader("../shaders/fragment.glsl", "../shaders/vertex.glsl");

	shader.Use();

	
	GLuint time_ = shader.GetUniformLocation("time");
	GLuint freqid = shader.GetUniformLocation("freq");
	

	
	GLuint deltatime_ = shader.GetUniformLocation("deltatime");

	bool menuopen = true;

	float freq = 1.0f;
	GLDEBUGCALL(glUniform1f(freqid, freq));

    float dt = game.Step();
	while (!game.ShouldClose())
	{
		GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT));

		GLDEBUGCALL(glUniform1f(deltatime_, dt));
		GLDEBUGCALL(glUniform1f(time_, game.GetTime()));

		renderer.Draw(va, ib, shader);

		gui.NewFrame();

		ImGui::SetNextWindowPos({0,0});
		ImGui::SetNextWindowSize({-1,110});
		ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
		if(ImGui::SliderFloat("Freq", &freq, 0.5f, 6.0f)){
			GLDEBUGCALL(glUniform1f(freqid, freq));
		}
		ImGui::Text("UpTime: %.3f", game.GetTime());
		ImGui::Text("FTime: %.3f", dt);
		ImGui::Text("FPS: %.f", 1.0f/dt);

		ImGui::End();
		
		gui.EndFrame();
		game.HandleBufferAndEvent();
		dt = game.Step();
	}

	return 0;
}