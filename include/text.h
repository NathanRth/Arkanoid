#ifndef TEXT_H
#define TEXT_H

#include "widget.h"
#include "texture.h"

class Text : public Widget
{
  public:
    Text(std::string content, Widget *parent = nullptr);

    void draw(SDL_Surface *srf) override;

    static void setAsciiTable(Atlas *table);
    static void setSizeOfChar(Vec2i s);

    void setText(const std::string &str);

  private:
    // atlas des caractères
    static Atlas *m_ascii_table;
    // taille d'un caractère sur l'atlas
    static Vec2i m_sizeOfChar;

    // text à afficher
    std::string m_content;
};

#endif