#pragma once
#include <GL/glew.h>
#include "stb_image.h"
#include "debug.h"

class Texture{
private:
    int m_Width;
    int m_Height;
    GLuint m_ID;
    unsigned char *data;
    int m_BPP;
public:
    Texture(const char *path);
    ~Texture();
    void Bind(unsigned int slot);
    void UnBind();

};