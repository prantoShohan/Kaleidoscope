	#include "Equil.h"
	#include "utils/utils.h"



Equil::Equil(float a)
{
	
	for (int i = 0; i < 1; i++)
	{
		vertices.push_back({ glm::vec3(3 * a * i,    0.0f,           0.0f),       0.0f });
		vertices.push_back({ glm::vec3(3 * a * i + a,       0.0f,           0.0f),       1.0f });
		vertices.push_back({ glm::vec3((3 * i * a) + (a / 2),   a * sin(-30),   0.0f),       2.0f });


		vertices.push_back({ glm::vec3((3 * i * a) + (1.5f * a),   a * sin(-30),   0.0f),       0.0f });
		vertices.push_back({ glm::vec3((3 * i * a) + (2.0f * a),      0.0f,           0.0f),       2.0f });
		vertices.push_back({ glm::vec3((3 * i * a) + (2.5f * a),    a * sin(-30),   0.0f),       1.0f });


		faces.push_back(glm::uvec3(0, 1, 2));
		faces.push_back(glm::uvec3(1, 3, 2));
		faces.push_back(glm::uvec3(1, 4, 3));
		faces.push_back(glm::uvec3(3, 4, 5));
		
	}








	float b = 0.5f;

	texCoord = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(b, 0.0f),
		glm::vec2(b / 2, b * sin(-30))
	};

// 	vertices = {
// 		{glm::vec3(0.0f, 0.0f, 0.0f), 0.0f},
// 		{glm::vec3(a, 0.0f, 0.0f), 1.0f},
// 		{glm::vec3(a / 2, a * sin(-30), 0.0f),2.0f},
// 		{glm::vec3(a / 2 + a, a * sin(-30), 0.0f), 0.0f},
// 		{glm::vec3(2*a, 0.0f, 0.0f), 2.0f}
// 	};
// 
// 
// 
// 
// 	faces = {
// 		glm::uvec3(0, 1, 2),
// 		glm::uvec3(1, 3, 2),
// 		glm::uvec3(4, 3, 1)
// 	};

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
