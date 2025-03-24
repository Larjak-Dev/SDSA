#pragma once
#include "GameState.hpp"

enum class ScreenEnterType {
    None,
    TopIn,   
    FadeIn
};

class ShooterState : public GameState {
public:
    ShooterState();
    ~ShooterState();

    void render(sf::RenderTarget *window);
    void handleInput();
    void init();
    void tick(float dT);
};