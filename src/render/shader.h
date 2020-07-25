#ifndef RIVER_SHADER_H
#define RIVER_SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace river
{
	/**
	 * \brief represents a shader object in OpenGL
	 */
	struct Shader final
	{
		explicit Shader() = default;
        virtual ~Shader() = default;


		/**
		 * \brief compile and link shader to program
		 * \param vertexCode the vertex source code
		 * \param fragmentCode the fragment source code
		 * \return whether compilation succeeded
		 */
		auto compile(const char* vertexCode, const char* fragmentCode) -> bool;
		/**
		 * \brief load shader from file into shader object
		 * \param vertexPath path to vertex file
		 * \param fragmentPath path to fragment file
		 * \return compiled shader object
		 */
		static auto loadFromFile(const std::string& vertexPath, const std::string& fragmentPath) -> Shader;

		/**
		 * \brief bind shader (do this before using draw calls)
		 */
		auto use() const -> void;

		/**
		 * \brief the OpenGL shader id
		 * \return shader id
		 */
		auto getId() const -> unsigned int;

		auto setUniformInt(const std::string& name, int value) const -> void;
		
		auto setUniformVec2(const std::string& name, float x, float y) const -> void;
		auto setUniformVec2(const std::string& name, const glm::vec2& value) const -> void;
		
		auto setUniformVec3(const std::string& name, float x, float y, float z) const -> void;
		auto setUniformVec3(const std::string& name, const glm::vec3& value) const -> void;

		auto setUniformVec4(const std::string& name, float x, float y, float z, float w) const -> void;
		auto setUniformVec4(const std::string& name, const glm::vec4& value) const -> void;

		auto setUniformMat4(const std::string& name, const glm::mat4& value) const -> void;
		
	private:
		/**
		 * \brief intern function to proof if compilation worked ... used in Shader::compile()
		 * \param shaderModule the shader (vertex/fragment) to check if compilation succeeded
		 * \\return whether module compilation succeeded
		 */
		
		static auto checkCompile(unsigned shaderModule) -> bool;
		unsigned int m_id = 0;
	};
}

#endif
