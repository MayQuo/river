#include "app/application.h"
#include "app/asset_manager.h"
#include "render/shader.h"
#include "render/texture2d.h"
#include "render/tile_map_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <memory>

constexpr unsigned SCR_WIDTH = 1280;
constexpr unsigned SCR_HEIGHT = 720;

struct Game : public river::Application
{
    Game(std::string title) : river::Application(SCR_WIDTH, SCR_HEIGHT, title)
    {
        
    }
    
    virtual void init() override {
        river::AssetManager::addShader("tile", river::Shader::loadFromFile("shader/tile.vert", "shader/tile.frag"));
        
        river::AssetManager::addTexture("tileset", river::Texture2D::loadFromFile("assets/textures/tileset.png", true));
    
        m_shader = &river::AssetManager::shader("tile");
        
        int level[] = {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
                0, 0, 1, 2, 2, 1, 1, 1, 0, 0,
                0, 0, 1, 2, 2, 2, 2, 1, 0, 0,
                0, 0, 1, 2, 1, 1, 1, 1, 0, 0,
                0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };
        
        m_tilemap = std::make_shared<river::TileMapRenderer>();
        m_tilemap->generate(10,8,32,32, river::AssetManager::texture("tileset"), level);
    }
    
    virtual void update(float delta) override {
        
    }
    
    virtual void render() override {
        m_shader->use();
        m_shader->setUniformMat4("u_projection", glm::ortho(0.f, static_cast<float>(this->getWidth()), static_cast<float>(this->getHeight()), 0.f, -1.f, 1.f));
        m_tilemap->draw();
    }
    
    virtual void renderUI() override {
        
    }
    
private:
    std::shared_ptr<river::TileMapRenderer> m_tilemap;
    river::Shader* m_shader;
};

int main()
{
	Game app{"River"};
	return app.run();
}
