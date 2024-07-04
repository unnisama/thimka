#include "mesh.h"

Mesh::Mesh(std::vector<Mesh_Vertex> verts, std::vector<Mesh_Triangle> indexes)
{
    aly.AddFloat(3);
    aly.AddFloat(2);
    vertices = verts;
    triangles = indexes;
    va = new VertexArray(&aly);
    Setup();
    va->Unbind();
}

Mesh::Mesh(MeshPrimitive primitive)
{
    if(primitive == MeshPrimitive::Cube){
        
    }
}

void Mesh::Setup()
{
    // no way only one get destroyed
    if(ib != nullptr){
        delete ib;
        delete vb;
    }
    
    vb = new VertexBuffer(vertices.data(), vertices.size(), GL_STREAM_DRAW);
    ib = new IndexBuffer(triangles.data(), triangles.size(), GL_STREAM_DRAW);
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
    if(vb != nullptr){
        delete vb;
    }
    vb = new VertexBuffer(vertices.data(), vertices.size(), GL_STREAM_DRAW);
    va->Unbind();
}

void Mesh::SetTriangles(std::vector<Mesh_Triangle> indexes)
{
    va->Bind();
    triangles = indexes;
    if(ib != nullptr){
        delete ib;
    }
    ib = new IndexBuffer(triangles.data(), triangles.size(), GL_STREAM_DRAW);
    va->Unbind();
}

void Mesh::Draw(Renderer &render, Shader &shader)
{
    render.Draw(*va, *ib, shader);
}

Mesh::~Mesh()
{
    delete ib;
    delete vb;
    delete va;
}
