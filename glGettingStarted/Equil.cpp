	#include "Equil.h"
	#include "utils/utils.h"



	Equil::Equil(float a)
	{
	
	float b = 0.5f;

	texCoord = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(b, 0.0f),
		glm::vec2(b / 2, b * sin(-30))
	};

	vertices = {
		{glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
		{glm::vec3(a, 0.0f, 0.0f), 1.0f},
		{glm::vec3(a / 2, a * sin(-30), 0.0f),2.0f},
		{glm::vec3(a / 2 + a, a * sin(-30), 0.0f), 0.0f},
		{glm::vec3(2*a, 0.0f, 0.0f), 2.0f}
	};




	faces = {
		glm::uvec3(0, 1, 2),
		glm::uvec3(1, 3, 2),
		glm::uvec3(4, 3, 1)
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

		vert.push_back(v.t);


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
