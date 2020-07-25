#ifndef RIVER_APPLICATION_H
#define RIVER_APPLICATION_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../core.h"
#include "../render/interface_drawable.h"

namespace river
{
	/**
	 * \brief represents a window app
	 */
	struct Application
	{
		explicit Application(unsigned int width, unsigned int height, std::string title);
		virtual ~Application() = default;
		
		/**
		 * \brief runs the main loop of the app
		 */
		int run();

		auto getWidth() const -> unsigned int;
		auto getHeight() const -> unsigned int;
		auto getTitle() const -> std::string;

		void draw(IDrawable* drawable);

		const glm::mat4& getProjection() const;

		bool isKeyPressed(int key) const;
	protected:
		virtual void init();
		virtual void update(float delta);
		virtual void render();
		virtual void renderUI();
	private:
		GLFWwindow* m_window;
		unsigned int m_width;
		unsigned int m_height;
		std::string m_title;

		glm::mat4 m_projection;
	};
}

#endif

