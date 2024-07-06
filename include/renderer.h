#pragma once
#include <GL/glew.h>
#include <stdio.h>
#include <iostream>
#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"

class Renderer{
public:
    void Draw(VertexArray &va, IndexBuffer& ib, Shader& shader);
    void Draw(VertexArray &va, size_t vertices, Shader &shader);
    void DrawInstanced(VertexArray &va, IndexBuffer &ib, Shader &shader, int count);
};