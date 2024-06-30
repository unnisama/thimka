#include "indexbuffer.h"

IndexBuffer::IndexBuffer(void *data, size_t count)
{
    this->count = count;
    GLDEBUGCALL(glGenBuffers(1, &m_ID));
    GLDEBUGCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
    GLDEBUGCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, data, GL_STREAM_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLDEBUGCALL(glDeleteBuffers(1, &m_ID));
}

void IndexBuffer::Bind() const
{
    GLDEBUGCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::UnBind() const
{
    GLDEBUGCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

uint32_t IndexBuffer::GetCount() const
{
    return count;
}

uint32_t IndexBuffer::GetID() const
{
    return m_ID;
}
