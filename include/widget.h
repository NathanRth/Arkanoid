#ifndef WIDGET_H
#define WIDGET_H

#include <string>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include "vec2.h"

class Widget
{
  public:
    Widget(Widget *parent = nullptr);

    void setPos(Vec2i p);
    void setSize(Vec2i s) { m_size = s; }

    virtual void draw(SDL_Surface *srf) {}

    Vec2i pos() const { return m_pos; }
    Vec2i size() const { return m_size; }

    SDL_Rect toSDLRect();

  protected:
    // position et taille sur la fenetre
    Vec2i m_size, m_pos;
    // wideget parent, si il est !NULL
    Widget *m_parent;
};

#endif // WIDGET_H
