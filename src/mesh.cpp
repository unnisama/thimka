#include "mesh.h"
#include <map>

std::vector<std::string> Split(std::string str, std::string s){
    std::vector<std::string> strs;
    std::stringstream ss;

    int index = 0;

    for(int i = 0; i < str.size(); i++){

        if(str[i] == s[index]){
            if(index == 0){
                strs.push_back(ss.str());
                ss.str("");
            }

            if(index+1 < s.size()){
                index += 1;
            }
        }else{
            ss << str[i];
            index = 0;
        }
    }
    strs.push_back(ss.str());
    return strs;
}

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
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}}, 
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},

            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}}
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
    }else if(primitive == MeshPrimitive::Plane){
        std::vector<Mesh_Vertex> verts = {
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}
        };
        std::vector<Mesh_Triangle> tris = {
            {0, 1, 2},
            {2, 3, 0},
        };
        vertices = verts;
        triangles = tris;
        Init();
    }
}

Mesh::Mesh(const char *path, bool doInit)
{
    std::vector<glm::vec3> verts;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::map<std::string, int> fdata;
    std::ifstream f(path);
    if(!f.good()){
        exit(-1);
    }

    std::string line;

    while(std::getline(f, line)){
        if(line.find("v ") == 0){
            line = line.substr(2, line.size()-2);
            std::vector<std::string> strs = Split(line, " ");
            verts.push_back(glm::vec3(std::stof(strs[0]), std::stof(strs[1]), std::stof(strs[2])));
        }
        else if(line.find("vt ") == 0){
            line = line.substr(3, line.size()-3);
            std::vector<std::string> strs = Split(line, " ");
            uvs.push_back(glm::vec2(std::stof(strs[0]), std::stof(strs[1])));
        }
        else if(line.find("vn ") == 0){
            line = line.substr(3, line.size()-3);
            std::vector<std::string> strs = Split(line, " ");
            normals.push_back(glm::vec3(std::stof(strs[0]), std::stof(strs[1]), std::stof(strs[2])));
        }
        else if(line.find("f ") == 0){
            line = line.substr(2, line.size()-2);
            std::vector<std::string> strs = Split(line, " ");
            if(fdata.find(strs[0]) == fdata.end()){
                auto st = Split(strs[0], "/");
                Mesh_Vertex vert;
                glm::vec3 vt = verts[std::stoi(st[0])-1];
                glm::vec2 uv = uvs[std::stoi(st[1])-1];
                glm::vec3 n = normals[std::stoi(st[2])-1];
                vert.postion[0] = vt.x;
                vert.postion[1] = vt.y;
                vert.postion[2] = vt.z;
                vert.uv[0] = uv.x;
                vert.uv[1] = uv.y;
                vert.normal[0] = n.x;
                vert.normal[1] = n.y;
                vert.normal[2] = n.z;
                fdata[strs[0]] = vertices.size();
                vertices.push_back(vert);
            }
            if(fdata.find(strs[1]) == fdata.end()){
                auto st = Split(strs[1], "/");
                Mesh_Vertex vert;
                glm::vec3 vt = verts[std::stoi(st[0])-1];
                glm::vec2 uv = uvs[std::stoi(st[1])-1];
                glm::vec3 n = normals[std::stoi(st[2])-1];
                vert.postion[0] = vt.x;
                vert.postion[1] = vt.y;
                vert.postion[2] = vt.z;
                vert.uv[0] = uv.x;
                vert.uv[1] = uv.y;
                vert.normal[0] = n.x;
                vert.normal[1] = n.y;
                vert.normal[2] = n.z;
                fdata[strs[1]] = vertices.size();
                vertices.push_back(vert);
            }
            if(fdata.find(strs[2]) == fdata.end()){
                auto st = Split(strs[2], "/");
                Mesh_Vertex vert;
                glm::vec3 vt = verts[std::stoi(st[0])-1];
                glm::vec2 uv = uvs[std::stoi(st[1])-1];
                glm::vec3 n = normals[std::stoi(st[2])-1];
                vert.postion[0] = vt.x;
                vert.postion[1] = vt.y;
                vert.postion[2] = vt.z;
                vert.uv[0] = uv.x;
                vert.uv[1] = uv.y;
                vert.normal[0] = n.x;
                vert.normal[1] = n.y;
                vert.normal[2] = n.z;
                fdata[strs[2]] = vertices.size();
                vertices.push_back(vert);
            }
            Mesh_Triangle tri;
            tri.indexes[0] = fdata[strs[0]];
            tri.indexes[1] = fdata[strs[1]];
            tri.indexes[2] = fdata[strs[2]];
            triangles.push_back(tri);
        }
    }
    if(doInit){
        Init();
    }
}

void Mesh::Init()
{
    aly.AddFloat(3);
    aly.AddFloat(2);
    aly.AddFloat(3);
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

void Mesh::Scale(glm::vec3 t)
{
    model = glm::scale(model, t);
}
void Mesh::Draw(Renderer *render, Shader *shader)
{
    shader->SetMat4f("umodel", model);
    render->Draw(*va, *ib);
}

void Mesh::Draw(Renderer *render, Shader *shader, int count)
{
    render->DrawInstanced(*va, *ib, count);
}

Mesh::~Mesh()
{
    delete ib;
    delete vb;
    delete va;
}
