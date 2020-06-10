#include "Shader.h"

#include <fstream>
#include <sstream>

Shader::Shader(std::string filepath):
	m_filepath(filepath), m_bound(false)
{
	ShaderSource source = parseShader(filepath);
	m_shaderID = createShader(source.vertexShader, source.fragmentShader);

	LOG << "createdShader, ID:" << m_shaderID << END;
}

Shader::~Shader()
{
	glCall(glDeleteShader(m_shaderID));
	LOG << "Deleted Shader :" << m_shaderID << END;
}

void Shader::bind()
{
	if (!m_bound)
	{
		glCall(glUseProgram(m_shaderID));
		m_bound = true;

		LOG << "Bound Shader :" << m_shaderID << END;
	}
}

void Shader::unbind()
{
	if (m_bound)
	{
		glCall(glUseProgram(0));
		m_bound = false;
		LOG << "Unbound Shader :" << m_shaderID << END;
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
