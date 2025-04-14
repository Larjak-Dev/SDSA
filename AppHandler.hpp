#pragma once
#include <SFML/Graphics.hpp>
#include <print>
#include <ranges>
#include <vector>
#include <list>
#include <array>
#include <math.h>


class AppHandler;

class Camera {
    sf::Vector2f currentPos;
    sf::Vector2f targetedPos;
    
    float currentZoom;
    float targetedZoom;
public:
    sf::Transform cameraTransform;

    Camera();
    ~Camera();

    void setPosition(sf::Vector2f position);

    void tick();
};

class Sprite {
public:
    sf::Texture* Atlas;
    sf::Vector2f texCords1;
    sf::Vector2f texCords2;
    

    Sprite();

    static Sprite getSpriteRect(int x, int y, int width, int height);
    
};
    
class RectDrawable {
public:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
    Sprite sprite;

    RectDrawable();
};

class BatchRenderer {
    std::array<sf::Vertex, 40000> drawBuffer;
    sf::VertexBuffer drawVBO;
    std::list<RectDrawable*> drawList;
public:

    BatchRenderer();
    ~BatchRenderer();

    std::list<RectDrawable*>::iterator stageRect(RectDrawable* rd);
    void unstageRect(std::list<RectDrawable*>::iterator rdit);
    void renderRects(sf::RenderTarget* window);
};

class FrameState {
public:
    
    FrameState();
    ~FrameState();

    virtual void tick(float dT);
    virtual void tickMenu(float dT, AppHandler* appHandler);
    virtual void render(sf::RenderTarget* window);
    virtual void handleInput();
};

class AppHandler {
    FrameState* currentFrameState;
    sf::Clock clock;
    float lowCostTimePassed = 0;
    
public:
    sf::RenderWindow window;

    AppHandler();
    ~AppHandler();


    void setUp(int width, int height, std::string title);
    void setFrameState(FrameState* frameState);

    void run();

};

