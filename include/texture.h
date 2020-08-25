#ifndef TEXTURE_H
#define TEXTURE_H

#include "atlas.h"
#include "vec2.h"

class Texture
{
  public:
    Texture(Atlas &atlas, Vec2i pos = {0,0}, Vec2i size = {0,0});

    void draw(SDL_Surface *srf, Vec2i destPos, Vec2i destSize);

    void setAtlas(Atlas &atlas);
    void setPos(Vec2i pos);
    void setSize(Vec2i size);

    Atlas &atlas()  { return m_atlas; }
    Vec2i pos()     { return m_pos; }
    Vec2i size()    { return m_size; }

  private:
    Atlas &m_atlas;
    // position et taille de la texture sur ** l'atlas **
    Vec2i m_pos, m_size;
};

#endif // TEXTURE_H
