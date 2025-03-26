#include "GameState.hpp"


Entity::Entity() : isInit(false)
{
    
}

Entity::~Entity()
{
    if(isInit) this->batchRenderer->unstageRect(this->renderAddress);
}

void Entity::tick(float dT)
{
    updateDrawable();
}

void Entity::init(BatchRenderer* batchRenderer)
{
    this->batchRenderer = batchRenderer;
    this->renderAddress = this->batchRenderer->stageRect(&this->drawable);
    this->isInit = true;
}

void Entity::updateDrawable()
{
    this->drawable.position = this->position - this->size / 2.0f;
    this->drawable.size = this->size;
}

EntityEvent::EntityEvent()
{
}

bool EntityEvent::tick(float dT, Entity *entity)
{
    this->timePassed += dT;
    return true;
}

MoveToPosEvent::MoveToPosEvent()
{
}

bool MoveToPosEvent::tick(float dT, Entity *entity)
{
    this->EntityEvent::tick(dT, entity);
    if(this->moveType == MoveType::Instant)
    {
        entity->position = this->targetPos;
        return true;
    }
    if(this->moveType == MoveType::Constant)
    {
        sf::Vector2f dir = this->targetPos - entity->position;
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if(len < this->speed * dT)
        {
            entity->position = this->targetPos;
            return true;
        }
        dir /= len;
        entity->position += dir * this->speed * dT;
        return false;
    }
    if(this->moveType == MoveType::AccelerationToLock)
    {
        sf::Vector2f dir = this->targetPos - entity->position;
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if(len < this->speed * dT)
        {
            entity->position = this->targetPos;
            return true;
        }
        dir /= len;
        entity->velocity += dir * this->speed * dT;
        entity->position += entity->velocity * dT;
        return false;
    }
    if(this->moveType == MoveType::AccelerationNoLock)
    {
        sf::Vector2f dir = this->targetPos - entity->position;
        float len = sqrt(dir.x * dir.x + dir.y * dir.y);
        if(len < this->speed * dT)
        {
            entity->position = this->targetPos;
            return true;
        }
        dir /= len;
        entity->velocity += dir * this->speed * dT;
        entity->position += entity->velocity * dT;
        return false;
    }
    return false;
}

MoveToPosEaseEvent::MoveToPosEaseEvent() : easeMoveType(EaseMoveType::EaseOutSine), easeDuration(1)
{
}

float easeOutBack(float x)
{
    float c1 = 1.70158f;
    float c3 = c1 + 1.0f;
    return 1 + c3 * pow(x-1,3) + c1 * pow(x-1,2);
}

bool MoveToPosEaseEvent::tick(float dT, Entity *entity)
{
    this->EntityEvent::tick(dT, entity);
    float progress = this->timePassed / this->easeDuration;
    if(progress > 1) progress = 1;
    if(this->easeMoveType == EaseMoveType::EaseOutSine)
    {
        entity->position = this->startPos + (this->targetPos - this->startPos) * sin(progress * 3.14159f / 2);
    } else if(this->easeMoveType == EaseMoveType::EaseOutBack)
    {
        float c1 = 1.70158f;
        float c3 = c1+1;
        entity->position = this->startPos + (this->targetPos - this->startPos) * easeOutBack(progress);
    } else if(this->easeMoveType == EaseMoveType::EaseOutCirc)
    {
        entity->position = this->startPos + (this->targetPos - this->startPos) * sqrt(1 - progress * progress);
    }

    return this->timePassed >= this->easeDuration;
}


SmartEntity::SmartEntity() : Entity(), timePassed(0)
{
    
}

SmartEntity::~SmartEntity()
{
    this->Entity::~Entity();

}

void SmartEntity::constructEntity(SmartEntityStruct data)
{
    this->size = data.size;
    this->drawable = data.drawable;
    this->position = data.position;
}

void SmartEntity::init(BatchRenderer* br)
{
    this->Entity::init(br);
}

void SmartEntity::tick(float dT)
{
    this->Entity::tick(dT);
}

void SmartEntity::tickFight(float dT)
{
}

// GameState

GameState::GameState() : FrameState(), batchRenderer(), timePassed(0)
{
}

GameState::~GameState()
{
}

void GameState::tick(float dT)
{
    for(auto& e : this->entities)
    {
        e->tick(dT);
    }
    this->timePassed += dT;
}

void GameState::render(sf::RenderTarget *window)
{
    batchRenderer.renderRects(window);
}

void GameState::handleInput()
{
}

void GameState::addEntity(std::unique_ptr<Entity> entity)
{
    this->entities.push_back(std::move(entity));
    this->entities.back()->init(&this->batchRenderer);
}
