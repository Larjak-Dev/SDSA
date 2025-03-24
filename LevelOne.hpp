#pragma once
#include "GameState.hpp"

class LevelOne : public GameState {
public:
    LevelOne();
    ~LevelOne();

    void tick(float dT);
    void render(sf::RenderTarget* window);
    void handleInput();

    void init();
};