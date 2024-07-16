#pragma once
#include "scene.h"

class JUScene : public Scene{
private:
    Mesh *skybox;
    unsigned int texID;
    Shader *skyboxshader;
    Shader *lightshader;
    Shader *objshader;
    Mesh *light;
    Mesh *obj;
    std::vector<Shader*> shaders;
    glm::vec3 lightPos;
    glm::vec3 lightcolor;
    Texture *texture;
    Texture *normal;
public:
    JUScene(GLFWwindow *window, Gui* gui, std::string assetspath);
    void Update(float dt);
    void Draw();
    void onGui(float dt);
    static JUScene *create(GLFWwindow *window, Gui* gui, std::string assetspath);
    void End(); 
};