#ifndef RIVER_SPRITE_H
#define RIVER_SPRITE_H

#include "../core.h"

#include <memory>

#include "../app/application.h"
#include "texture2d.h"
#include "interface_drawable.h"

namespace river
{
	// TODO: sprite
	struct Sprite : public IDrawable
	{
		explicit Sprite(Texture2D& texture, Shader& shader);
		virtual ~Sprite();
		void draw(const Application& app) override;

		void setPosition(float x, float y);
		void setPosition(const glm::vec2& pos);

		void setSize(float w, float h);
		void setSize(const glm::vec2& size);

		void setRotation(float angle);
		
		void setColor(float r, float g, float b);
		void setColor(const glm::vec3& color);
		
		const glm::vec2& getPosition() const;
		const glm::vec2& getSize() const;
		float getRotation() const;
		const glm::vec3& getColor() const;

		void setTexture(Texture2D& texture);
		const Texture2D& getTexture() const;

		void setShader(Shader& shader);
		const Shader& getShader() const;
	private:
		Shader* m_shader = nullptr;
		Texture2D* m_texture;
		std::unique_ptr<VertexArray> m_vertexArray;

		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
		glm::vec3 m_color;
	};
}

#endif
