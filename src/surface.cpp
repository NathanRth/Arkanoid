#include "surface.h"

Surface::Surface(SDL_Surface *surf, Uint32 color, Widget *parent) : 
    Widget(parent), m_color(color)
{
    if (m_parent)
    {
        m_pos = m_pos + m_parent->pos();
    }
    m_size = {surf->w, surf->h};
    m_surface = surf;
}

Surface::Surface(int width, int height, Uint32 color, Widget *parent) : 
    Widget(parent), m_color(color)
{
    if (m_parent)
    {
        m_pos = m_pos + m_parent->pos();
    }
    m_size = {width, height};

    Uint32 rmask, gmask, bmask, amask;
    /* SDL représente chaque pixel par un Uint32 (RGBA) donc les masques dépendent
     * de la représentationgrand-boutiste/petit-boutiste du système
     */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    // on génère la surface à la taille de la fenêtre
    m_surface = SDL_CreateRGBSurface(0, width, height, 32,
                                     rmask, gmask, bmask, amask);
    if (m_surface == NULL)
    {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }
    SDL_FillRect(m_surface, NULL, m_color);
}

Surface::~Surface()
{
    SDL_FreeSurface(m_surface);
}

void Surface::optimize(bool b)
{
    SDL_SetSurfaceRLE(m_surface, static_cast<int>(b));
}

void Surface::refresh()
{
    SDL_FillRect(m_surface, NULL, m_color);
}

void Surface::draw(SDL_Surface *surf)
{
    SDL_Rect dst = toSDLRect();
    SDL_BlitSurface(m_surface, NULL, surf, &dst);
}