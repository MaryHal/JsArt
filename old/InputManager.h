#ifndef _InputManager_h_
#define _InputManager_h_

#include <string>
#include <map>

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

// This shadows the SFML event types
//sf::Event::<EventType>
enum EventType
{
    Closed,
    Resized,
    LostFocus,
    GainedFocus,
    TextEntered,
    KeyPressed,
    KeyReleased,
    MouseWheelMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseEntered,
    MouseLeft,
    JoyButtonPressed,
    JoyButtonReleased,
    JoyMoved,

    Count // Keep last -- total number of event types
}; 

class InputManager
{
    private:
        enum InputType
        {
            KeyboardEvent,
            MouseEvent,
            JoypadEvent
        };

        struct __Input
        {
            InputType type;
            sf::Keyboard::Key keyCode;
            sf::Mouse::Button mouseButton;
        };

        std::map<std::string, __Input> inputmap;

        sf::Event event;
        const sf::Vector2i windowSize;

    public:
        InputManager();
        ~InputManager();

        void AddKeyEvent(const std::string& identifier,
                         sf::Keyboard::Key keyCode);

        void AddMouseEvent(const std::string& identifier,
                           sf::Mouse::Button mouseButton);

        sf::Vector2f GetMouseCoords() const;

        bool TestEvent(const std::string& identifier, sf::Event::EventType eventType);
        bool TestKeyEvent(sf::Keyboard::Key code, sf::Event::EventType eventType);
        bool CloseEvent();

        sf::Event& GetEvent();
};

#endif

