#pragma once
#include "GameState.hpp"

enum class ScreenEnterType {
    None,
    TopIn,   
    FadeIn
};

struct ShooterEntityStruct : SmartEntityStruct {
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

        void tick(float dT);
        void init(BatchRenderer* batchRenderer);
};

class ShooterState : public GameState {
public:

    ShooterState();
    ~ShooterState();
    void constructEntity(ShooterEntityStruct data);

    void render(sf::RenderTarget *window);
    void handleInput();
    void init();
    void tick(float dT);
};