#include "ShooterState.hpp"

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

    if(this->isFighting)
    {
        this->tickFight(dT);
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
        event->easeMoveType = EaseMoveType::EaseOutBack;
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
