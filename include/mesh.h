#pragma once
#include <vector>
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "renderer.h"

enum class MeshPrimitive{
    Cube
};


class Mesh
{
    struct Mesh_Vertex
    {
        float postion[3];
        float uv[2];
    };

    struct Mesh_Triangle
    {
        unsigned int indexes[3];
    };

private:
    std::vector<Mesh_Vertex> vertices;
    std::vector<Mesh_Triangle> triangles;
    VertexArray *va;
    VertexBuffer *vb;
    IndexBuffer *ib;
    ArrayLayout aly;

public:
    Mesh(std::vector<Mesh_Vertex> verts, std::vector<Mesh_Triangle> triangle);
    Mesh(MeshPrimitive primitive);
    void Setup();
    void AddVertex(Mesh_Vertex vert);
    void AddTriangle(Mesh_Triangle triangle);
    void SetVertices(std::vector<Mesh_Vertex> verts);
    void SetTriangles(std::vector<Mesh_Triangle> triangle);
    /// @brief Expects the shader on to be in use
    /// @param render 
    /// @param shader 
    void Draw(Renderer &render, Shader &shader);
    ~Mesh();
};