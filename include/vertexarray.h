#pragma once
#include "renderer.h"
#include "vertexbuffer.h"
#include <vector>

struct VertexArrayLayout
{
    GLuint type;
    GLuint count;
    GLuint normalized;
};

class ArrayLayout{

private:
    size_t m_stride = 0;
    std::vector<VertexArrayLayout> layout;
public:
    void AddFloat(GLuint count);
    void AddInt(GLuint count);
    void AddByte(GLuint count); 
    size_t GetStride();
    std::vector<VertexArrayLayout> &GetElements();
};

class VertexArray{
private:
    GLuint m_ID; 
    ArrayLayout* layout;
    VertexBuffer *vb;
    
public:
    VertexArray(VertexBuffer *vb, ArrayLayout* layout);
    void Bind();
    void Unbind();
    void SetAttribs();
    void Enable();
    size_t TypeToSize(GLuint type);
    ~VertexArray();
};