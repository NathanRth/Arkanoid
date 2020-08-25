#ifndef STATIC_BRICK_H
#define STATIC_BRICK_H

#include "sprite.h"

class StaticBrick : public Sprite
{
  public:
    // pos : position à l'écran
    // type : type de la brique (couleur)
    // atlas : atlas de ref des textures
    // hitLeft : nombre de coup restant pour détruire la brique (si ==-1 alors brique incassable)
    StaticBrick(Vec2i pos, int type, Atlas &atlas, int hitLeft);
};

#endif