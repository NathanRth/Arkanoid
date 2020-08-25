#include "uicollection.h"

UICollection::UICollection()
{
}

void UICollection::add(std::string tag, Widget *elem, int z)
{
    m_elems.emplace(std::pair<std::string, Widget *>(tag, elem));

    if (m_zindex.find(z) == m_zindex.end())
    {
        std::vector<Widget *> v;
        v.push_back(elem);
        m_zindex.emplace(std::pair<int, std::vector<Widget *>>(z, v));
    }
    else
    {
        m_zindex.at(z).push_back(elem);
    }
}

Widget *UICollection::getByTag(std::string tag)
{
    return m_elems.at(tag);
}

void UICollection::draw(SDL_Surface *surf)
{
    for (auto mit : m_zindex)
    {
        for (auto vit : mit.second)
        {
            vit->draw(surf);
        }
    }
}