#ifndef SURFACE_H
#define SURFACE_H

#include "widget.h"
#include <SDL.h>

class Surface : public Widget
{
  public:
    Surface(SDL_Surface *surf, Uint32 color = 0, Widget *parent = nullptr);
    Surface(int width, int height, Uint32 color = 0, Widget *parent = nullptr);
    ~Surface();

    void refresh();
    void draw(SDL_Surface *surf) override;
    void optimize(bool b);
    SDL_Surface *toSDLSurface_ptr() { return m_surface; }

  private:
    Uint32 m_color;
    SDL_Surface *m_surface;
};

#endif
