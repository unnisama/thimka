#include "texture.h"

Texture::Texture(const char *path)
{
    stbi_set_flip_vertically_on_load(1);

    data = stbi_load(path, &m_Width, &m_Height, &m_BPP, 4);
    if(!data){
        printf("Couldn't load %s\n", path);
        exit(-1);
    }
    // Generating ID
    GLDEBUGCALL(glGenTextures(1, &m_ID));
    // Binding 
    GLDEBUGCALL(glBindTexture(GL_TEXTURE_2D, m_ID));

    // setting params
    GLDEBUGCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLDEBUGCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // S -> like x and T -> like y
    GLDEBUGCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLDEBUGCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    // storing on vram
    GLDEBUGCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));

    GLDEBUGCALL(glBindTexture(GL_TEXTURE_2D, 0));

    stbi_image_free(data);
}

Texture::~Texture()
{
    GLDEBUGCALL(glDeleteTextures(1, &m_ID));
}

void Texture::Bind(unsigned int slot)
{
    GLDEBUGCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLDEBUGCALL(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture::UnBind()
{
    GLDEBUGCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
