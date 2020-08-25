#ifndef BONUS_H
#define BONUS_H

#include "sprite.h"
#include "vaus.h"
#include "player.h"

class Bonus : public Sprite
{
  public:
    Bonus(Vec2i pos, int num, Atlas &atlas, Vec2f fpos);

    void setFpos(Vec2f pos) { fposition = pos; }

    Vec2f fpos()	{ return fposition; }

    int move(SDL_Surface *win_surf, Vaus vaus);

  private:

    int m_idBonus;
    Vec2f fposition;
};

#endif