#include <river/river.h>
#include <iostream>

struct Game : public ri::Application
{
    explicit Game() : ri::Application::Application(1280, 720, "my river game") 
    {

    }

    virtual ~Game() = default;

    virtual auto init() -> void override 
    {
        ri::foo();
        this->setVerticalSync(true);
    }

    virtual auto update(float delta) -> void override 
    {
        //system("clear");
        //std::cout << "FPS: " << static_cast<int>(1.f/delta) << std::endl; 
    }

    virtual auto render() -> void override 
    {

    }
};

int main()
{
    Game app{};
    
    return app.run();
}