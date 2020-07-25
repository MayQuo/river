#include "texture2d.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

river::Texture2D::~Texture2D()
{
	if (m_id > 0)
		glDeleteTextures(1, &m_id);
}

auto river::Texture2D::loadFromFile(std::string file, bool alpha = true) -> river::Texture2D
{
	int width, height, nr_channels;
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &nr_channels, 0);

	auto texture = Texture2D{};
	texture.generate(data, width, height, alpha);

	stbi_image_free(data);
	
	return texture;
}

auto river::Texture2D::generate(unsigned char* data, unsigned width, unsigned height, bool alpha) -> void
{
	unsigned rgb = alpha ? GL_RGBA : GL_RGB;
	
	glGenTextures(1, &m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, rgb, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	m_width = width;
	m_height = height;
}

auto river::Texture2D::bind() const -> void
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

auto river::Texture2D::getId() const -> unsigned
{
	return m_id;
}

auto river::Texture2D::getWidth() const -> unsigned
{
	return m_width;
}

auto river::Texture2D::getHeight() const -> unsigned
{
	return m_height;
}
