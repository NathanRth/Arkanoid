#ifndef UI_COLLECTION_H
#define UI_COLLECTION_H

#include <map>
#include <string>
#include <vector>
#include <SDL.h>

#include "widget.h"

class UICollection
{
  public:
    UICollection();

    void add(std::string tag, Widget *elem, int z);
    Widget *getByTag(std::string tag);

    void draw(SDL_Surface *surf);

  private:
    std::map<std::string, Widget *> m_elems;
    std::map<int, std::vector<Widget *>> m_zindex;
};

#endif