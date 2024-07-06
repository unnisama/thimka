#pragma once
#include <vector>
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "renderer.h"

enum class MeshPrimitive{
    Cube
};

struct Mesh_Vertex
    {
        float postion[3];
        float uv[2];
    };

    struct Mesh_Triangle
    {
        unsigned int indexes[3];
    };

class Mesh
{
private:
    std::vector<Mesh_Vertex> vertices;
    std::vector<Mesh_Triangle> triangles;
    VertexArray *va = nullptr;
    VertexBuffer *vb = nullptr;
    IndexBuffer *ib = nullptr;
    ArrayLayout aly;
    glm::mat4 model{1.0f};

public:
    Mesh(std::vector<Mesh_Vertex> verts, std::vector<Mesh_Triangle> triangle);
    Mesh(MeshPrimitive primitive);
    void Init();
    void Setup();
    void AddVertex(Mesh_Vertex vert);
    void AddTriangle(Mesh_Triangle triangle);
    void SetVertices(std::vector<Mesh_Vertex> verts);
    void SetTriangles(std::vector<Mesh_Triangle> triangle);
    void Translate(glm::vec3 t);
    /// @brief Expects the shader on to be in use
    /// @param render 
    /// @param shader 
    void Draw(Renderer &render, Shader &shader);
    void Draw(Renderer &render, Shader &shader, int count);
    ~Mesh();
};