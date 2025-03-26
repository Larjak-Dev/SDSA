#pragma once
#include "AppHandler.hpp"
#include <memory>
#include <queue>

class Entity {
    public:
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    bool isInit = false;

    Entity();
    ~Entity();

    virtual void tick(float dT);
    

    //Rendering
    BatchRenderer* batchRenderer;
    RectDrawable drawable;
    std::list<RectDrawable*>::iterator renderAddress;
    void updateDrawable();
    virtual void init(BatchRenderer* batchRenderer);
    
};

/// ENTITY EVENTS

class EntityEvent {
public:
    bool hasDuration = true;
    float durationTime = 1;
    float timePassed = 0;
    bool willStopOnDone = true;


    EntityEvent();
    virtual ~EntityEvent() = default;

    virtual bool tick(float dT, Entity* entity);


};

enum class MoveType {
    Instant, Constant, AccelerationToLock, AccelerationNoLock
};

class MoveToPosEvent : public EntityEvent {
public:
    sf::Vector2f targetPos;
    MoveType moveType;
    float speed = 1;

    MoveToPosEvent();

    bool tick(float dT, Entity* entity);
};

enum class EaseType {
    EaseOutSine, EaseOutBack, EaseOutCirc
};

class MoveToPosEaseEvent : public EntityEvent {
public:
    sf::Vector2f startPos;
    sf::Vector2f targetPos;
    EaseType easeMoveType;
    float easeDuration = 1;

    MoveToPosEaseEvent();

    bool tick(float dT, Entity* entity);
};

class HitBox {
    
};

struct SmartEntityStruct {
    sf::Vector2f size = sf::Vector2f(100,100);
    RectDrawable drawable;
    HitBox hitBox;
    sf::Vector2f position;

};

class SmartEntity : public Entity {
public:
    float timePassed = 0;
    std::list<std::unique_ptr<EntityEvent>> events; // List of active events
    std::queue<std::unique_ptr<EntityEvent>> eventQueue; // Queued event that is going to happen 

    SmartEntity();
    ~SmartEntity();
    void constructEntity(SmartEntityStruct data);

    void init(BatchRenderer* bt);
    void tick(float dT);
    void tickFight(float dT);

};

class GameState : public FrameState {
protected:
    BatchRenderer batchRenderer;
public:
    std::list<std::unique_ptr<Entity>> entities;
    float timePassed;

    GameState();
    ~GameState();

    void tick(float dT);
    void render(sf::RenderTarget* window);
    void handleInput();

    void addEntity(std::unique_ptr<Entity> entity);
};