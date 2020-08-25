#ifndef GAME_H
#define GAME_H

#include <vector>
#include "sprite.h"
#include "vaus.h"
#include "player.h"
#include "staticbrick.h"
#include "animatedbrick.h"
#include "text.h"
#include "widget.h"
#include "level.h"
#include "ball.h"
#include "uicollection.h"
#include "surface.h"
#include "bonus.h"
#include "laser.h"

typedef enum {MENU, EXIT, CONTINUE} Code;

class Game
{
public:
    Game(std::string folder, std::string spriteAtlas, std::string textAtlas);
    ~ Game();
    
    bool menu();
    
    // main game loop
    Code gameLoop();

    //affecte les bonus en temps réel
    void setBonus(int bonusIndex,Player* player);

    // dessine le jeu
    void render();
    // remet à 0 les positions du vaus et de la balle
    void resetPosition();
    // lance le niveau suivant
    void nextLevel();

    void spawnBonus(Vec2i pos);


private:

    // génère la surface du bg
    void genBackgroundSurface();
    Level* parseFile(const std::string &path,int lvlIndex);

    int m_nbIndestructableBricks;
    bool m_firstLaunch;
    // les atlas pour le text et les sprites
    Atlas m_spriteAtlas;
    Atlas m_asciiTable;

    // premier niveau (debut de la liste chainée)
    Level *m_level;
    // niveau courant
    Level *m_current_level;
    
    //ball, vaus et player, bonus et laser balls du jeu
    Vaus *m_vaus;
    std::vector<Ball*> m_balls;
    std::vector<Player> m_players;
    std::vector<Bonus*> m_bonuses;
    std::vector<Laser*> m_lasers;

    // surfaces SDL
    SDL_Window* m_window;
    Surface* m_win_surf;
    Surface* m_game_surf;
    Surface* m_background_surf;

    UICollection m_gameui;
};

#endif