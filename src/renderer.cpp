#include <renderer.h>

void Renderer::Draw(VertexArray &va, IndexBuffer &ib, Shader &shader)
{
    va.Bind();
    ib.Bind();
    GLDEBUGCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(VertexArray &va, size_t vertices, Shader &shader)
{
    va.Bind();
    GLDEBUGCALL(glDrawArrays(GL_TRIANGLES, 0, vertices));
}
