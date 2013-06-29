#ifndef _ResourceCache_h_
#define _ResourceCache_h_

#include <string>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template <class T>
class ResourceCache
{
    protected:
        std::map<std::string, T*> resmap;

    public:
        ResourceCache()
        {
        }
        ~ResourceCache()
        {
            removeAll();
        }

        bool alreadyExists(const std::string& identifier)
        {
            return resmap.find(identifier) != resmap.end();
        }

        void add(const std::string& identifier, const std::string& filename)
        {
            if (alreadyExists(identifier))
                return;

            T* resource = new T();;
            if(!resource->loadFromFile(filename))
            {
                delete resource;
                resource = NULL;
                return;
            }
            resmap[identifier] = resource;
 }

        void remove(const std::string& identifier)
        {
            delete resmap[identifier];
            resmap.erase(identifier);
        }

        void removeAll()
        {
            if (resmap.empty())
                return;

            while (resmap.begin() != resmap.end())
            {
                delete resmap.begin()->second;
                resmap.erase(resmap.begin());
            }
            resmap.clear();
        }

        T* get(const std::string& identifier)
        {
            //std::map<std::string, sf::Image*>::iterator search;
            //search = resmap.find(identifier);
            return alreadyExists(identifier) ? resmap[identifier] : NULL;
        }

        T* operator[] (const std::string& identifier)
        {
            return get(identifier);
        }
};



class TextureCache : public ResourceCache<sf::Texture>
{
    public:
        sf::Sprite makeSprite(const std::string& identifier);
};

class FontCache : public ResourceCache<sf::Font>
{
    public:
        void add(const std::string& identifier, const std::string& filename);
        sf::Text makeText(const std::string& identifier, const std::string& str, const int size);
        sf::Text makeText(const std::string& identifier, const int size);
};

class SoundCache : public ResourceCache<sf::SoundBuffer>
{
    public:
        sf::Sound makeSound(const std::string& identifier);
};

class MusicCache : public ResourceCache<sf::Music>
{
    public:
        void add(const std::string& identifier, const std::string& filename);
};

#endif
