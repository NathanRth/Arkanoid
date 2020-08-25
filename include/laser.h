#ifndef LASER_H
#define LASER_H

#include "sprite.h"
#include "vaus.h"
#include "player.h"
#include "ball.h"

class Laser : public Sprite
{
  public:
    Laser(Vec2i pos, Atlas &atlas, Vec2f fpos);

    void setFpos(Vec2f pos) { fposition = pos; }

    Vec2f fpos()	{ return fposition; }

    void move(SDL_Surface *win_surf, Vaus vaus);

    Vec2i checkCollision(std::vector<Sprite *> &levelBricks, Player *player, int currentLevel,Ball* ball);

  private:

    Vec2f fposition;
};

#endif