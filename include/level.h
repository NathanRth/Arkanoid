#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <sprite.h>

struct level_s
{
    std::vector<Sprite *> bricks;
    int background;
    Vec2i gameSize;
    bool cylindrical;
    struct level_s *next;
    int levelIndex;
};

using Level = struct level_s;

#endif