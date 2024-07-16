#include "JUScene.h"

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}  

JUScene::JUScene(GLFWwindow *window, Gui *gui, std::string assetspath) : Scene(window, gui)
{
    lightcolor = glm::vec3(1.0f, 1.0f, 1.0f);
    lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
    skybox = new Mesh((assetspath+"/objs/cube.obj").data(), true);
    light = new Mesh((assetspath+"/objs/sphere.obj").data(), true);
    obj = new Mesh((assetspath+"/objs/sword.obj").data(), true);
 
    
    std::vector<std::string> faces = {
        (assetspath+"/textures/cube/px.jpg").data(),
        (assetspath+"/textures/cube/nx.jpg").data(),
        (assetspath+"/textures/cube/py.jpg").data(),
        (assetspath+"/textures/cube/ny.jpg").data(),
        (assetspath+"/textures/cube/pz.jpg").data(),
        (assetspath+"/textures/cube/nz.jpg").data(),
    };

   texID = loadCubemap(faces);

    texture = new Texture((assetspath+"/textures/FS_Sw_Tex_BaseColor.png").data(), 1);
    texture->Bind(1);

    normal = new Texture((assetspath+"/textures/FS_Sw_Tex_Normal.png").data(), 2);
    normal->Bind(2);

   
    skyboxshader = new Shader((assetspath+"/shaders/skyboxfrag.glsl").data(), (assetspath+"/shaders/skyboxvert.glsl").data());
    if(!skyboxshader->GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }
    skyboxshader->Use();
    skyboxshader->SetUniform1i("skybox", 0);
    shaders.push_back(skyboxshader);
    lightshader = new Shader((assetspath+"/shaders/lightfrag.glsl").data(), (assetspath+"/shaders/lightvert.glsl").data());
    if(!lightshader->GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }
    lightshader->Use();
    lightshader->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);
    shaders.push_back(lightshader);

    objshader = new Shader((assetspath+"/shaders/objfrag.glsl").data(), (assetspath+"/shaders/objvert.glsl").data());
    if(!objshader->GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }
    objshader->Use();
    objshader->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);
    objshader->SetUniform1i("u_texture", texture->GetSlotID());
    objshader->SetUniform1i("u_normal", normal->GetSlotID());
    shaders.push_back(objshader);

    int height, width;
    glfwGetWindowSize(window, &width, &height);
    camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 10.0f), 45.0f, 0.001f, 1000.0f, &shaders);
    skybox->Scale(glm::vec3(100.0f, 100.0f, 100.0f));
}

void JUScene::Update(float dt)
{
    
}

void JUScene::Draw()
{
    skyboxshader->Use();
    skybox->Draw(&renderer, skyboxshader);
    lightshader->Use();
    light->Draw(&renderer, lightshader);
    objshader->Use();
    obj->Draw(&renderer, objshader);
}

void JUScene::onGui(float dt)
{
    ImGui::Text("FTime: %.3f", dt);
    ImGui::Text("FPS: %.f", 1.0f / dt);
    
    if(ImGui::DragFloat3("Light Position", glm::value_ptr(lightPos), 0.01f, -20.0f, 20.0f)){
        light->model[3][0] = lightPos.x;
        light->model[3][1] = lightPos.y;
        light->model[3][2] = lightPos.z;
        objshader->Use();
        objshader->SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
    }
    if(ImGui::ColorEdit3("Light Color", glm::value_ptr(lightcolor))){
        lightshader->Use();
        lightshader->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);
        objshader->Use();
        objshader->SetUniform3f("lightcolor", lightcolor.r, lightcolor.g, lightcolor.b);
    }
}

JUScene *JUScene::create(GLFWwindow *window, Gui *gui, std::string assetspath)
{
    return new JUScene(window, gui, assetspath);
}

void JUScene::End()
{
    GLDEBUGCALL(glDeleteTextures(1, &texID));
    delete skyboxshader;
    delete lightshader;
    delete objshader;
    delete skybox;
    delete obj;
    delete light;
    delete texture;
    delete normal;
}
