#include "../../include/river/core/rmath.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utility>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto glmMatFrom(const ri::Mat4& mat) -> glm::mat4&&;
auto matFromGlm(const glm::mat4& gmat) -> ri::Mat4&&;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto ri::Vec3::normalize(const Vec3& v) -> ri::Vec3&&
{
    auto&& gvec = glm::normalize(glm::vec3{v.x, v.y, v.z});
    auto&& vec = ri::Vec3();
    vec.x = gvec.x;
    vec.y = gvec.y;
    vec.z = gvec.z;

    return std::move(vec);
}

auto ri::Vec3::length(const Vec3& v) -> float
{
    return glm::length(glm::vec3{v.x, v.y, v.z});
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto ri::Vec2::normalize(const Vec2& v) -> ri::Vec2&&
{
    auto&& gvec = glm::normalize(glm::vec2{v.x, v.y});
    auto&& vec = ri::Vec2();
    vec.x = gvec.x;
    vec.y = gvec.y;

    return std::move(vec);
}

auto ri::Vec2::length(const Vec2& v) -> float
{
    return glm::length(glm::vec2{v.x, v.y});
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto ri::deg2rad(float deg) -> float
{
    return glm::radians(deg);
}

auto ri::rad2deg(float rad) -> float
{
    return glm::degrees(rad);
}

auto ri::square(float value) -> float
{
    return value*value;
}

auto ri::abs(float value) -> float
{
    return value < 0 ? -value : value;
}

auto ri::floor(float value) -> int
{
    return static_cast<int>(floorf32(value));
}

auto ri::ceil(float value) -> int
{
    return static_cast<int>(ceilf32(value));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ri::Mat4::Mat4(float value)
{
    x1 = value; x2 = value; x3 = value; x4 = value;
    y1 = value; y2 = value; y3 = value; y4 = value;
    z1 = value; z2 = value; z3 = value; z4 = value;
    w1 = value; w2 = value; w3 = value; w4 = value;
}

auto ri::Mat4::transform(const Mat4& mat, const Vec3& position) -> ri::Mat4&&
{
    auto&& gmat = glm::translate(glmMatFrom(mat), glm::vec3(position.x, position.y, position.z));
    return matFromGlm(gmat);
}

auto ri::Mat4::scale(const Mat4& mat, const Vec3& scale) -> ri::Mat4&&
{
    auto&& gmat = glm::scale(glmMatFrom(mat), glm::vec3(scale.x, scale.y, scale.z));
    return matFromGlm(gmat);
}

auto ri::Mat4::rotate(const Mat4& mat, float radians, const Vec3& rotation) -> ri::Mat4&&
{
    auto&& gmat = glm::rotate(glmMatFrom(mat), radians, glm::vec3(rotation.x, rotation.y, rotation.z));
    return matFromGlm(gmat);
}

auto ortho(unsigned screenWidth, unsigned screenHeight, float min, float max) -> ri::Mat4&&
{
    auto&& gmat = glm::ortho(0.f, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0.f, min, max);
    return matFromGlm(gmat);
}

auto ri::Mat4::data(const Mat4& mat) -> float*
{
    return (float*)offsetof(Mat4, x1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto glmMatFrom(const ri::Mat4& mat) -> glm::mat4&&
{
    glm::mat4&& gmat = {
        mat.x1, mat.x2, mat.x3, mat.x4,
        mat.y1, mat.y2, mat.y3, mat.y4,
        mat.z1, mat.z2, mat.z3, mat.z4,
        mat.w1, mat.w2, mat.w3, mat.w4
    };

    return std::move(gmat);
}

auto matFromGlm(const glm::mat4& gmat) -> ri::Mat4&&
{
    auto&& mat = ri::Mat4{};

    mat.x1 = gmat[0][0]; mat.x2 = gmat[0][1]; mat.x3 = gmat[0][2]; mat.x4 = gmat[0][3];
    mat.y1 = gmat[1][0]; mat.y2 = gmat[1][1]; mat.y3 = gmat[1][2]; mat.x4 = gmat[1][3];
    mat.z1 = gmat[2][0]; mat.z2 = gmat[2][1]; mat.z3 = gmat[2][2]; mat.x4 = gmat[2][3];
    mat.w1 = gmat[3][0]; mat.w2 = gmat[3][1]; mat.w3 = gmat[3][2]; mat.x4 = gmat[3][3];

    return std::move(mat);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////