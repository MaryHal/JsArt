#ifndef _TitleState_h_
#define _TitleState_h_

#include <Core/CoreState.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class InputManager;

class TitleState : public CoreState
{
    private:
    sf::Text text;

    public:
    TitleState();

    void init(ResourceManager& resources);
    void deinit();

    void handleInput();
    void logic(float timeStep);
    void draw(sf::RenderTarget& renderer);
};

#endif
