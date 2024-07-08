#include "App.h"

App::App(int WIDTH, int HEIGHT, const char *title, std::string assetspath)
{
    game = new Game(WIDTH, HEIGHT, title);
    gui = new Gui(Game::GetWindow(), game);
    this->assetspath = assetspath;
}


void App::Run(int index)
{
    float dt = 0.0f;
    while (!game->ShouldClose())
    {
        GLDEBUGCALL(glClearColor(0.094f, 0.094f, 0.094f, 1.0f));
        GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        scenes[index]->Run(dt);

        game->HandleBufferAndEvent();
        dt = game->Step();
    }
}

void App::AddScene(std::function<Scene *(GLFWwindow *, Gui *, std::string)> func)
{
    scenes.push_back(func(game->GetWindow(), gui, assetspath));
}

App::~App()
{
    delete gui;
    delete game;
    for(Scene *sc : scenes){
        sc->End();
        delete sc;
    }
}
