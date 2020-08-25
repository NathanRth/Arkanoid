#include "sprite.h"

// dans le cas d'un héritage virtuel je ne suis pas sur qu'il faille initialiser object ici...
Sprite::Sprite(Texture tex, Vec2i pos, Vec2i size) : Object(pos, size, false), m_tex(tex), m_startPos({0, 0})
{
    m_hasAnimation = false;
    m_animate = false;
    m_cycle = false;

    m_maxRowLength = 0;
    m_frames = 0;
    m_currentFrame = 0;
    m_prevTime = 0;
    m_brickType = 0;
}

Sprite::Sprite(Texture startTex, int nbFrames, int maxRowLength, Vec2i pos, Vec2i size) : Object(pos, size, false), m_tex(startTex), m_startPos(m_tex.pos())
{
    m_hasAnimation = true;
    m_animate = false;
    m_cycle = false;

    m_maxRowLength = maxRowLength;
    m_frames = nbFrames;
    m_currentFrame = 0;
    m_prevTime = 0;
}

void Sprite::draw(SDL_Surface *srf, mtime_t time)
{
    // dessine la texture
    m_tex.draw(srf, m_pos, m_size);

    if (m_hasAnimation)
    {
        // calcule les cordonées de la texture à afficher en fonction du numéro de la frame
        m_tex.setPos({m_startPos.x + (m_currentFrame % m_maxRowLength) * m_size.x,
                      m_startPos.y + (m_currentFrame / m_maxRowLength) * m_size.y});

        // si on anime et que le dernier changement de frame était il y a au moins 100ms
        if (m_animate && ((time - m_prevTime) > 100))
        {
            if (m_currentFrame >= m_frames - 1)
            {
                if (!m_cycle)
                {
                    // on ne boucle pas -> on arete l'animation
                    m_animate = false;
                }
                //on revient à la première frame
                m_currentFrame = 0;
            }
            else
            {
                // frame suivante
                m_currentFrame += 1;
            }
            // comme on a changé de frame, on retient le timestamp
            m_prevTime = time;
        }
    }
}

int Sprite::getBrickType()
{
    if (m_brickType > 100)
        return m_brickType - 100;
    else
        return m_brickType;
}

void Sprite::animate(bool b)
{
    m_animate = b;
}

void Sprite::cycleAnimation(bool b)
{
    m_cycle = b;
}