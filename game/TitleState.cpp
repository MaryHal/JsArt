#include "TitleState.h"

#include <Core/Core.h>
#include <Core/CoreRegistry.h>

#include <System/ResourceManager.h>

REGISTER_GAME("Title", TitleState);

TitleState::TitleState()
{
}

void TitleState::init(ResourceManager& resources)
{
    CoreState::init(resources);

    fonts->add("hahaha", "data/fonts/comic.ttf");
    text = fonts->makeText("hahaha", "Hello Comic Sans World", 46);
    text.setColor(sf::Color::White);
}

void TitleState::deinit()
{
}

void TitleState::handleInput()
{
}

void TitleState::logic(float timeStep)
{
}

void TitleState::draw(sf::RenderTarget& renderer)
{
    renderer.draw(text);
}
