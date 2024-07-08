#include <renderer.h>

void Renderer::Draw(VertexArray &va, IndexBuffer &ib)
{
    va.Bind();
    GLDEBUGCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(VertexArray &va, unsigned long vertices)
{
    va.Bind();
    GLDEBUGCALL(glDrawArrays(GL_TRIANGLES, 0, vertices));
}

void Renderer::DrawInstanced(VertexArray &va, IndexBuffer &ib, int count)
{
    va.Bind();
    GLDEBUGCALL(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, count));
}
