#ifndef _Map_h_
#define _Map_h_

#include <SFML/Graphics.hpp>

class Cell : public sf::Drawable
{
    public:
    Cell()
        : box(sf::Vector2f(4.0f, 4.0f))
    {
        alive = 0;
    }
    int alive;
    sf::RectangleShape box;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(box);
    }
};

class Map : public sf::Drawable
{
    private:
    Cell** data;
    int width;
    int height;

    public:
    Map(int width, int height);
    ~Map();

    void randomize();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
