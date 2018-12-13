#include "GL/glew.h"
#include "stb_image.h"
#include "Texture.h"
#include <iostream>

Texture::Texture(unsigned int shaderProgram, const char* textureFileName)
	: m_shaderProgram(shaderProgram)
	, m_textureFileName(textureFileName)
{

}

bool Texture::init()
{
	glGenTextures(1, &m_texture);

	// load texture file
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(m_textureFileName, &width, &height, &channels, 0);	
	if (data)
	{
		GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cerr << "[ERROR]: Failed to load texture file: " << m_textureFileName << std::endl;
		stbi_image_free(data);
		return false;
	}

	glUseProgram(m_shaderProgram);
	glUniform1i( glGetUniformLocation(m_shaderProgram, "tex"), 0);

	return true;
}

bool Texture::render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	return true;
}

void Texture::cleanup()
{
	glDeleteTextures(1, &m_texture);
}