#ifndef _CoreState_h_
#define _CoreState_h_

#include "../System/ResourceManager.h"

namespace sf
{
    class RenderTarget;
}

class CoreState
{
    protected:
        TextureCache* textures;
        FontCache*    fonts;
        SoundCache*   sounds;
        MusicCache*   music;

    public:
        CoreState();
        virtual ~CoreState();

        virtual void init(ResourceManager& resources);
        virtual void deinit() = 0;

        virtual void handleInput() = 0;
        virtual void logic(float timeStep) = 0;
        virtual void draw(sf::RenderTarget& renderer) = 0;
};

#endif
