#include "Equil.h"
#include "utils/utils.h"



Equil::Equil(float a)
{
	vertices = {
		{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3(a, 0.0f, 0.0f), glm::vec2(a, 0.0f)},
		{glm::vec3(a / 2, a * sin(-30), 0.0f), glm::vec2(a/2, a * sin(-30))}
	};

	texCoord = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(a, 0.0f),
		glm::vec2(a / 2, a * sin(-30))
	};


	faces = {
		glm::uvec3(0, 1, 2)
	};

	lattice = Geometry(getVertices(), layout, getIndices());

}

void Equil::bind()
{
	lattice.bind();
}

void Equil::unbind()
{
	lattice.unbind();
}

std::vector<float> Equil::getVertices()
{
	std::vector<float> vert;
	for (Vertex v : vertices)
	{
		vert.push_back(v.pos.x);
		vert.push_back(v.pos.y);
		vert.push_back(v.pos.z);

		vert.push_back(v.tex.x);
		vert.push_back(v.tex.y);

	}

	return vert;
}

std::vector<unsigned int> Equil::getIndices()
{
	std::vector<unsigned int> ind;
	for (glm::ivec3 v : faces)
	{
		ind.push_back(v.x);
		ind.push_back(v.y);
		ind.push_back(v.z);
	}

	return ind;
}
