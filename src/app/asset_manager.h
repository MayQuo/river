#ifndef RIVER_ASSET_MANAGER_H
#define RIVER_ASSET_MANAGER_H

#include "../core.h"
#include <map>
#include <string>
// #include "../render/font.h"
#include "../render/shader.h"
#include "../render/texture2d.h"

namespace river
{
	
	/**
	 * \brief Represents the Content Loader for your Game. Use its static methodes to load all necessary assets and shaders!
	 */
	struct AssetManager
	{
// 		static void addFont(std::string name, Font&& font);
		static void addTexture(std::string name, Texture2D&& texture);
		static void addShader(std::string name, Shader&& shader);

// 		static Font& font(std::string name);
		static Shader& shader(std::string name);
		static Texture2D& texture(std::string name);

	private:
// 		static std::map<std::string, Font> s_fonts;
		static std::map<std::string, Shader> s_shaders;
 		static std::map<std::string, Texture2D> s_textures;
		
	};
}

#endif
