#include "Map.h"
#include <Math/Random.h>
#include <GL/gl.h>
#include <cstdio>

Map::Map(int width, int height)
{
    data = new Cell*[height];
    for (int i = 0; i < height; ++i)
        data[i] = new Cell[width];

    this->width = width;
    this->height = height;
}

Map::~Map()
{
    for (int i = 0; i < height; ++i)
        delete [] data[i];
    delete [] data;
}

void Map::randomize()
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
        {
            data[y][x].alive = rng.genRand(0, 1);
            data[y][x].box.setPosition(x * 4, y * 4);
        }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            if (data[y][x].alive)
            {
                target.draw(data[y][x].box);
            }
        }
    }
}
