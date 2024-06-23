#include "vertexbuffer.h"

VertexBuffer::VertexBuffer(void *data, size_t size)
{
    this->size = size;
    GLDEBUGCALL(glGenBuffers(1, &m_ID));
    GLDEBUGCALL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
    GLDEBUGCALL(glBufferData(GL_ARRAY_BUFFER, size, (void *)data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLDEBUGCALL(glDeleteBuffers(1, &m_ID));
}

void VertexBuffer::Bind() const
{
    GLDEBUGCALL(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VertexBuffer::UnBind() const
{
    GLDEBUGCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

uint32_t VertexBuffer::GetID() const
{
    return m_ID;
}
