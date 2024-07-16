#include <vector>
#include <fstream>
#include <iostream>
#include "App.h"
#include "JUScene.h"
#include <map>

int WIDTH = 640;
int HEIGHT = 480;


int main(void)
{
    App app(WIDTH, HEIGHT, "Hi", "/mnt/Data/home/nob/Documents/Projects/C++/opeglsa/assets");

    app.AddScene(JUScene::create);
    app.Run(0);
    

    return 0;
}