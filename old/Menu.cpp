#include <cstdio>
#include "Menu.h"

#include "System/InputManager.h"

Menu::Menu()
    : currentChoice(0), font(NULL), fontSize(30), longest(0)
{
}

Menu::Menu(const std::string& t)
    : currentChoice(0), font(&sf::Font::GetDefaultFont()), fontSize(30), longest(0)
{
    SetTitle(t);
}

Menu::Menu(const std::string& t, const sf::Font& f, int fontHeight)
    : currentChoice(0), font(&f), fontSize(fontHeight), longest(0)
{
    SetTitle(t);
}

Menu::~Menu()
{
    items.clear();
}

int Menu:: __checkLongest(int current)
{
    if (current > longest)
        return current;
    return longest;
}

void Menu::AddItem(std::string item)
{
    sf::Text str(item, *font, fontSize);

    // Help us find the longest string
    longest = __checkLongest(str.GetRect().Width);

    items.push_back(str);
}

void Menu::MakeMenu()
{
    rect = 
    sf::Shape::Rectangle(0, 0,
                         (longest + 2 * metrics.margin), 
                         (metrics.newline * (items.size() + 1) + 3 * metrics.margin),
                         sf::Color(100, 100, 100, 32),
                         2, sf::Color(240, 240, 240, 200)
                         );
    
    titleString.SetPosition(metrics.margin, metrics.margin);

    titleLine = 
    sf::Shape::Line(metrics.margin, metrics.margin + metrics.newline, 
                    longest, metrics.margin + metrics.newline,
                    2, sf::Color(240, 240, 240, 100)
                    );

    for (unsigned int i = 0; i < items.size(); ++i)
    {
        items[i].SetPosition(metrics.margin, (metrics.newline * (i + 1)) + (metrics.margin * 2));
    }
}

void Menu::HandleInput(InputManager& input)
{
    if (input.TestEvent("Up", sf::Event::KeyPressed))
    {
        items[currentChoice].SetColor(sf::Color(255, 255, 255));
        --currentChoice;
        if (currentChoice < 0)
            currentChoice = items.size() - 1;
    }

    if (input.TestEvent("Down", sf::Event::KeyPressed))
    {
        items[currentChoice].SetColor(sf::Color(255, 255, 255));
        ++currentChoice;
        if (currentChoice > (signed)items.size() - 1) // hehehehahahahahhohaha...
            currentChoice = 0;
    }

    if (input.TestEvent("Go", sf::Event::KeyPressed))
        choice = (std::string)items[currentChoice].GetString();
}

void Menu::Logic()
{
    items[currentChoice].SetColor(sf::Color(255, 255, 0));
}

void Menu::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(rect);

    target.Draw(titleString);
    target.Draw(titleLine);

    for (std::vector<sf::Text>::const_iterator iter = items.begin();
            iter != items.end();
            ++iter)
    {
        target.Draw(*iter);
    }
}

void Menu::SetFont(const sf::Font& f, int fontHeight)
{
    font = &f;
    fontSize = fontHeight;
}

void Menu::SetTitle(const std::string& t)
{
    title = t;
    titleString = sf::Text(title, *font, fontSize);

    longest = __checkLongest(titleString.GetRect().Width);
}

void Menu::SetMetrics(const MenuMetrics& m)
{
    metrics = m;
}

const std::string& Menu::GetChoice() const
{
    return choice;
}

void Menu::ResetChoice()
{
    choice.clear();
}

