#ifndef ATLAS_H
#define ATLAS_H

#include <SDL.h>
#include <string>

#define BG_TILE_SIZE 64
#define BRICK_SIZE_X 32
#define BRICK_SIZE_Y 16

class Atlas
{
  public:
    // construit l'atlas d'après un fichier de texture
    Atlas(std::string src_file);

    SDL_Surface *surface() { return atlas; }

    // défini la couleur transparente de l'atlas
    void setColorKey(Uint32 key);

  private:
    SDL_Surface *atlas;
};

#endif // ATLAS_H