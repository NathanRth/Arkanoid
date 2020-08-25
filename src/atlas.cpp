#include "atlas.h"

#include <iostream>

Atlas::Atlas(std::string src_file)
{
    atlas = SDL_LoadBMP(src_file.c_str());
    if (atlas == NULL)
    {
        std::cerr << __FUNCTION__
                  << "Error while loading Atlas file (" << src_file << "): "
                  << SDL_GetError() << std::endl;
    }
}

void Atlas::setColorKey(Uint32 key)
{
    SDL_SetColorKey(atlas, true, key);
}
