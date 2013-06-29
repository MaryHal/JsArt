#include "CoreState.h"

#include <SFML/Graphics.hpp>

CoreState::CoreState()
    : textures(NULL),
      fonts(NULL),
      sounds(NULL),
      music(NULL)
{
}

CoreState::~CoreState()
{
}

void CoreState::init(ResourceManager& resources)
{
    textures = &resources.textureCache;
    fonts    = &resources.fontCache;
    sounds   = &resources.soundCache;
    music    = &resources.musicCache;
}

