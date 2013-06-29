#ifndef _ResourceManager_h_
#define _ResourceManager_h_

#include "ResourceCache.h"

struct ResourceManager
{
    TextureCache textureCache;
    FontCache fontCache;
    SoundCache soundCache;
    MusicCache musicCache;
};

#endif

