#ifndef _GameState_h_
#define _GameState_h_

#include <Core/CoreState.h>
#include <SFML/Graphics.hpp>
#include "Map.h"

class InputManager;

class GameState : public CoreState
{
    private:
    Map* map;

    public:
    GameState();

    void init(ResourceManager& resources);
    void deinit();

    void handleInput();
    void logic(float timeStep);
    void draw(sf::RenderTarget& renderer);
};

#endif
