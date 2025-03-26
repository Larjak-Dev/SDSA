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

ShooterEntityStruct basicFairy;

void LevelOne::init()
{
    basicFairy.smartEntityStruct.position = sf::Vector2f(300,300);
    basicFairy.smartEntityStruct.size = sf::Vector2f(100,100);
    basicFairy.smartEntityStruct.drawable.color = sf::Color::Green;
    basicFairy.enterType = ScreenEnterType::TopIn;
    basicFairy.enterDuration = 2.0f;

    auto entityPtr = std::make_unique<ShooterEntity>();
    entityPtr->constructEntity(basicFairy);
    this->addEntity(std::move(entityPtr));
}

void LevelOne::tick(float dT)
{
    this->GameState::tick(dT);
}
