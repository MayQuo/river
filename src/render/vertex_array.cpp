#include "vertex_array.h"

#include <cstddef>
#include <glad/glad.h>

river::VertexArray::VertexArray() = default;

river::VertexArray::~VertexArray() = default;

auto river::VertexArray::generateVao(void* vertices, unsigned verticesLength, void* indices,
                                       unsigned indicesLength) -> bool
{
	p_indices = indices;
	m_verticesCount = verticesLength;
	m_indicesCount = indicesLength;
	
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*verticesLength, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned)*indicesLength, indices, GL_STATIC_DRAW);

	// position x, y, z
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>((offsetof(Vertex, pos))));
	glEnableVertexAttribArray(0);

	// texture coordinates tx, ty
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>((offsetof(Vertex, texCoord))));
	glEnableVertexAttribArray(1);

	return true;
}

auto river::VertexArray::generateQuadVao() -> bool
{
	vertex vertices[] = {
		vertex{glm::vec3{0.f,0.f,0.f}, glm::vec2{0.f,0.f}},
		vertex{glm::vec3{1.f,0.f,0.f}, glm::vec2{1.f,0.f}},
		vertex{glm::vec3{1.f,1.f,0.f}, glm::vec2{1.f,1.f}},
		vertex{glm::vec3{0.f,1.f,0.f}, glm::vec2{0.f,1.f}}
	};
	
	unsigned indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	
	return generateVao(vertices, 20, indices, 6);
}

auto river::VertexArray::draw() const -> void
{
	bind();
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, nullptr);
}

auto river::VertexArray::bind() const -> void
{
	glBindVertexArray(m_vao);
}
