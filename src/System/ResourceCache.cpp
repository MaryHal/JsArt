#include "ResourceCache.h"

// ==================================== ResourceCache

// ==================================== TextureCache
sf::Sprite TextureCache::makeSprite(const std::string& identifier)
{
    return sf::Sprite(*get(identifier));
}

// ==================================== FontCache
void FontCache::add(const std::string& identifier, const std::string& filename)
{
    if (alreadyExists(identifier))
        return;

    sf::Font* font = new sf::Font();
    if(!font->loadFromFile(filename))
    {
        delete font;
        font = NULL;
        return;
    }

    resmap[identifier] = font;
}

sf::Text FontCache::makeText(const std::string& identifier, const std::string& str, const int size)
{
    return sf::Text(str, *resmap[identifier], size);
}

sf::Text FontCache::makeText(const std::string& identifier, const int size)
{
    return sf::Text("", *resmap[identifier], size);
}

// ==================================== SoundCache
sf::Sound SoundCache::makeSound(const std::string& identifier)
{
    return sf::Sound(*get(identifier));
}

// ==================================== MusicCache
void MusicCache::add(const std::string& identifier, const std::string& filename)
{
    if (alreadyExists(identifier))
        return;

    sf::Music* music = new sf::Music();
    if (!music->openFromFile(filename))
    {
        delete music;
        music = NULL;
        return;
    }

    resmap[identifier] = music;
}

