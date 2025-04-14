
#include "AppHandler.hpp"
#include "LevelOne.hpp"
#include <iostream>

int main() {
    std::cout << "Starting App! \n";

    AppHandler appHandler;
    appHandler.setUp(800, 600, "SDSA");

    // GameState gameState;
    LevelOne levelOne;
    appHandler.setFrameState(&levelOne);
    levelOne.init();

    appHandler.run();

    std::cout << "Closing App! \n";
    return 0;
}