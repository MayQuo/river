#include "application.h"

#include <iostream>
#include <ostream>
#include <utility>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../render/shader.h"
#include "../render/vertex_array.h"
#include "../render/tile_map_renderer.h"
#include "../render/texture2d.h"
// #include "../render/font.h"
#include "../render/sprite.h"

river::Application::Application(unsigned width, unsigned height, std::string title)
	: m_width(width), m_height(height), m_title(std::move(title)), m_window(nullptr)
{
}

int river::Application::run()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	if(!m_window)
	{
		std::cout << "failed to create GLFW-Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_window);

	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glViewport(0, 0, m_width, m_height);

	init();
	
	auto last_frame_time = static_cast<float>(glfwGetTime());
	
	while (!glfwWindowShouldClose(m_window))
	{
		const auto time = static_cast<float>(glfwGetTime());
		const auto delta = time - last_frame_time;
		last_frame_time = time;

		update(delta);

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_projection = glm::mat4{ 1.f };
		m_projection = glm::ortho(0.f, static_cast<float>(m_width), static_cast<float>(m_height), 0.f, -1.f, 1.f);
		
		render();

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		renderUI();
		
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		

		glfwSwapBuffers(m_window);
		glfwPollEvents();	
	}
	
	glfwTerminate();
	return 0;
}

unsigned river::Application::getWidth() const
{
	return m_width;
}

unsigned river::Application::getHeight() const
{
	return m_height;
}

std::string river::Application::getTitle() const
{
	return m_title;
}

void river::Application::draw(IDrawable* drawable)
{
	if (drawable)
		drawable->draw(*this);
	else
		std::cout << "[ERROR] parameter is null: Application::draw(IDrawable* drawable)" << std::endl;
}

const glm::mat4& river::Application::getProjection() const
{
	return m_projection;
}

bool river::Application::isKeyPressed(int key) const
{
	return (glfwGetKey(m_window, key) == GLFW_PRESS);
}

void river::Application::init()
{
}

void river::Application::update(float delta)
{
}

void river::Application::render()
{
}

void river::Application::renderUI()
{
	
}
