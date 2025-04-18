#include "AppHandler.hpp"
#include <iostream>

Camera::Camera() : currentZoom(), targetedZoom()
{
    
}

Camera::~Camera()
{
}

void Camera::setPosition(sf::Vector2f position)
{
}

void Camera::tick()
{
    
}

Sprite::Sprite() : Atlas(nullptr), texCords1(), texCords2()
{
}

Sprite Sprite::getSpriteRect(int x, int y, int width, int height)
{
    return Sprite();
}

RectDrawable::RectDrawable()
{
}

BatchRenderer::BatchRenderer()
{
    this->drawVBO.create(40000);
    this->drawVBO.setPrimitiveType(sf::PrimitiveType::Triangles);
    this->drawVBO.setUsage(sf::VertexBuffer::Usage::Stream);
}

BatchRenderer::~BatchRenderer()
{
}

std::list<RectDrawable*>::iterator BatchRenderer::stageRect(RectDrawable* rd)
{
    this->drawList.push_back(rd);
    return this->drawList.end();
}

void BatchRenderer::unstageRect(std::list<RectDrawable*>::iterator rdit)
{
    this->drawList.erase(rdit);
}

void BatchRenderer::renderRects(sf::RenderTarget *window)
{
    int i = 0;
    for (auto& q : this->drawList) {

        drawBuffer[i].position = q->position;
        drawBuffer[i].color = q->color;
        drawBuffer[i].texCoords = q->sprite.texCords1;

        drawBuffer[i + 1].position = q->position + sf::Vector2f(q->size.x, 0);
        drawBuffer[i + 1].color = q->color;
        drawBuffer[i + 1].texCoords = sf::Vector2f(q->sprite.texCords2.x, q->sprite.texCords1.y);

        drawBuffer[i + 2].position = q->position + sf::Vector2f(0, q->size.y);
        drawBuffer[i + 2].color = q->color;
        drawBuffer[i + 2].texCoords = sf::Vector2f(q->sprite.texCords1.x, q->sprite.texCords2.y);

        drawBuffer[i + 3].position = q->position + sf::Vector2f(q->size.x, 0);
        drawBuffer[i + 3].color = q->color;
        drawBuffer[i + 3].texCoords = sf::Vector2f(q->sprite.texCords2.x, q->sprite.texCords1.y);

        drawBuffer[i + 4].position = q->position + sf::Vector2f(q->size.x, q->size.y);
        drawBuffer[i + 4].color = q->color;
        drawBuffer[i + 4].texCoords = q->sprite.texCords2;

        drawBuffer[i + 5].position = q->position + sf::Vector2f(0, q->size.y);
        drawBuffer[i + 5].color = q->color;
        drawBuffer[i + 5].texCoords = sf::Vector2f(q->sprite.texCords1.x, q->sprite.texCords2.y);
        i += 6;
    }
    this->drawVBO.update(drawBuffer.data(), i, 0);
    window->draw(drawVBO, 0, i, sf::RenderStates::Default);
    
}

FrameState::FrameState()
{
    
}

FrameState::~FrameState()
{
    
}

void FrameState::tick(float dT)
{
}

void FrameState::tickMenu(float dT, AppHandler* appHandler)
{
    
}

void FrameState::render(sf::RenderTarget *window)
{
}

void FrameState::handleInput()
{
}

AppHandler::AppHandler() : window(), clock(), currentFrameState(nullptr)
{
}

AppHandler::~AppHandler()
{
}

void AppHandler::setUp(int width, int height, std::string title)
{
    this->window.create(sf::VideoMode(width, height), title);

}

void AppHandler::setFrameState(FrameState *frameState)
{
    this->currentFrameState = frameState;
}

void AppHandler::run()
{
    while (window.isOpen()) {
        float deltaTime = std::min(clock.restart().asSeconds(), 0.1f);

        // Low cost updating
        lowCostTimePassed += deltaTime;
        if (lowCostTimePassed > 0.3f) {
            window.setTitle("SDSA FPS: " + std::to_string(1.0f / deltaTime));
            if(this->currentFrameState != nullptr) this->currentFrameState->tickMenu(lowCostTimePassed, this);
            lowCostTimePassed = 0;
        }
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else {
                if(this->currentFrameState != nullptr) this->currentFrameState->handleInput();
            }
        }

        

        // Clear the window
        window.clear(sf::Color::Magenta);

        if(this->currentFrameState != nullptr) {
            this->currentFrameState->tick(deltaTime);
            this->currentFrameState->render(&this->window);
        }

        // Display the content
        window.display();
    }
}
