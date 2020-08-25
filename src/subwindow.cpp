#include "subwindow.h"

#include "surface.h"
#include "text.h"

SubWindow::SubWindow(std::string left, std::string right, std::string msg, Surface *surf, SDL_Window *window)
{
    m_src = surf;
    m_win = window;
    Surface *blur = new Surface(m_src->size().x, m_src->size().y, 0x11111111, nullptr);
    Surface *bg = new Surface(m_src->size().x, 128, 0xFFFF0000, nullptr);
    bg->setPos({0, 200});

    Surface *left_bt = new Surface(184, 50, 0xFFFFFF00, bg);
    left_bt->setPos({16, 50});

    Surface *right_bt = new Surface(184, 50, 0xFFFF00FF, bg);
    right_bt->setPos({216, 50});

    Text *left_txt = new Text(left, left_bt);
    Text *right_txt = new Text(right, right_bt);
    Text *msg_txt = new Text(msg, bg);

    m_win_ui.add("blur", blur, -1);
    m_win_ui.add("bg", bg, 0);
    m_win_ui.add("left_bt", left_bt, 1);
    m_win_ui.add("right_bt", right_bt, 1);
    m_win_ui.add("left_txt", left_txt, 2);
    m_win_ui.add("right_txt", right_txt, 2);
    m_win_ui.add("msg", msg_txt, 2);
}

int SubWindow::show()
{
    bool quit = false;
    int ret;
    SDL_Event event;

    Widget *btl = m_win_ui.getByTag("left_bt");
    SDL_Rect rbtl = btl->toSDLRect();
    Widget *btr = m_win_ui.getByTag("right_bt");
    SDL_Rect rbtr = btr->toSDLRect();

    while (!quit)
    {
        while (!quit && SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                int mx, my;
                SDL_GetMouseState(&mx, &my);

                if (mx >= rbtl.x && mx <= rbtl.x + rbtl.w && my >= rbtl.y && my <= rbtl.y + rbtl.h)
                {
                    quit = true;
                    ret = 0;
                }
                if (mx >= rbtr.x && mx <= rbtr.x + rbtr.w && my >= rbtr.y && my <= rbtr.y + rbtr.h)
                {
                    quit = true;
                    ret = 1;
                }
                break;
            default:
                break;
            }
        }

        SDL_UpdateWindowSurface(m_win);

        m_win_ui.draw(m_src->toSDLSurface_ptr());
    }
    return ret;
}