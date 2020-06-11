#pragma once

#include "utils/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "utils/stb_image.h"



class Texture
{
private:

public:
	static int count;

	unsigned int m_rendererID;
	std::string m_name;
	int m_textureUnit;

	//this name should match the sampler2d uniform in shader
	Texture(std::string filepath, std::string name)
		:m_name(name), m_textureUnit(count)
	{

		glCall(glGenTextures(1, &m_rendererID));
		glCall(glActiveTexture(GL_TEXTURE0+count));
		LOG << "Activated texture unit :" << count << END;
		glCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
		LOG << "Bound texture " << name <<" at"<<count<<" slot."<< END;

		//TODO: this part should be accessible
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		LOG << "Loading image" << END;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		}
		else
		{
			LOG << "ERROR loading image" << END;
		}
		stbi_image_free(data);


		count++;
	}
};

int Texture::count = 0;