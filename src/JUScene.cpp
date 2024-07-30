#include "JUScene.h"

siv::BasicPerlinNoise<float> noise;

bool isEnabled(float x, float y, float z, float scale){
    float n = noise.noise3D(x*scale, y*scale, z*scale);
    return n > 0.0f;
}
void SetupData(std::vector<Mat4>& meshes, float x, float y, float z, float scale){
    
    meshes.clear();
    std::random_device rd;
    std::uniform_real_distribution<float> tdist(-y/2.0f, y/2.0f);
    std::uniform_real_distribution<float> rdist(-3.14f, 3.14f);

    for (float i = -x/2.0f; i < x/2.0f; i++)
    {
        for (float j = -z/2.0f; j < z/2.0f; j++)
        {
            for (float k = -y/2.0f; k < y/2.0f; k++)
            {
                    // glm::mat4 mat2 = glm::rotate(glm::mat4(1.0f), rdist(rd), glm::vec3(1.0f, 0.0f, 0.0f));
                    // mat2 = glm::rotate(mat2, rdist(rd), glm::vec3(0.0f, 1.0f, 0.0f));
                    // mat2 = glm::rotate(mat2, rdist(rd), glm::vec3(0.0f, 0.0f, 1.0f));
                    glm::mat4 mat2 = glm::mat4(1.0f);
                    mat2 = glm::translate(mat2, glm::vec3(i, k, j));
                    Mat4 mat4;
                    mat4.data[0] = mat2[0][0];
                    mat4.data[1] = mat2[0][1];
                    mat4.data[2] = mat2[0][2];
                    mat4.data[3] = mat2[0][3];
                    mat4.data[4] = mat2[1][0];
                    mat4.data[5] = mat2[1][1];
                    mat4.data[6] = mat2[1][2];
                    mat4.data[7] = mat2[1][3];
                    mat4.data[8] = mat2[2][0];
                    mat4.data[9] = mat2[2][1];
                    mat4.data[10] = mat2[2][2];
                    mat4.data[11] = mat2[2][3];
                    mat4.data[12] = mat2[3][0];
                    mat4.data[13] = mat2[3][1];
                    mat4.data[14] = mat2[3][2];
                    mat4.data[15] = mat2[3][3];
                    meshes.push_back(mat4);
            }
        }
    }
}

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
    noise = siv::BasicPerlinNoise<float>();
    lightcolor = glm::vec3(1.0f, 1.0f, 1.0f);
    lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
    skybox = new Mesh((assetspath+"/objs/cube.obj").data(), true);
    // light = new Mesh((assetspath+"/objs/sphere.obj").data(), true);
    obj = new Mesh((assetspath+"/objs/plane.obj").data(), true);
    SetupData(meshes, 10.0f, 1.0f, 50.0f, 0.1f);


    std::vector<std::string> faces = {
        (assetspath+"/textures/cube/px.jpg").data(),
        (assetspath+"/textures/cube/nx.jpg").data(),
        (assetspath+"/textures/cube/py.jpg").data(),
        (assetspath+"/textures/cube/ny.jpg").data(),
        (assetspath+"/textures/cube/pz.jpg").data(),
        (assetspath+"/textures/cube/nz.jpg").data(),
    };

   texID = loadCubemap(faces);

   texture = new Texture((assetspath+"/textures/galaxy.jpg").data(), 1);
   texture->Bind(1);

   
    skyboxshader = new Shader((assetspath+"/shaders/skyboxfrag.glsl").data(), (assetspath+"/shaders/skyboxvert.glsl").data());
    if(!skyboxshader->GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }
    skyboxshader->Use();
    skyboxshader->SetUniform1i("skybox", 0);
    shaders.push_back(skyboxshader);
    

    objshader = new Shader((assetspath+"/shaders/objfrag.glsl").data(), (assetspath+"/shaders/objvert.glsl").data());
    if(!objshader->GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }
    objshader->Use();

    
    shaders.push_back(objshader);
    objshader->SetUniform1i("u_texture", texture->GetSlotID());
    objshader->SetUniform1f("scale", 0.1f);

    int height, width;
    glfwGetWindowSize(window, &width, &height);
    camera = new Camera(width, height, glm::vec3(0.0f, 0.0f, 10.0f), 45.0f, 0.001f, 50000.0f, &shaders);
    skybox->Scale(glm::vec3(5000.0f, 5000.0f, 5000.0f));

    sb = new StorageBuffer(meshes.data(), meshes.size()*sizeof(Mat4), GL_STREAM_READ, 3);
    sb->Bind();

    AddMouseWheelCallback([&](double xoff, double yoff){
        float sp = this->GetCamera()->GetSpeed();
        if(sp+(float)yoff > 0.7f){
            this->GetCamera()->SetSpeed(sp+(float)yoff);
        }

    });
}

void JUScene::Update(float dt)
{
    objshader->Use();
    objshader->SetUniform1f("time", gui->GetGame()->GetTime());
}

void JUScene::Draw()
{
    //glDepthMask(GL_FALSE);
    // skyboxshader->Use();
    // skybox->Draw(&renderer, skyboxshader);
    objshader->Use();
    obj->Draw(&renderer, objshader, meshes.size());
}

void JUScene::onGui(float dt)
{
    ImGui::Text("FTime: %.3f", dt);
    ImGui::Text("FPS: %.f", 1.0f / dt);
    ImGui::Text("Objects: %lu", meshes.size());
    ImGui::Text("Memory: %lu", meshes.size()*sizeof(Mat4));
    static float scale = 0.1f;

    if(ImGui::InputFloat("Scale", &scale, 0.01f)){
        objshader->Use();
        objshader->SetUniform1f("scale", scale);
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

    delete objshader;
    delete skybox;
    delete obj;
    delete texture;
    delete sb;
}

Camera *JUScene::GetCamera()
{
    return camera;
}
