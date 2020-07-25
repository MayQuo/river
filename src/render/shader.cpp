#include "shader.h"

#include "../core.h"

#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

bool river::Shader::compile(const char* vertexCode, const char* fragmentCode)
{
	const auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, &vertexCode, nullptr);
	glCompileShader(vertex_shader);

	if (!checkCompile(vertex_shader))
	{
		throw std::runtime_error("vertex shader compilation failed!");
		return false;
	}

	glShaderSource(fragment_shader, 1, &fragmentCode, nullptr);
	glCompileShader(fragment_shader);

	if (!checkCompile(fragment_shader))
	{
		std::cout << "fragment shader compilation failed" << std::endl;
		return false;
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertex_shader);
	glAttachShader(m_id, fragment_shader);
	glLinkProgram(m_id);

	int success; char infoLog[512];
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
		std::cout << infoLog << std::endl;
		std::cout << "shader linking failed" << std::endl;
		return false;
	}

	if constexpr (is_debug)
	{
		std::cout << "shader with id: '" << m_id << "' compilation succeeded" << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	if constexpr (is_debug)
	{
		std::cout << "shader with id: '" << m_id << "' program linking succeeded" << std::endl;
	}
	
	return true;
	
}

auto river::Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath) -> river::Shader
{
	auto s = Shader{};
	
	std::fstream vertex_file, fragment_file;
	std::stringstream vertex_stream, fragment_stream;

	vertex_file.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	fragment_file.exceptions(std::ios_base::failbit | std::ios_base::badbit);

	std::string vertex_code, fragment_code;
	
	try
	{
		vertex_file.open(vertexPath);
		fragment_file.open(fragmentPath);

		vertex_stream << vertex_file.rdbuf();
		fragment_stream << fragment_file.rdbuf();

		vertex_code = vertex_stream.str();
		fragment_code = fragment_stream.str();
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	const auto* c_vertex_code = vertex_code.c_str();
	const auto* c_fragment_code = fragment_code.c_str();

	if (!s.compile(c_vertex_code, c_fragment_code))
		throw std::runtime_error("shader compilation failed!");
	
	return s;
}

auto river::Shader::use() const -> void
{
	glUseProgram(m_id);
}

auto river::Shader::getId() const -> unsigned
{
	return m_id;
}

auto river::Shader::setUniformInt(const std::string& name, int value) const -> void
{
	glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

auto river::Shader::setUniformVec2(const std::string& name, float x, float y) const -> void
{
	glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

auto river::Shader::setUniformVec2(const std::string& name, const glm::vec2& value) const -> void
{
	glUniform2f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y);
}

auto river::Shader::setUniformVec3(const std::string& name, float x, float y, float z) const -> void
{
	glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

auto river::Shader::setUniformVec3(const std::string& name, const glm::vec3& value) const -> void
{
	glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z);
}

auto river::Shader::setUniformVec4(const std::string& name, float x, float y, float z, float w) const -> void
{
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

auto river::Shader::setUniformVec4(const std::string& name, const glm::vec4& value) const -> void
{
	glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y, value.z, value.w);
}

auto river::Shader::setUniformMat4(const std::string& name, const glm::mat4& value) const -> void
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

auto river::Shader::checkCompile(unsigned shaderModule) -> bool
{
	int success; char infoLog[512];

	glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(shaderModule, 512, nullptr, infoLog);
		std::cout << infoLog << std::endl;
	}
	
	return success;
}
