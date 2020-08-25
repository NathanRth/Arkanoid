#ifndef SPRITE_H
#define SPRITE_H

#include "texture.h"
#include "object.h"
#include "mtime.h"

class Sprite : public Object
{
  public:

    // pour les sprites non-animés
    Sprite(Texture tex, Vec2i pos = {0, 0}, Vec2i size = {0, 0});
    // pour les sprite animés
    Sprite(Texture startTex, int nbFrames, int maxRowLength, Vec2i pos = {0, 0}, Vec2i size = {0, 0});

    // dessine le sprite à l'ecran, attend un timestamp pour savoir s'il faut changer de frame (voir .cpp)
    void draw(SDL_Surface *sfc, mtime_t time = 0);

    /***** animation *****/

    // déclenche l'animation si on envoie true
    // arete l'animation si on met false, ou si l'animation est finie eet que m_cycle = false
    void animate(bool b);
    // determine si l'animation boucle sur elle-même (boucle tant que m_cycle = true)
    void cycleAnimation(bool b);


    int getBrickType();
    int getHitLeft() { return m_hitLeft; }

    void setHitLeft(int hitLeft) { m_hitLeft = hitLeft; }

  protected:
    Texture m_tex;

    // animation
    bool m_hasAnimation; // indique si le sprite est un sprite animé ou non
    int m_maxRowLength;  // le nombre max de frame par ligne sur l'atlas
    Vec2i m_startPos;    // position sur l'atlas de la texture de départ
    int m_frames;        // nombre de frame
    int m_currentFrame;  // frame actuelle
    bool m_animate;      // est en train d'etre animé
    bool m_cycle;        // l'animation boucle sur elle meme
    mtime_t m_prevTime;  // stocke le timestamp de la frame précédente (pas du dernier timestamp recu !)
    // briques
    int m_brickType;     // type de la brique
    int m_hitLeft;       // coup restant pour détruire la brique
};

#endif // SPRITE_H
