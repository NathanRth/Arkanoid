#include "staticbrick.h"

StaticBrick::StaticBrick(Vec2i pos, int type, Atlas &atlas,int hitLeft) : 
    Sprite(Texture(atlas))
{
    m_pos = pos;
    m_size = {32,16};
    m_tex.setSize({32,16});
    m_brickType = type;
    m_hitLeft = hitLeft;
    
    if(type > 0 && type < 13)
    {
        m_tex.setPos({((type-1)%6)*32,((type-1)/6)*16});
    }
    else if(type > 100 && type < 113)
    {
        m_tex.setPos({((type-101)%6)*32,((type-101)/6)*16});
    }
}