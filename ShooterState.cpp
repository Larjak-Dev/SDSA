#include "ShooterState.hpp"
#include <iostream>

CustomShotEvent::CustomShotEvent()
{
}

bool CustomShotEvent::tick(float dT, SmartEntity *entity)
{
    this->EntityEvent::tick(dT, entity);
    if(this->customFunction != nullptr) {
        return this->customFunction(dT, (ShotEntity*)entity, this->mainPlayer);
    }
    std::cout << "No custom function set!" << std::endl;
    return true;
}

ShotEntity::ShotEntity() : SmartEntity()
{
}

ShotEntity::~ShotEntity()
{
}

void ShotEntity::init(BatchRenderer *batchRenderer)
{
    this->SmartEntity::init(batchRenderer);
}

void ShotEntity::constructEntity(ShotEntityStruct data)
{
    this->SmartEntity::constructEntity(data.smartEntityStruct);
    this->speed = data.speed;
    this->damage = data.damage;
}

void ShotEntity::tick(float dT)
{
    this->SmartEntity::tick(dT);
}


///Shot Event
ShotSpreadEvent::ShotSpreadEvent()
{

}

bool ShotSpreadEvent::tick(float dT, SmartEntity *entity)
{
    ShooterEntity* shooterEntity = (ShooterEntity*)entity;
    shooterEntity
    return true;
}

ShooterEntity::ShooterEntity() : SmartEntity(), enterType(ScreenEnterType::None), enterDuration(0), isFighting(false)
{
}

ShooterEntity::~ShooterEntity()
{
}

void ShooterEntity::constructEntity(ShooterEntityStruct data)
{
    this->SmartEntity::constructEntity(data.smartEntityStruct);
    this->enterType = data.enterType;
    this->enterDuration = data.enterDuration;
}

void ShooterEntity::tick(float dT)
{
    if(this->timePassed > this->enterDuration) {
        this->isFighting = true;
    } else if (enterEvent != nullptr) {
        this->enterEvent->tick(dT, this);
    }
    SmartEntity::tick(dT);
}

void ShooterEntity::init(BatchRenderer *batchRenderer)
{
    this->Entity::init(batchRenderer);
    if(this->enterType == ScreenEnterType::None)
    {
        auto event = std::make_unique<MoveToPosEvent>();
        event->durationTime = 0;
        event->targetPos = this->position;
        event->moveType = MoveType::Instant;

        this->enterEvent = std::move(event);
    } else if (this->enterType == ScreenEnterType::TopIn) {
        auto event = std::make_unique<MoveToPosEaseEvent>();
        event->durationTime = this->enterDuration;
        event->easeDuration = this->enterDuration;
        event->easeMoveType = EaseType::EaseOutBack;
        event->willStopOnDone = true;
        event->startPos = sf::Vector2f(this->position.x, -this->size.y);
        event->targetPos = this->position;

        this->enterEvent = std::move(event);
    }
}

ShooterState::ShooterState() : GameState()
{
}

ShooterState::~ShooterState()
{
}

void ShooterState::render(sf::RenderTarget *window)
{
    this->GameState::render(window);
}

void ShooterState::handleInput()
{
    this->GameState::handleInput();
}

void ShooterState::tick(float dT)
{
    this->GameState::tick(dT);
}

