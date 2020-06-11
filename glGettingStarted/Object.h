#pragma once

#include "utils/utils.h"

#include<vector>
#include <numeric>

class Object
{
public:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ebo;

	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<int> m_layout;

	bool m_useIndex;
	bool m_bound;

	glm::mat4 model;

	Object(std::vector<float> vertices, std::vector<int> layout, std::vector<unsigned int> indices)
		:m_vertices(vertices), m_indices(indices), m_layout(layout),
		 m_useIndex(true), model(glm::mat4(1.0f)),m_bound(false)
	{

		glCall(glGenVertexArrays(1, &m_vao));
		glCall(glBindVertexArray(m_vao));
		LOG << "Created vao: " << m_vao << END;

		glCall(glGenBuffers(1, &m_vbo));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		glCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));
		LOG << "Created vbo: " << m_vbo << END;

		glCall(glGenBuffers(1, &m_ebo));
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
		glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW));
		LOG << "Created ebo: " << m_ebo << END;

		int stride = std::accumulate(layout.begin(), layout.end(), 0) * sizeof(float);
		int offset = 0;
		for (int i = 0; i < layout.size(); i++)
		{
			glCall(glEnableVertexAttribArray(i));
			glCall(glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, stride, (void*)offset));
			offset += layout[i] * sizeof(float);
			LOG << "Created layout size: " << layout[i]<<" at: "<<i<< END;
		}

		//Sequence is important//
		glCall(glBindVertexArray(0));
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		LOG << "Created object." << END;

	}

	Object(std::vector<float> vertices, std::vector<int> layout)
		:m_vertices(vertices), m_indices({ 0 }), m_layout(layout),
		 m_useIndex(false), model(glm::mat4(1.0f)), m_bound(false), m_ebo(0)
	{

		glCall(glGenVertexArrays(1, &m_vao));
		glCall(glBindVertexArray(m_vao));
		LOG << "Created vao: " << m_vao << END;

		glCall(glGenBuffers(1, &m_vbo));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		glCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));
		LOG << "Created vbo: " << m_vbo << END;

		int stride = std::accumulate(layout.begin(), layout.end(), 0) * sizeof(float);
		int offset = 0;
		for (int i = 0; i < layout.size(); i++)
		{
			glCall(glEnableVertexAttribArray(i));
			glCall(glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, stride, (void*)offset));
			offset += layout[i] * sizeof(float);
			LOG << "Created layout size: " << layout[i] << " at: " << i << END;
		}

		//Sequence is important//
		glCall(glBindVertexArray(0));
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		LOG << "Created object." << END;

	}

	void bind()
	{
		if (!m_bound)
		{
			glCall(glBindVertexArray(m_vao));
		}
	}

	void unbind()
	{
		if (m_bound)
		{
			glCall(glBindVertexArray(0));
		}
	}

	glm::mat4 move(float x, float y, float z)
	{
		model = glm::translate(model, glm::vec3(x, y, z));
		return model;
	}

	glm::mat4 rotate(float x, float y, float z, float degree)
	{
		model = glm::rotate(model, glm::radians(degree), glm::vec3(x, y, z));
		return model;
	}

	glm::mat4 transform(glm::mat4 transform)
	{
		model *= transform;
		return model;
	}

	glm::mat4 getModel()
	{
		return model;
	}

};

