#pragma once
#include "storagebuffer.h"
#include "scene.h"


class ThimkaScene : public Scene{
private:
    std::vector<Shader*> shaders;
    std::vector<glm::mat4> meshes;
    StorageBuffer *sb;
    Texture *texture;
    Shader *shader;
    Mesh *plane;
    std::string assetspath;

public:
    ThimkaScene(GLFWwindow *window, Gui* gui, std::string assetspath);
    void Update(float dt);
    void Draw();
    void onGui(float dt);
    static ThimkaScene *create(GLFWwindow *window, Gui* gui, std::string assetspath);
    void End();
};