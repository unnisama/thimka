#include <renderer.h>

void Renderer::Draw(VertexArray &va, IndexBuffer &ib, Shader &shader)
{
    va.Bind();
    GLDEBUGCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(VertexArray &va, size_t vertices, Shader &shader)
{
    va.Bind();
    GLDEBUGCALL(glDrawArrays(GL_TRIANGLES, 0, vertices));
}

void Renderer::DrawInstanced(VertexArray &va, IndexBuffer &ib, Shader &shader, int count)
{
    va.Bind();
    GLDEBUGCALL(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, count));
}
