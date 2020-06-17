#pragma once

#include "utils/utils.h"
#include "Texture.h"
#include <unordered_map>

struct ShaderSource {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader
{
private:

	std::string m_filepath;
	std::unordered_map<std::string, int> m_uniforms;
	bool bound;

public:
	unsigned int m_rendererID;
	Shader(const std::string filepath);
	Shader();
	~Shader();

	void bind();
	void unbind();

	void setTexture(Texture tex);

	void setUniformInt(std::string name, int data);
	void setuniformFloat(std::string name, float data);
	void setUniformMat4(std::string name, glm::mat4 data);
	void setUniformVec2(std::string name, glm::vec2 data);

	int getUniformLoaction(std::string name);


private:
	unsigned int createShader(const std::string& vertesShader, const std::string& fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string& source);
	ShaderSource parseShader(const std::string& filepath);

};

