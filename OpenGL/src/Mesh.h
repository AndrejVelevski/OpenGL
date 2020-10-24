#pragma once
#include <vector>
#include "Vertex.h"
#include "Material.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Camera.h"
#include "Light.h"

class Mesh
{
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> elements;
    Material* material;

    VertexArray vao;
    Buffer vbo;
    Buffer ebo;

public:
    Mesh();
    ~Mesh();
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& elements, Material* material);
    void create(std::vector<Vertex>& vertices, std::vector<unsigned int>& elements, Material* material);
    void draw(Shader* shader);

    static Mesh* generate_plane(Material* material);
    static Mesh* generate_cube(Material* material);
    static Mesh* generate_uvsphere(Material* material, unsigned int meridians = 36, unsigned int parallels = 36);
    static Mesh* generate_quadsphere(Material* material, unsigned int xseams = 8, unsigned int yseams = 8, unsigned int zseams = 8);
};