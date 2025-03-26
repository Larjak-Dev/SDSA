#pragma once
#include "GameState.hpp"

enum class ScreenEnterType {
    None,
    TopIn,   
    FadeIn
};

struct ShooterEntityStruct {
    SmartEntityStruct smartEntityStruct;
    ScreenEnterType enterType;
    float enterDuration;
};

class ShooterEntity : public SmartEntity {
    public:
        ScreenEnterType enterType;
        float enterDuration;
        std::unique_ptr<EntityEvent> enterEvent;

        bool isFighting;

        ShooterEntity();
        ~ShooterEntity();
        void constructEntity(ShooterEntityStruct data);
        void init(BatchRenderer* batchRenderer);

        void tick(float dT);
};

class ShooterState : public GameState {
public:

    ShooterState();
    ~ShooterState();
    void init();

    void render(sf::RenderTarget *window);
    void handleInput();
    void tick(float dT);
};