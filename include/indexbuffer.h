#pragma once
#include "debug.h"

class IndexBuffer
{
private:
    uint32_t m_ID;
    uint32_t count;

public:
    IndexBuffer(void *data, size_t count);
    ~IndexBuffer();

    void Bind() const;

    void UnBind() const;

    uint32_t GetCount() const;

    uint32_t GetID() const;
};