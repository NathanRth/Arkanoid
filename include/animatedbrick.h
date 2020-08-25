#ifndef ANIMATED_BRICK_H
#define ANIMATED_BRICK_H

#include "sprite.h"

class AnimatedBrick : public Sprite
{
  public:
    // pos : position à l'écran
    // type : type de la brique (or ou argent)
    // atlas : atlas de ref des textures
    // hitLeft : nombre de coup restant pour détruire la brique (si ==-1 alors brique incassable)
    AnimatedBrick(Vec2i pos, int type, Atlas &atlas, int hitLeft);
};

#endif