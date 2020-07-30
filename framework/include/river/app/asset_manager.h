#ifndef RIVER_ASSET_MANAGER_H
#define RIVER_ASSET_MANAGER_H

#include "../render/shader.h"
#include "../core/container.h"

namespace ri
{
    auto foo() -> void;
    struct AssetManager
    {
        static auto shaderAdd(const char* name, Shader&& shader) -> bool;
        static auto shader(const char* name) -> const Shader&;
    private:
        static Dictionary<const char*, Shader> s_shaders;
    };
}

#endif