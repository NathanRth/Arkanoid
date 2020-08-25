#ifndef VAUS_H
#define VAUS_H

#include <iostream>
#include "sprite.h"

class Vaus : public Sprite
{
  public:
    Vaus(int vaussize, Texture tex, Vec2i pos = {0, 0}, Vec2i size = {0, 0}, bool collider = true, int move = 0);

    void setSize(int size) { current_size = size; }
    void setDirection(int direction) { movingDirection = direction; }

    int vsize() { return current_size; }
    int direction() { return movingDirection; }

    float moveVaus(SDL_Surface *win_surf);

  private:
    int current_size;
    int movingDirection;
};

#endif