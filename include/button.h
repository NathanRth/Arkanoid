#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "widget.h"
#include "texture.h"

class Button : public Widget
{
public:
    Button(Texture tex, Widget* parent = nullptr);

    // défini la fonction à lancer si le boutton est cliqué
    void onClick(std::function<void(int)> cb);
    // lance la fonction onClick
    void clicked(int val){on_click(val);}

    //dessine le bouton
    void draw(SDL_Surface* srf);

private:
    Texture m_tex;
    std::function<void(int)> on_click;
};

#endif // BUTTON_H
