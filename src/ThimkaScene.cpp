#include "ThimkaScene.h"

inline bool isEnabled(int x, int y, int z){
    return true;
}
inline std::vector<glm::mat4> SetupData(float x, float y, float z){
    std::vector<glm::mat4> meshes;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                if(isEnabled(i, j, k) == true){
                    glm::mat4 mat2 = glm::translate(glm::mat4(1.0f), glm::vec3(i, j, k*3.0f));
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
    meshes = SetupData(1, 1, 1);
    lightPos = glm::vec3(2.0f, 2.0f, 2.0f);
    lightcolor = glm::vec3(1.0f, 1.0f, 1.0f);

    for(int i = 0; i < meshes.size(); i++){
        meshes[i] = glm::scale(meshes[i], glm::vec3(10.0f, 10.0f, 10.0f));
        meshes[i] = meshes[i] * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    texture = new Texture((assetspath+"/textures/FS_Sw_Tex_BaseColor.png").data(), 0);
    texture->Bind(0);

    texture1 = new Texture((assetspath+"/textures/FS_Sw_Tex_Normal.png").data(), 1);
    texture1->Bind(1);

    sb = new StorageBuffer(meshes.data(), meshes.size()*sizeof(glm::mat4), GL_STREAM_READ, 3);
    
    shader = new Shader((assetspath+"/shaders/objfrag.glsl").data(), (assetspath+"/shaders/objvert.glsl").data());
    if(!shader->GetStatus()){
        printf("Shader1 failed!\n");
        exit(0);
    }
    shader->Use();

    shader->SetUniform1i("u_texture", texture->GetSlotID());
    shader->SetUniform1i("u_normal", texture1->GetSlotID());
    shader->SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
    shader->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);

    shaders.push_back(shader);

    shader1 = new Shader((assetspath+"/shaders/lightfrag.glsl").data(), (assetspath+"/shaders/lightvert.glsl").data());
    if(!shader1->GetStatus()){
        printf("Shader1 failed!\n");
        exit(0);
    }
    shader1->Use();
    shader1->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);


    shaders.push_back(shader1);

    int width = 0;
    int height = 0;

    glfwGetWindowSize(window, &width, &height);
    camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 0.01f, 1000.0f, &shaders);

    plane = new Mesh((assetspath+"/objs/plane.obj").data(), true);

    light = new Mesh((assetspath+"/objs/cube.obj").data(), true);

    light->Scale(glm::vec3(0.2f, 0.2f, 0.2f));
    light->model[3][0] = lightPos.x;
    light->model[3][1] = lightPos.y;
    light->model[3][2] = lightPos.z;

    sb->Bind();
}

void ThimkaScene::Update(float dt)
{
    for(int i = 0; i < meshes.size(); i++){
        meshes[i] = glm::rotate(meshes[i], freq * dt, glm::vec3(1.0f, 0.0f, 0.0f));
        sb->SetData(i*sizeof(glm::mat4), &meshes[i], sizeof(glm::mat4));
    }

}

void ThimkaScene::Draw()
{
    shader->Use();
    plane->Draw(&renderer, shader, meshes.size());
    shader1->Use();
    light->Draw(&renderer, shader1);
}

void ThimkaScene::onGui(float dt)
{
    ImGui::Text("FTime: %.3f", dt);
    ImGui::Text("FPS: %.f", 1.0f / dt);

    ImGui::DragFloat("Freq", &freq, 0.01f, -3.0f, 3.0f);
    
    if(ImGui::DragFloat3("Light Position", glm::value_ptr(lightPos), 0.01f, -20.0f, 20.0f)){
        light->model[3][0] = lightPos.x;
        light->model[3][1] = lightPos.y;
        light->model[3][2] = lightPos.z;
        shader->Use();
        shader->SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
    }
    if(ImGui::ColorEdit3("Light Color", glm::value_ptr(lightcolor))){
        shader1->Use();
        shader1->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);
        shader->Use();
        shader->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);
    }
    
}

ThimkaScene *ThimkaScene::create(GLFWwindow *window, Gui *gui, std::string assetspath)
{
    return new ThimkaScene(window, gui, assetspath);
}

void ThimkaScene::End()
{
    delete texture;
    delete texture1;
    delete sb;
    delete shader;
    delete shader1;
    delete plane;
}
