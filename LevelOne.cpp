#include "LevelOne.hpp"

LevelOne::LevelOne() : ShooterState()
{
    
}

LevelOne::~LevelOne()
{
}

void LevelOne::render(sf::RenderTarget *window)
{
    this->GameState::render(window);
}

void LevelOne::handleInput()
{
    this->GameState::handleInput();
}

ShooterEntity fairy;

void LevelOne::init()
{
    fairy.position = sf::Vector2f(300,300);
    fairy.size = sf::Vector2f(100,100);
    fairy.drawable.color = sf::Color::Green;
    fairy.enterType = ScreenEnterType::TopIn;

    auto entityPtr = std::make_unique<ShooterEntity>();
    (*entityPtr) = fairy;
    this->addEntity(std::move(entityPtr));
}

void LevelOne::tick(float dT)
{
    this->GameState::tick(dT);
}
