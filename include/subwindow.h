#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <string>

#include "uicollection.h"
#include "surface.h"

class SubWindow
{
  public:
    SubWindow(std::string left_txt, std::string right_txt, std::string msg, Surface *surf, SDL_Window *win);

    int show();

  private:
    UICollection m_win_ui;
    Surface *m_src;
    SDL_Window *m_win;
};

#endif