#include "GameState.h"

#include <Core/Core.h>
#include <Core/CoreRegistry.h>

#include <System/ResourceManager.h>

REGISTER_GAME("Game", GameState);

GameState::GameState()
{
}

void GameState::init(ResourceManager& resources)
{
    CoreState::init(resources);
    map = new Map(640 / 4, 480 / 4);
    map->randomize();
}

void GameState::deinit()
{
    delete map;
}

void GameState::handleInput()
{
}

void GameState::logic(float timeStep)
{
}

void GameState::draw(sf::RenderTarget& renderer)
{
    renderer.draw(*map);
}
