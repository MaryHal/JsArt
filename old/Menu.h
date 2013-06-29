#ifndef _Menu_h_
#define _Menu_h_

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class InputManager;

struct MenuMetrics
{
    MenuMetrics()
        : margin(5), newline(40)
    {
    }

    MenuMetrics(int m, int n)
        : margin(m), newline(n)
    {
    }

    int margin;
    int newline;
};

class Menu : public sf::Drawable
{
    private:
        std::string title;
        sf::Text titleString;

        std::vector<sf::Text> items;
        int currentChoice;
        std::string choice;

        MenuMetrics metrics;
        const sf::Font* font;
        int fontSize;

        int longest;

        sf::Shape titleLine;
        sf::Shape rect;

        int __checkLongest(int current);
        
    public:
        Menu();
        Menu(const std::string& t);
        Menu(const std::string& t, const sf::Font& f, int fontHeight);
        ~Menu();

        void AddItem(std::string item);
        void MakeMenu();

        void HandleInput(InputManager& input);
        void Logic();

        void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        void SetFont(const sf::Font& f, int fontHeight);
        void SetTitle(const std::string& t);
        void SetMetrics(const MenuMetrics& m);

        const std::string& GetChoice() const;
        void ResetChoice();
};

#endif

