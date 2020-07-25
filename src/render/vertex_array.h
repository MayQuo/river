#ifndef RIVER_VERTEX_ARRAY_H
#define RIVER_VERTEX_ARRAY_H

#include "../core.h"

namespace river
{
	/**
	 * \brief represents a vertex array object with vertex buffer, index buffer etc.
	 */
	struct VertexArray final
	{
		explicit VertexArray();
		virtual ~VertexArray();

		auto generateVao(void* vertices, unsigned verticesLength, void* indices, unsigned indicesLength) -> bool;
		auto generateQuadVao() -> bool;

		auto draw() const -> void;
		auto bind() const -> void;
	private:
		unsigned m_vao = 0;
		unsigned m_vbo = 0;
		unsigned m_ebo = 0;

		unsigned m_verticesCount = 0;
		unsigned m_indicesCount  = 0;

		void* p_indices = nullptr;
	};
	
}

#endif