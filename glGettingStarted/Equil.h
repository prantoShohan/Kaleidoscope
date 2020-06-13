#pragma once
#include "Geometry.h"
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec2 tex;
};

class Equil
{
public:
    std::vector<Vertex> vertices;
    std::vector<glm::uvec3> faces;
    std::vector<int> layout = { 3, 2 };
    std::vector<glm::vec2> texCoord;

    Geometry lattice;


    Equil(float a);

    void bind();
    void unbind();

    std::vector<float> getVertices();
    std::vector<unsigned int> getIndices();

};

