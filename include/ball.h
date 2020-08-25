#ifndef BALL_H
#define BALL_H

#include <algorithm>
#include <iostream>
#include "sprite.h"
#include "vaus.h"
#include "player.h"
#include "staticbrick.h"
#include "animatedbrick.h"
#include "text.h"
#include "widget.h"
#include "bonus.h"

#include <vector>

#include <sprite.h>

class Ball : public Sprite
{
public:
    Ball(Texture tex, Vec2i pos = {0,0}, Vec2i size = {0,0},bool collider = true,bool moving = false,Vec2f force = {0.0,0.0}, Vec2f fpos={0.0,0.0},float speed = 1.0);

    void setMove(bool move) { isMoving = move; }
    void setForce(Vec2f force) { currentForce = force; }
    void setFpos(Vec2f pos) { fposition = pos; }
    void setSpeed(float speed) { fspeed = speed; }

    bool doesMove()	{ return isMoving; }
    Vec2f force()	{ return currentForce; }
    Vec2f fpos()	{ return fposition; }
    float speed()    { return fspeed; }

    bool moveBall(SDL_Surface* win_surf,Vaus vaus,bool cylindrical, Player* player);
    Vec2i checkCollision(std::vector<Sprite*> &levelBricks, Player* player,int currentLevel);

    bool destroyBrick(Sprite* it, Player* player,int currentLevel);

private:
    bool isMoving;
    Vec2f currentForce;
    Vec2f fposition;
    float fspeed;
};

#endif