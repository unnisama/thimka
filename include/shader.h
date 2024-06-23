#pragma once
#include "renderer.h"
#include <string>
#include <fstream>
#include <GLFW/glfw3.h>
#include <sstream>


class Shader{
private:
    unsigned int vs;
    unsigned int fs;
    unsigned int program;
    bool status;
public:
    Shader(const char *fragpath, const char *vertpath);
    void Delete();
    bool LogError();
    ~Shader();

    static std::string readFile(const char *path);
    bool GetStatus();
    void Use();
};