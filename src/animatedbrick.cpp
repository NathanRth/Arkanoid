#include "animatedbrick.h"

AnimatedBrick::AnimatedBrick(Vec2i pos, int type, Atlas &atlas,int hitLeft) :
    Sprite(Texture(atlas),6,6)
{
    m_pos = pos;
    m_size = {32,16};
    m_tex.setSize({32,16});
    //m_hasAnimation = true;
    m_animate = true;
    m_cycle = false;
    //m_maxRowLength = 6;
    //m_frames = 6;
    m_currentFrame = 0;
    m_brickType = type;
    m_hitLeft = hitLeft;
    
    if(type == 13)
    {
        m_startPos = {0,32};
    }
    else if(type == 14)
    {
        m_startPos = {0,48};
    }
}