#include "storagebuffer.h"

StorageBuffer::StorageBuffer(void *data, unsigned long size, GLuint usage, GLuint bind)
{
    GLDEBUGCALL(glGenBuffers(1, &m_ID));
    GLDEBUGCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ID));
    GLDEBUGCALL(glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, usage));
    GLDEBUGCALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bind, m_ID));
    GLDEBUGCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
    this->bind = bind;
}

void StorageBuffer::SetData(unsigned long off, void *data, unsigned long size)
{
    GLDEBUGCALL(glBufferSubData(GL_SHADER_STORAGE_BUFFER, off, size, data));
}

void StorageBuffer::Bind()
{
    GLDEBUGCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ID));
}

void StorageBuffer::UnBind()
{
    GLDEBUGCALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));
}

StorageBuffer::~StorageBuffer()
{
    GLDEBUGCALL(glDeleteBuffers(1, &m_ID));
}
