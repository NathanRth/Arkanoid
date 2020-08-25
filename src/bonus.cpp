#include "bonus.h"

Bonus::Bonus(Vec2i pos, int id, Atlas &atlas, Vec2f fpos) : 
    Sprite(Texture(atlas), 6, 6, pos, {32, 16}), m_idBonus(id), fposition(fpos)
{
    //m_hasAnimation = true;
    m_cycle = true;
    m_animate = true;
    //m_maxRowLength = 6;
    //m_frames = 6;
    m_currentFrame = 0;

    m_tex.setPos({256, m_idBonus * 16});
    m_tex.setSize({32, 16});
    m_startPos = m_tex.pos();
}

int Bonus::move(SDL_Surface *win_surf, Vaus vaus)
{
    // faire descendre le bonus vers le bas de l'écran
    //Vec2f move = {0.0,0.2};				   //ajoute une force de 0.0,0.2 au bonus
    fposition.y = fposition.y + 0.2; //.operator+(move); //ajoute ce vecteur à la position float
    int x = (int)fposition.x;        //cherche les coord x et y entière pour les mettre dans m_pos
    int y = (int)fposition.y;

    m_pos = {x, y}; //m_pos= coord entière du bonus pour l'affichage

    if (m_pos.y > (vaus.pos().y - m_size.y) &&
        m_pos.y < vaus.pos().y &&
        m_pos.x > (vaus.pos().x - m_size.x) &&
        m_pos.x < (vaus.pos().x + vaus.size().x))
    {
        return m_idBonus;
    }
    return -1;
}
