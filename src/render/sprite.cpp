#include "sprite.h"
#include "shader.h"
#include "vertex_array.h"
#include "texture2d.h"
#include "interface_drawable.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

river::Sprite::Sprite(Texture2D& texture, Shader& shader)
{
	m_texture = &texture;
	m_vertexArray = std::make_unique<VertexArray>();
	m_vertexArray->generateQuadVao();

	m_shader = &shader;
	m_shader->setUniformInt("u_texture", m_texture->getId());

	m_position = glm::vec2{ 0.f };
	m_size = glm::vec2{ m_texture->getWidth(), m_texture->getHeight() };
	m_rotation = 0.f;
}

river::Sprite::~Sprite()
{
}

void river::Sprite::draw(const river::Application& app)
{
	m_shader->use();
	glm::mat4 model = glm::mat4{ 1.f };

	model = glm::translate(model, glm::vec3{ m_position, 0.f });
	
	model = glm::translate(model, glm::vec3{ 0.5f * m_size.x, 0.5f * m_size.y, 0.f });
	model = glm::rotate(model, glm::radians(m_rotation), glm::vec3{ 0.f,0.f,1.f });
	model = glm::translate(model, glm::vec3{ -0.5f * m_size.x, -0.5f * m_size.y, 0.f });
	
	model = glm::scale(model, glm::vec3{ m_size, 1.0f });
	m_shader->setUniformMat4("u_projection", app.getProjection());
	m_shader->setUniformMat4("u_model", model);
	m_shader->setUniformVec3("u_color", m_color);
	
	m_texture->bind();
	m_vertexArray->bind();
	m_vertexArray->draw();
}

void river::Sprite::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void river::Sprite::setPosition(const glm::vec2& pos)
{
	m_position = pos;
}

void river::Sprite::setSize(float w, float h)
{
	m_size.x = w;
	m_size.y = h;
}

void river::Sprite::setSize(const glm::vec2& size)
{
	m_size = size;
}

void river::Sprite::setRotation(float angle)
{
	while (angle > 360.f)
		angle -= 360.f;
	while (angle < 0.f)
		angle += 360.f;
	
	m_rotation = angle;
}

void river::Sprite::setColor(float r, float g, float b)
{
	m_color.x = r;
	m_color.y = g;
	m_color.z = b;
}

void river::Sprite::setColor(const glm::vec3& color)
{
	m_color = color;
}

const glm::vec2& river::Sprite::getPosition() const
{
	return m_position;
}

const glm::vec2& river::Sprite::getSize() const
{
	return m_size;
}

float river::Sprite::getRotation() const
{
	return m_rotation;
}

const glm::vec3& river::Sprite::getColor() const
{
	return m_color;
}

void river::Sprite::setTexture(Texture2D& texture)
{
	m_texture = &texture;
	m_shader->use();
	m_shader->setUniformInt("u_texture", m_texture->getId());
}

const river::Texture2D& river::Sprite::getTexture() const
{
	return *m_texture;
}

void river::Sprite::setShader(Shader& shader)
{
	m_shader = &shader;
}

const river::Shader& river::Sprite::getShader() const
{
	return *m_shader;
}
