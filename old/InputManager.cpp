#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::AddKeyEvent(const std::string& identifier,
                               sf::Keyboard::Key keyCode)
{
    __Input i;
    i.type = KeyboardEvent;
    i.keyCode = keyCode;
    
    // Doesn't mean anything
    i.mouseButton = sf::Mouse::ButtonCount;

    inputmap[identifier] = i;
}

void InputManager::AddMouseEvent(const std::string& identifier,
                                 sf::Mouse::Button mouseButton)
{
    __Input i;
    i.type = MouseEvent;
    i.mouseButton = mouseButton;
    
    // Doesn't mean anything
    i.keyCode = sf::Keyboard::KeyCount;

    inputmap[identifier] = i;
}

sf::Vector2f InputManager::GetMouseCoords() const
{
    sf::Vector2i position = sf::Mouse::GetPosition();
    return sf::Vector2f(position.x, position.y);
}

bool InputManager::TestEvent(const std::string& identifier, sf::Event::EventType eventType)
{
    __Input& i = inputmap[identifier];

    //Mouse event
    if (i.type == MouseEvent &&
        eventType == event.Type && 
        i.mouseButton == event.MouseButton.Button)
    {
        return true;
    }

    //Keyboard event
    if (i.type == KeyboardEvent &&
        eventType == event.Type && 
        i.keyCode == event.Key.Code)
    {
        return true;
    }

    return false;
}

bool InputManager::TestKeyEvent(sf::Keyboard::Key code, sf::Event::EventType eventType)
{
    return event.Type == eventType && code == event.Key.Code;
}

bool InputManager::CloseEvent()
{
    return (event.Type == sf::Event::Closed);
}

sf::Event& InputManager::GetEvent()
{
    return event;
}


