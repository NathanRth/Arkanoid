#include "text.h"
#include <iostream>

Atlas *Text::m_ascii_table;
Vec2i Text::m_sizeOfChar;

Text::Text(std::string str, Widget *parent) : Widget(parent), m_content(str)
{
}

void Text::setAsciiTable(Atlas *atlas)
{
    m_ascii_table = atlas;
}

void Text::setSizeOfChar(Vec2i s)
{
    m_sizeOfChar = s;
}

void Text::draw(SDL_Surface *srf)
{
    Vec2i posOnAtlas = {0, 0};
    Texture charTex(*m_ascii_table, {0, 0}, m_sizeOfChar);
    Vec2i offset = {0, 0};
    charTex.draw(srf, m_pos, {32, 32});
    for (char c : m_content)
    {
        if (c >= 32 && c < 127)
        {
            char cc = c - 32;
            posOnAtlas.x = (cc % 16) * 32;
            posOnAtlas.y = (cc / 16) * 32;
            charTex.setPos(posOnAtlas);
            if (m_parent)
            {
                charTex.draw(srf, m_pos + offset + m_parent->pos(), m_sizeOfChar);
            }
            else
            {
                charTex.draw(srf, m_pos + offset, m_sizeOfChar);
            }
            offset.x += m_sizeOfChar.x;
        }
    }
}

void Text::setText(const std::string &str)
{
    m_content = str;
}