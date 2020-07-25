#ifndef RIVER_TEXTURE2D_H
#define RIVER_TEXTURE2D_H

#include <string>

#include "../core.h"

namespace river
{
	
	/**
	 * \brief Represents a 2D Texture. Every sprites refers to one or many textures to draw them with its position and scale value.
	 */
	struct Texture2D
	{
		explicit Texture2D() = default;
		virtual ~Texture2D();

		/**
		 * \brief load and generate texture from file
		 * \param file path + filename
		 * \param alpha whether alpha value should be used
		 * \return new texture
		 */
		static auto loadFromFile(std::string file, bool alpha) -> Texture2D;

		/**
		 * \brief generate texture id etc.
		 */
		auto generate(unsigned char* data, unsigned width, unsigned height, bool alpha) -> void;

		/**
		 * \brief bind texture
		 */
		void bind() const;

		auto getId() const -> unsigned;
		auto getWidth() const -> unsigned;
		auto getHeight() const -> unsigned;
	private:
		unsigned m_id = 0;
		unsigned m_width = 0;
		unsigned m_height = 0;
		
	};
}

#endif