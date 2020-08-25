#include "button.h"

Button::Button(Texture tex, Widget *parent):
    Widget (parent), m_tex(tex)
{
    m_size = tex.size();
}

void Button::draw(SDL_Surface* srf)
{
    m_tex.draw(srf, m_pos, m_size);
}

void Button::onClick(std::function<void(int)> cb)
{
    on_click = cb;
}
