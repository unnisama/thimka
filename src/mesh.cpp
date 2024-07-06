#include "mesh.h"

Mesh::Mesh(std::vector<Mesh_Vertex> verts, std::vector<Mesh_Triangle> indexes)
{
    vertices = verts;
    triangles = indexes;
    Init();
}

Mesh::Mesh(MeshPrimitive primitive)
{
    if (primitive == MeshPrimitive::Cube)
    {
        std::vector<Mesh_Vertex> verts = {
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}},
            
            {{-0.5f, -0.5f,  -0.5f}, {0.0f, 1.0f}},
            {{ 0.5f, -0.5f,  -0.5f}, {1.0f, 1.0f}}
        };
        std::vector<Mesh_Triangle> tris = {
            {0, 1, 2},
            {2, 3, 0},

            {4, 5, 6},
            {6, 7, 4},

            {1, 5, 6},
            {6, 2, 1},

            {0, 4, 7},
            {7, 3, 0},

            {0, 1, 9},
            {9, 8, 0},

            {3, 2, 10},
            {10, 11, 3}
        };
        vertices = verts;
        triangles = tris;
        Init();
    }
}

void Mesh::Init()
{
    aly.AddFloat(3);
    aly.AddFloat(2);
    va = new VertexArray(&aly);
    va->Bind();
    Setup();
    va->Enable();
    va->Unbind();
}

void Mesh::Setup()
{
    // no way only one get destroyed
    if (ib != nullptr)
    {
        delete ib;
        delete vb;
    }

    vb = new VertexBuffer(vertices.data(), vertices.size() * sizeof(Mesh_Vertex), GL_STREAM_DRAW);
    ib = new IndexBuffer(triangles.data(), triangles.size() * 3, GL_STREAM_DRAW);
}

void Mesh::AddVertex(Mesh_Vertex vert)
{
    va->Bind();
    vertices.push_back(vert);
    Setup();
    va->Unbind();
}

void Mesh::AddTriangle(Mesh_Triangle triangle)
{
    va->Bind();
    triangles.push_back(triangle);
    Setup();
    va->Unbind();
}

void Mesh::SetVertices(std::vector<Mesh_Vertex> verts)
{
    va->Bind();
    vertices = verts;
    if (vb != nullptr)
    {
        delete vb;
    }
    vb = new VertexBuffer(vertices.data(), vertices.size() * sizeof(Mesh_Vertex), GL_STREAM_DRAW);
    va->Unbind();
}

void Mesh::SetTriangles(std::vector<Mesh_Triangle> indexes)
{
    va->Bind();
    triangles = indexes;
    if (ib != nullptr)
    {
        delete ib;
    }
    ib = new IndexBuffer(triangles.data(), triangles.size() * 3, GL_STREAM_DRAW);
    va->Unbind();
}

void Mesh::Translate(glm::vec3 t)
{
    model = glm::translate(model, t);
}

void Mesh::Draw(Renderer &render, Shader &shader)
{
    shader.SetMat4f("umodel", model);
    render.Draw(*va, *ib, shader);
}

void Mesh::Draw(Renderer &render, Shader &shader, int count)
{
    render.DrawInstanced(*va, *ib, shader, count);
}

Mesh::~Mesh()
{
    delete ib;
    delete vb;
    delete va;
}
