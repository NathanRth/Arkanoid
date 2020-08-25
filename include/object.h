#ifndef OBJECT_H
#define OBJECT_H

#include "vec2.h"
class Object
{
  public:
    Object(Vec2i pos, Vec2i size, bool collider);

    // setters
    void setPos(Vec2i pos) { m_pos = pos; }
    void setSize(Vec2i size) { m_size = size; }
    void setCollider(bool canCollide) { has_collider = canCollide; }

    // getters
    Vec2i pos() { return m_pos; }
    Vec2i size() { return m_size; }
    bool collider() { return has_collider; }

  protected:
    // posititon de l'objet sur la fenetre, taille de l'objet sur la fenêtre
    Vec2i m_pos, m_size;

    bool has_collider;
    /*
    détermine si l'object a un collider (pour les briques, le vaisseau, les murs, etc...),
    si oui on a m_pos = {xmin,ymin} et m_pos+m_size={xmax,ymax} pour les coordonnées du collider en question
    */
};

#endif