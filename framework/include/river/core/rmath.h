#ifndef RIVER_MATH_H
#define RIVER_MATH_H

namespace ri
 {
    struct Vec2  
    { 
        float x, y;
    
        static auto normalize(const Vec2& v) -> Vec2&&;
        static auto length(const Vec2& v) -> float;
    };
    struct Vec3  
    { 
        float x, y, z; 

        static auto normalize(const Vec3& v) -> Vec3&&;
        static auto length(const Vec3& v) -> float;
    };
    struct Vec4
    {
        float x, y, z, w;
    };

    auto deg2rad(float deg) -> float;
    auto rad2deg(float rad) -> float;
    auto square(float value) -> float;
    auto abs(float value) -> float;
    auto floor(float value) -> int;
    auto ceil(float value) -> int;
    
    struct Mat4
    {       
        float x1, x2, x3, x4;
        float y1, y2, y3, y4;
        float z1, z2, z3, z4;
        float w1, w2, w3, w4;
        
        explicit Mat4(float value = 1.f);

        static auto transform(const Mat4& mat, const Vec3& position) -> Mat4&&;
        static auto scale(const Mat4& mat, const Vec3& scale) -> Mat4&&;
        static auto rotate(const Mat4& mat, float radians, const Vec3& rotation) -> Mat4&&;

        static auto ortho(unsigned screenWidth, unsigned screenHeight, float min, float max) -> Mat4&&;
        // TODO: perspective
        static auto data(const Mat4& mat) -> float*; 


    };
 }

#endif