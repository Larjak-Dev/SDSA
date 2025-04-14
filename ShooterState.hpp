#pragma once
#include "GameState.hpp"

class ShotEntity;

class CustomShotEvent : public EntityEvent {
    public:
        std::function<bool(float, ShotEntity*, SmartEntity*)> customFunction;
        SmartEntity* mainPlayer;
    
        CustomShotEvent();
    
        bool tick(float dT, SmartEntity* entity) override;
};

struct ShotEntityStruct {
    SmartEntityStruct smartEntityStruct;
    float speed = 1;
    float damage = 1;
    CustomShotEvent customShotEvent;

};

class ShotEntity : public SmartEntity {
public:
    sf::Vector2f targetPos;
    float speed = 1;
    float damage = 1;

    float invisibleTime = 0;

    ShotEntity();
    ~ShotEntity();
    void constructEntity(ShotEntityStruct data);
    void init(BatchRenderer* batchRenderer);

    void tick(float dT);
};



class ShotSpreadEvent : public EntityEvent {
public:
    ShotEntityStruct shotType;
    GameState* gameState;

    float targetAngle = 0;
    sf::Vector2f targetPos;
    float spreadAngle = 0;
    float amountBullets = 1;
    
    float invisibleTime = 0;


    ShotSpreadEvent();
    bool tick(float dT, SmartEntity* entity);
};


enum class ScreenEnterType {
    None,
    TopIn,   
    FadeIn
};

struct ShooterEntityStruct {
    SmartEntityStruct smartEntityStruct;
    ScreenEnterType enterType = ScreenEnterType::None;
    float enterDuration = 0;
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
    void render(sf::RenderTarget *window);
    void handleInput();
    void tick(float dT);
};