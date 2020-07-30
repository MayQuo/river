#ifndef RIVER_SHADER_H
#define RIVER_SHADER_H

#include "../core/rmath.h"

namespace ri
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
		static auto loadFromFile(const char* vertexPath, const char* fragmentPath) -> Shader;

        /**
		 * \brief bind shader (do this before using draw calls)
		 */
        auto use() const -> void;

        /**
		 * \brief the OpenGL shader id
		 * \return shader id
		 */
        auto getId() const -> unsigned;

        auto setInt(const char* name, int value) const -> void;
        auto setVec2(const char* name, float x, float y) const -> void;
        auto setVec2(const char* name, const Vec2& value) const -> void;
        auto setVec3(const char* name, float x, float y, float z) const -> void;
        auto setVec3(const char* name, const Vec3& value) const -> void;
        auto setVec4(const char* name, float x, float y, float z, float w) const -> void;
        auto setVec4(const char* name, const Vec4& value) const -> void;
        auto setMat4(const char* name, const Mat4& value) const -> void;

    private:
        static auto checkCompile(unsigned module) -> bool;
        unsigned m_id{0};
    };
}

#endif