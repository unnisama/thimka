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
    GLuint slotid;
public:
    Texture(const char *path, unsigned int slot);
    ~Texture();
    void Bind(unsigned int slot);
    inline int getWidth() const { return m_Width; };
    inline int getHeight() const { return m_Height; };
    void UnBind();
    inline GLuint GetSlotID() const {
        return slotid;
    };

};