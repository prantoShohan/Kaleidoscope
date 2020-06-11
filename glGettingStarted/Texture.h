#pragma once

#include "utils/utils.h"

class Texture
{
private:

public:

	static int count;

	unsigned int m_rendererID;
	std::string m_name;
	int m_textureUnit;

	//this name should match the sampler2d uniform in shader
	Texture(std::string filepath, std::string name);
	
};
