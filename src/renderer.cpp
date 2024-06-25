#include <renderer.h>

void Renderer::Draw(VertexArray &va, IndexBuffer &ib, Shader &shader)
{
    va.Bind();
    ib.Bind();
    GLDEBUGCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
