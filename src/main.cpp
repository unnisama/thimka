#include <vector>
#include <fstream>
#include <iostream>
#include "App.h"
#include "JUScene.h"
#include <map>
#include <stddef.h>
#include <unistd.h>

int WIDTH = 640;
int HEIGHT = 480;


int main(int argc, char **argv)
{
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    auto path = std::string(cwd);

    App app(WIDTH, HEIGHT, "Hi", path+"/assets");

    app.AddScene(JUScene::create);
    app.Run(0);
    

    return 0;
}