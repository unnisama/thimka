#pragma once
#include "debug.h"

class VertexBuffer
{
private:
    uint32_t m_ID;
    size_t size;

public:
    VertexBuffer(void *data, size_t size, GLenum usage);
    ~VertexBuffer();

    void Bind() const;

    void UnBind() const;

    uint32_t GetID() const;
};