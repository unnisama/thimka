#pragma once
#include <GL/glew.h>
#include "debug.h"

class StorageBuffer{

private:
    GLuint m_ID;
    GLuint bind;

public:
    StorageBuffer(void *data, size_t size, GLuint usage,  GLuint bind);
    void Bind();
    void UnBind();
    ~StorageBuffer();
};
