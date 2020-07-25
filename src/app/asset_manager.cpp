#include "asset_manager.h"
#include <iostream>

// std::map<std::string, river::Font> river::AssetManager::s_fonts = std::map<std::string, river::Font>();
std::map<std::string, river::Shader> river::AssetManager::s_shaders = std::map<std::string, river::Shader>();
std::map<std::string, river::Texture2D> river::AssetManager::s_textures = std::map<std::string, river::Texture2D>();

// void river::AssetManager::addFont(std::string name, Font&& font)
// {
// 	s_fonts.insert(std::make_pair(name, std::move(font)));
// 	std::cout << "font: '" << name << "' added" << std::endl;
// }

void river::AssetManager::addTexture(std::string name, Texture2D&& texture)
{
	s_textures.insert(std::make_pair(name, std::move(texture)));
	std::cout << "texture: '" << name << "' added" << std::endl;
}

void river::AssetManager::addShader(std::string name, Shader&& shader)
{
	s_shaders.insert(std::make_pair(name, std::move(shader)));
	std::cout << "shader: '" << name << "' added" << std::endl;
}

// river::Font& river::AssetManager::font(std::string name)
// {
// 	return s_fonts[name];
// }

river::Shader& river::AssetManager::shader(std::string name)
{
	return s_shaders[name];
}

river::Texture2D& river::AssetManager::texture(std::string name)
{
	return s_textures[name];
}
