#include "ThimkaScene.h"

bool isEnabled(int x, int y, int z){
    return true;
}
std::vector<glm::mat4> SetupData(float x, float y, float z){
    std::vector<glm::mat4> meshes;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                if(isEnabled(i, j, k) == true){
                    glm::mat4 mat2 = glm::translate(glm::mat4(1.0f), glm::vec3(i*0.4f, j, 0.4f*k));
                    meshes.push_back(mat2);
                }
            }
        }
    }
    return meshes;
}

ThimkaScene::ThimkaScene(GLFWwindow *window, Gui* gui, std::string assetspath) : Scene(window, gui)
{
    this->assetspath = assetspath;
    meshes = SetupData(4, 4, 10);

    for(int i = 0; i < meshes.size(); i++){
        meshes[i] = meshes[i] * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        meshes[i] = glm::scale(meshes[i], glm::vec3(0.2f));
    }

    texture = new Texture((assetspath+"/textures/raider_sword_Mat_Base_Color.png").data(), 0);
    
    texture->Bind(0);   

    sb = new StorageBuffer(meshes.data(), meshes.size()*sizeof(glm::mat4), GL_STREAM_READ, 3);
    
    shader = new Shader((assetspath+"/shaders/objfrag.glsl").data(), (assetspath+"/shaders/objvert.glsl").data());
    if(!shader->GetStatus()){
        printf("Shader1 failed!\n");
        exit(0);
    }
    shader->Use();

    shaders.push_back(shader);

    int width = 0;
    int height = 0;

    glfwGetWindowSize(window, &width, &height);
    camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 0.01f, 1000.0f, &shaders);
    plane = new Mesh((assetspath+"/objs/sword.obj").data());
}

void ThimkaScene::Update(float dt)
{
   
}

void ThimkaScene::Draw()
{
    plane->Draw(&renderer, shader, meshes.size());
}

void ThimkaScene::onGui(float dt)
{
    ImGui::Text("FTime: %.3f", dt);
    ImGui::Text("FPS: %.f", 1.0f / dt);
}

ThimkaScene *ThimkaScene::create(GLFWwindow *window, Gui *gui, std::string assetspath)
{
    return new ThimkaScene(window, gui, assetspath);
}

void ThimkaScene::End()
{
    delete texture;
    delete sb;
    delete shader;
    delete plane;
}
