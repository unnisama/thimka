#include "vertexarray.h"

VertexArray::VertexArray(VertexBuffer *vb, ArrayLayout* layout)
{
    GLDEBUGCALL(glGenVertexArrays(1, &m_ID));
    GLDEBUGCALL(glBindVertexArray(m_ID));
    this->vb = vb;
    this->layout = layout;
}

void ArrayLayout::AddFloat(GLuint count)
{
    layout.push_back({GL_FLOAT, count, false});
    m_stride += 4 * count;
}

void ArrayLayout::AddInt(GLuint count)
{
    layout.push_back({GL_UNSIGNED_INT, count, false});
    m_stride += 4 * count;
}

void ArrayLayout::AddByte(GLuint count)
{
    layout.push_back({GL_UNSIGNED_BYTE, count, false});
    m_stride += 1 * count;
}

size_t ArrayLayout::GetStride()
{
    return m_stride;
}

std::vector<VertexArrayLayout> &ArrayLayout::GetElements()
{
    return layout;
}

void VertexArray::Bind()
{
    GLDEBUGCALL(glBindVertexArray(m_ID));
}

void VertexArray::Unbind()
{
    GLDEBUGCALL(glBindVertexArray(0));
}

void VertexArray::SetAttribs()
{
    auto &elements = layout->GetElements();
    size_t size = 0;
    for(int i = 0; i < elements.size(); i++){
        auto &element = elements[i];
        GLDEBUGCALL(glEnableVertexAttribArray(i));
        GLDEBUGCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->GetStride(), (void *)size));
        size += TypeToSize(element.type) * element.count;
    }
}

void VertexArray::Enable()
{
    Bind();
    vb->Bind();
    SetAttribs();
}

size_t VertexArray::TypeToSize(GLuint type)
{
    switch (type)
    {
    case GL_FLOAT: return 4;
        break;
    case GL_UNSIGNED_INT: return 4;
        break;
    case GL_UNSIGNED_BYTE: return 1;
        break;
    default:
        break;
    }
    return 1;
}

VertexArray::~VertexArray()
{
    GLDEBUGCALL(glDeleteVertexArrays(1, &m_ID));
}
