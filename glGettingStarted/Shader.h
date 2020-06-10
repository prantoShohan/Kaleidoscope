#pragma once

#include "utils/utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <unordered_map>

struct ShaderSource {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
public:
	unsigned int m_shaderID;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_uniforms;
	bool m_bound;

	Shader(std::string filepath);
	~Shader();

	void bind();
	void unbind();

	void setUniformInt(std::string name, int data);
	void setuniformFloat(std::string name, float data);
	void setUniformMat4(std::string name, glm::mat4 data);

	int getUniformLoaction(std::string name);

	unsigned int createShader(const std::string& vertesShader, const std::string& fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string& source);
	ShaderSource parseShader(const std::string& filepath);

};

