#include "Shader.h"

#include <fstream>
#include <sstream>


Shader::Shader(const std::string filepath)
	:m_filepath(filepath), bound(false)
{
	ShaderSource source = parseShader(filepath);
	//std::cout << source.fragmentShader << "\n" << source.vertexShader;
	m_rendererID = createShader(source.vertexShader, source.fragmentShader);

}

Shader::~Shader()
{
	//glCall(glDeleteProgram(m_rendererID));
}

void Shader::bind()
{
	if (!bound)
	{
		glCall(glUseProgram(m_rendererID));
		bound = true;
	}
}

void Shader::unbind()
{
	glCall(glUseProgram(0));
	bound = false;
}




void Shader::setTexture(Texture tex)
{
	setUniformInt(tex.m_name.c_str(), tex.m_textureUnit);
}

void Shader::setUniformInt(std::string name, int data)
{
	glCall(glUniform1i(getUniformLoaction(name), data));
}

void Shader::setuniformFloat(std::string name, float data)
{
	glCall(glUniform1f(getUniformLoaction(name), data));
}

void Shader::setUniformMat4(std::string name, glm::mat4 data)
{
	glCall(glUniformMatrix4fv(getUniformLoaction(name), 1, GL_FALSE, glm::value_ptr(data)));
}

void Shader::setUniformVec2(std::string name, glm::vec2 data)
{
	glCall(glUniform2fv(getUniformLoaction(name), 1, glm::value_ptr(data)));
}

int Shader::getUniformLoaction(std::string name)
{
	if (m_uniforms.find(name) != m_uniforms.end())
	{
		return m_uniforms[name];
	}
	else
	{
		glCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
		m_uniforms[name] = location;
		if (location == -1)
		{
			std::cout << "UNIFORM NOT FOUND\n";
		}
		return location;
	}
}

unsigned int Shader::createShader(const std::string& vertesShader, const std::string& fragmentShader)
{
	glCall(unsigned int program = glCreateProgram());
	glCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertesShader));
	glCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader));

	glCall(glAttachShader(program, vs));
	glCall(glAttachShader(program, fs));
	glCall(glLinkProgram(program));
	glCall(glValidateProgram(program));

	glCall(glDeleteShader(vs));
	glCall(glDeleteShader(fs));

	return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	//main code
	glCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	glCall(glShaderSource(id, 1, &src, NULL));
	glCall(glCompileShader(id));

	//error checking
	int result;
	glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		glCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << message << std::endl;
		return 0;
	}

	return id;
}

ShaderSource Shader::parseShader(const std::string& filepath)
{
	std::fstream stream(filepath);
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };

}
