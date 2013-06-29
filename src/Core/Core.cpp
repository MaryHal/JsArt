#include "Core.h"
#include "CoreRegistry.h"

#include "../System/ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <cstdio>

const std::string Core::version = "0.01a";

sf::RenderWindow* Core::renderer = NULL;
ResourceManager* Core::resources = NULL;

CoreState* Core::currentState = NULL;
CoreState* Core::nextState = NULL;
bool Core::quit = false;

void Core::init()
{
    sf::VideoMode videoMode(640, 480, 32);
    renderer = new sf::RenderWindow(videoMode, "Hello World", sf::Style::Close);
    renderer->setFramerateLimit(60);
    renderer->setVerticalSyncEnabled(true);
    renderer->setKeyRepeatEnabled(false);

    // Center our window. Keep in mind that SFML does not support multiple monitors right now.
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    renderer->setPosition(sf::Vector2i(desktop.width  / 2 - videoMode.width  / 2,
                                       desktop.height / 2 - videoMode.height / 2));

    if (sf::Shader::isAvailable())
    {
        printf("Shaders Available\n");
    }

    resources = new ResourceManager;
}

void Core::deinit()
{
    delete renderer;
    delete resources;
}

void Core::run()
{
    if (currentState == NULL)
    {
        printf(" ## No Initial State");
        return;
    }

    sf::Clock clock;
    while (!quit && renderer->isOpen())
    {
        if (nextState)
        {
            changeState(nextState);
        }

        // Process Events
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            quit = true;
        }

        sf::Event event;
        while (renderer->pollEvent(event))
        {
            // Close Events
            if (event.type == sf::Event::Closed)
                quit = true;
        }

        renderer->clear();

        //printf("%f\n", 1.f / renderer->GetFrameTime());
        currentState->logic(clock.restart().asMilliseconds());
        currentState->draw(*renderer);

        renderer->display();
    }

    renderer->close();
    changeState(NULL);
}

void Core::changeState(CoreState* s)
{
    if (currentState)
    {
        currentState->deinit();
        printf(" -- Deinitialized State: \"%s\"\n", getStateName().c_str());
    }

    currentState = s;

    if (currentState == NULL)
    {
        return;
    }

    currentState->init(*resources);
    printf(" -- Initialized State: \"%s\"\n", getStateName().c_str());

    nextState = NULL;
}

void Core::setNextState(CoreState* s)
{
    nextState = s;
}

void Core::exit()
{
    quit = true;
}

const std::string& Core::getStateName()
{
    return CoreRegistry::getStateName(currentState);
}

ResourceManager* Core::getResourceManager()
{
    return resources;
}

const std::string& Core::getVersion()
{
    return version;
}
