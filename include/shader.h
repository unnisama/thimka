#pragma once
#include "debug.h"
#include <string>
#include <fstream>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>
#include <unordered_map>


class Shader{
private:
    unsigned int vs;
    unsigned int fs;
    unsigned int program;
    bool status;
    std::unordered_map<const char *, GLuint> uniformStored;
public:
    Shader(const char *fragpath, const char *vertpath);
    void Delete();
    bool LogError();
    GLuint GetUniformLocation(const GLchar *name);
    void SetUniform1f(const GLchar *name, float v);
    void SetUniform4f(const GLchar *name, float v0, float v1, float v2, float v3);
    void SetUniform1i(const GLchar *name, int v);
    ~Shader();

    static std::string readFile(const char *path);
    bool GetStatus();
    void Use();
};