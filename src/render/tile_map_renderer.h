#ifndef RIVER_TILE_MAP_RENDERER_H
#define RIVER_TILE_MAP_RENDERER_H

#include "../core.h"
#include "vertex_array.h"
#include "texture2d.h"
#include <memory>
#include <vector>

namespace river
{
	/**
	 * \brief represents an object which is able to render a tile map
	 * TODO: dynamic maps
	 */
	struct TileMapRenderer final
	{
		explicit TileMapRenderer() = default;
		virtual ~TileMapRenderer() = default;

		/**
		 * \brief generate a TileMap
		 * \param width cell width
		 * \param height cell height
		 * \param tileSizeX cell x size
		 * \param tileSizeY cell y size
		 * \param textureAtlas texture reference
		 * \param tiles level
		 */
		void generate(unsigned width, unsigned height, unsigned tileSizeX, unsigned tileSizeY, const Texture2D& textureAtlas, const int* tiles);

		void draw() const;
	private:
		std::unique_ptr<VertexArray> m_vao = nullptr;
		unsigned m_width = 0;
		unsigned m_height = 0;
		unsigned m_tileSizeX = 0;
		unsigned m_tileSizeY = 0;

		std::vector<Vertex> m_vertices;
		std::vector<unsigned> m_indices;

		Texture2D const * m_textureAtlas = nullptr;
	};
}

#endif