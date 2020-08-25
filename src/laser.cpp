#include "laser.h"

Laser::Laser(Vec2i pos, Atlas &atlas, Vec2f fpos) : 
    Sprite(Texture(atlas,{4, 69}, {8, 6}), pos, {8, 6}), fposition(fpos)
{

}

void Laser::move(SDL_Surface *win_surf, Vaus vaus)
{

    fposition.y = fposition.y - 0.5;
    int x = (int)fposition.x;        //cherche les coord x et y entière pour les mettre dans m_pos
    int y = (int)fposition.y;

    m_pos = {x, y};                 //m_pos= coord entière du laser pour l'affichage
}

Vec2i Laser::checkCollision(std::vector<Sprite *> &levelBricks, Player *player, int currentLevel,Ball* ball)
{
    if(m_pos.y<0)
        return {-2, -2};
    // auto = std::vector<Sprite*>::iterator
    // pour chaque brique
    for (auto it = levelBricks.begin(); it != levelBricks.end(); it++)
    {
        // on calcule les bornes
        int xmin = (*it)->pos().x;
        int ymin = (*it)->pos().y;
        int xmax = (*it)->pos().x + (*it)->size().x;
        int ymax = (*it)->pos().y + (*it)->size().y;

        int laserxMiddle = m_pos.x + (m_size.x / 2);
        int laseryMiddle = m_pos.y + (m_size.y / 2);


        // la ball est dans les bornes ?
        if ((laserxMiddle > xmin && laserxMiddle < xmax) //la balle est dans les bornes x de la brique ?
            &&
            (laseryMiddle > ymin &&
              m_pos.y < ymax) //touché depuis le bas de la brique
             ) //touché depuis le haut de la brique
        {

            if (ball->destroyBrick(*it, player, currentLevel) == true)
            {
                Vec2i brickPos = (*it)->pos();
                levelBricks.erase(it);
                return brickPos;
            }
            else if((*it)->getBrickType()==14)
                return {-2,-2};

            return {-1, -1};
        }
    }
    return {-1, -1};
}
