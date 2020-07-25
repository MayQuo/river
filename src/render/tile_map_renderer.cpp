#include "tile_map_renderer.h"

#include <iostream>
#include <glad/glad.h>

void river::TileMapRenderer::generate(unsigned width, unsigned height, unsigned tileSizeX, unsigned tileSizeY, const Texture2D& textureAtlas, const int* tiles)
{
	m_width = width;
	m_height = height;
	m_tileSizeX = tileSizeY;
	m_tileSizeY = tileSizeY;
	
	m_vao = std::make_unique<VertexArray>();

	m_textureAtlas = &textureAtlas;
	
	// generate m_vertices & indices
	m_vertices = std::vector<Vertex>();
	m_indices = std::vector<unsigned>();

	for(unsigned j = 0; j < height;j++)
	{
		for (unsigned i = 0; i < width; i++)
		{
			Vertex v0{}, v1{}, v2{}, v3{};

			auto tile_number = tiles[i + j * width];

			if (tile_number == 8)
			{
				std::cout << std::endl;
			}
			
			auto tiles_x = textureAtlas.getWidth() / tileSizeX;
			auto tiles_y = textureAtlas.getHeight() / tileSizeY;

			auto tx = tile_number % tiles_x;
			auto ty = tile_number / tiles_x;
			
			v0.pos = glm::vec3{ i * tileSizeX,				j * tileSizeY,	  0.f };
			v1.pos = glm::vec3{ (i+1) * tileSizeX,			j * tileSizeY,	  0.f };
			v2.pos = glm::vec3{ (i+1) * tileSizeX ,			(j+1) * tileSizeY, 0.f };
			v3.pos = glm::vec3{ i * tileSizeX,				(j+1) * tileSizeY, 0.f };

			auto ftx = static_cast<float>(tx);
			auto fty = static_cast<float>(ty);
			auto ftiles_x = static_cast<float>(tiles_x);
			auto ftiles_y = static_cast<float>(tiles_y);
			
			v0.texCoord = glm::vec2{ftx/ftiles_x,				(fty+1.f)/ftiles_y};
			v1.texCoord = glm::vec2{(ftx+1.f)/ftiles_x,		(fty+1.f)/ftiles_y};
			v2.texCoord = glm::vec2{(ftx+1.f)/ftiles_x,		(fty)/ftiles_y};
			v3.texCoord = glm::vec2{ ftx/ftiles_x,			(fty)/ftiles_y };

			m_vertices.push_back(v0);
			m_vertices.push_back(v1);
			m_vertices.push_back(v2);
			m_vertices.push_back(v3);
		}
	}

	for(unsigned k = 0; k < height*width; k++)
	{
		m_indices.push_back(0 + (4 * k));
		m_indices.push_back(1 + (4 * k));
		m_indices.push_back(2 + (4 * k));
		m_indices.push_back(2 + (4 * k));
		m_indices.push_back(3 + (4 * k));
		m_indices.push_back(0 + (4 * k));
	}
	
	m_vao->generateVao(m_vertices.data(), static_cast<unsigned>(m_vertices.size()), 
		m_indices.data(), static_cast<unsigned>(m_indices.size()));
}

void river::TileMapRenderer::draw() const
{
	// TODO: set the corresponding projection matrix
	m_vao->draw();
}
