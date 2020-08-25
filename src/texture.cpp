#include "texture.h"

Texture::Texture(Atlas &atlas, Vec2i pos, Vec2i size) : 
    m_atlas(atlas), m_pos(pos), m_size(size)
{
}

void Texture::draw(SDL_Surface *srf, Vec2i destPos, Vec2i destSize)
{
    SDL_Rect src = {m_pos.x, m_pos.y, m_size.x, m_size.y};
    SDL_Rect dest = {destPos.x, destPos.y, destSize.x, destSize.y};
    SDL_BlitSurface(m_atlas.surface(), &src, srf, &dest);
}

void Texture::setAtlas(Atlas &atlas)
{
    m_atlas = atlas;
}

void Texture::setPos(Vec2i pos)
{
    m_pos = pos;
}

void Texture::setSize(Vec2i size)
{
    m_size = size;
}