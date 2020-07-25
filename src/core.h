#ifndef RIVER_CORE_H
#define RIVER_CORE_H

#include <glm/glm.hpp>

namespace river
{
#ifdef _DEBUG
	constexpr bool is_debug = true;
#else
	constexpr bool is_debug = false;
#endif
	
	typedef struct Vertex
	{
		glm::vec3 pos;
		glm::vec2 texCoord;
	} vertex;

	// Application
	struct Application;
	struct AssetManager;
	
	// Render
	struct Shader;
	struct VertexArray;
	struct TileMapRenderer;
// 	struct Font;
// 	struct Text2D;
	struct Sprite;
	struct IDrawable;
}

#endif
