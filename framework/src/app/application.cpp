#include "../../include/river/app/application.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ri::Application::Application(unsigned width, unsigned height, const char* title)
    : m_width(width), m_height(height), m_vsync(false), m_title(title), m_window(nullptr)
{

}

auto ri::Application::run() -> int
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    auto p_window{(GLFWwindow*)m_window};
    if(!p_window)
    { 
        std::cout << "[RIVER] - failed to create Window" << std::endl;
        return 1;
    }

    glfwMakeContextCurrent(p_window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[RIVER] - failed to initialize OpenGL" << std::endl;
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, m_width, m_height);
    glfwSwapInterval(0);

    auto last_frame_time{static_cast<float>(glfwGetTime())};

    this->init();

    while(!glfwWindowShouldClose(p_window))
    {
        // calculate delta time
        auto frame_time{static_cast<float>(glfwGetTime())};
        auto delta{frame_time - last_frame_time};
        last_frame_time = frame_time;

        this->update(delta);

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->render();

        glfwSwapBuffers(p_window);
        glfwPollEvents();
    }

    return 0;
}

auto ri::Application::getScreenWidth() const -> unsigned
{
    return m_width;
}

auto ri::Application::getScreenHeight() const -> unsigned
{
    return m_height;
}

auto ri::Application::getVerticalSync() const -> float
{
    return m_vsync;
}

auto ri::Application::setVerticalSync(bool vsync) -> void
{
    m_vsync = vsync;
    glfwSwapInterval(m_vsync? 1 : 0);
}