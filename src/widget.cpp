#include "widget.h"

Widget::Widget(Widget *parent) : m_parent(parent)
{
}

void Widget::setPos(Vec2i pos)
{
    if (m_parent)
    {
        m_pos = m_parent->pos() + pos;
    }
    else
    {
        m_pos = pos;
    }
}
SDL_Rect Widget::toSDLRect()
{
    SDL_Rect r = {m_pos.x, m_pos.y, m_size.x, m_size.y};
    return r;
}
