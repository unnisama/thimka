#pragma once
#include <GL/glew.h>
#include "debug.h"
#include <stddef.h>

class StorageBuffer{

private:
    GLuint m_ID;
    GLuint bind;

public:
    StorageBuffer(void *data, unsigned long size, GLuint usage,  GLuint bind);
    void SetData(unsigned long off, void *data, unsigned long size);
    void Bind();
    void UnBind();
    ~StorageBuffer();
};
