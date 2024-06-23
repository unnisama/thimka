#include "Gui.h"

Gui::Gui(GLFWwindow *window)
{
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init("#version 330");
    io = &ImGui::GetIO();
    font = io->Fonts->AddFontFromFileTTF("/usr/share/fonts/TTF/JetBrainsMono-Medium.ttf", 16.0f);
    ImGui::GetStyle().FrameRounding = 5.0f;
    ImGui::GetStyle().WindowRounding = 5.0f;

}

void Gui::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::DrawFrame()
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
