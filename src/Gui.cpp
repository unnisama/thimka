#include "Gui.h"

Gui::Gui(GLFWwindow *window, Game *game, std::string assetspath)
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init("#version 330");
    io = &ImGui::GetIO();
    font = io->Fonts->AddFontFromFileTTF((assetspath + "/fonts/JetBrainsMono-Medium.ttf").data(), 16.0f);
    ImGui::GetStyle().FrameRounding = 5.0f;
    ImGui::GetStyle().WindowRounding = 5.0f;
    this->game = game;

}

void Gui::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


ImGuiIO *Gui::GetIO()
{
    return io;
}
Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

Game *Gui::GetGame()
{
    return game;
}
