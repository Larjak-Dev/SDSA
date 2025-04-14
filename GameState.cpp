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
    this->accelerationVelocity += this->accelerationVelocity * dT;

    this->position += this->accelerationVelocity * dT;
    this->position += this->velocity * dT;

    this->velocity = sf::Vector2f(0,0);
    this->acceleration = sf::Vector2f(0,0);
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

bool EntityEvent::tick(float dT, SmartEntity *entity)
{
    this->timePassed += dT;
    return true;
}

MoveToPosEvent::MoveToPosEvent() : EntityEvent()
{
}

bool MoveToPosEvent::tick(float dT, SmartEntity *entity)
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
        return false;
    }
    return false;
}

MoveToPosEaseEvent::MoveToPosEaseEvent() : EntityEvent(), easeMoveType(EaseType::EaseOutSine), easeDuration(1)
{
}

float easeDefualt(float x) {
    return 1;
}

float easeOutBack(float x)
{
    float c1 = 1.70158f;
    float c3 = c1 + 1.0f;
    return 1.0f + c3 * pow(x-1.0f,3.0f) + c1 * pow(x-1.0f,2.0f);
}

float easeOutSine(float x)
{
    return std::clamp(sin(x * 3.14159f / 2),0.0f, 1.0f);
}

float easeOutCirc(float x)
{
    return std::clamp(sqrt(1 - x * x),0.0f,1.0f);
}

std::function<float(float)> getEaseFunction(EaseType type)
{
    if(type == EaseType::Default) return std::function<float(float)>(easeDefualt);
    if(type == EaseType::EaseOutSine) return std::function<float(float)>(easeOutSine);
    if(type == EaseType::EaseOutCirc) return std::function<float(float)>(easeOutCirc);
    if(type == EaseType::EaseOutBack) return std::function<float(float)>(easeOutBack);
    return std::function<float(float)>(easeOutSine);
}

bool MoveToPosEaseEvent::tick(float dT, SmartEntity *entity)
{
    this->EntityEvent::tick(dT, entity);
    float progress = this->timePassed / this->easeDuration;
    if(progress > 1) progress = 1;
    
    auto easeFunction = getEaseFunction(this->easeMoveType);
    entity->position = this->startPos + (this->targetPos - this->startPos) * easeFunction(progress);

    return this->timePassed >= this->easeDuration;
}

AlteratingVelocityEvent::AlteratingVelocityEvent() : EntityEvent()
{
}

bool AlteratingVelocityEvent::tick(float dT, SmartEntity *entity)
{
    this->EntityEvent::tick(dT, entity);
    auto easeFunction = getEaseFunction(this->easeMoveType);
    entity->velocity.x += easeFunction(this->timePassed) * this->maxVelocity * cos(this->angle);
    entity->velocity.y += easeFunction(this->timePassed) * this->maxVelocity * sin(this->angle);
    return false;
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

