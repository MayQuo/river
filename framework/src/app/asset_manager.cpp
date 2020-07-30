#include "../../include/river/app/asset_manager.h"
#include "../../include/river/core/container.h"

#include "../../include/river/core/container.h"

 ri::Dictionary<const char*, ri::Shader> ri::AssetManager::s_shaders = ri::Dictionary<const char*, ri::Shader>();

auto ri::AssetManager::shaderAdd(const char* name, ri::Shader&& shader) -> bool
{
    return s_shaders.add(name, shader);
}

auto ri::AssetManager::shader(const char* name) -> const ri::Shader&
{
    return s_shaders[name];
}