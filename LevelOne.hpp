#pragma once
#include "ShooterState.hpp"

class LevelOne : public ShooterState {
public:
    LevelOne();
    ~LevelOne();

    void tick(float dT);
    void render(sf::RenderTarget* window);
    void handleInput();

    void init();
};