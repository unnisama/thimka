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
};