#include "game.h"

#include <dirent.h>
#include <sstream>
#include <iostream>
#include <fstream>

#include "subwindow.h"
#include "button.h"

#define PI 3.14159265

Game::Game(std::string folder, std::string spriteAtlas, std::string textAtlas) : m_spriteAtlas(spriteAtlas), m_asciiTable(textAtlas)
{
    m_spriteAtlas.setColorKey(0);
    m_asciiTable.setColorKey(0);

    // Création de la fenêtre
    m_window = SDL_CreateWindow("Arkanoïd",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                13 * 32, 600,
                                SDL_WINDOW_SHOWN);

    // création de la surface de la fenêtre
    m_win_surf = new Surface(SDL_GetWindowSurface(m_window));

    // création de la surface qui affiche le fond
    m_background_surf = new Surface(m_win_surf->size().x, m_win_surf->size().y);
    m_background_surf->setPos({0, 64});
    // on utilise l'acceleration RLE pour la le fond (on ne dessine pas dessus)
    m_background_surf->optimize(true);

    // création de la surface du jeu
    m_game_surf = new Surface(m_win_surf->size().x, m_win_surf->size().y - 64);
    m_game_surf->setPos({0, 64});

    /******* PARSING DE NIVEAUX ******/

    m_level = NULL;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(folder.c_str())) != NULL)
    {
        int lvlIndex = 1;
        // pour chaque fichier dans le dossier
        while ((ent = readdir(dir)) != NULL)
        {

            Level *lvl;
            Level *current;
            std::cout << "opening: " << ent->d_name << std::endl;

            // si le nom contient 'Level'
            if (std::string(ent->d_name).find("Level") != std::string::npos)
            {
                std::cout << "found!" << '\n';

                // on parse le fichier
                lvl = parseFile(folder + std::string(ent->d_name), lvlIndex);

                // si le parsing est correct
                if (lvl)
                {
                    std::cout << "valid file" << std::endl;
                    lvlIndex++;
                    // si c'est le premier niveau de la liste
                    if (m_level == NULL)
                    {
                        m_level = lvl;
                        m_current_level = m_level;
                    }
                    else
                    {
                        m_current_level->next = lvl;
                        m_current_level = m_current_level->next;
                    }
                    std::cout << "level number" << lvl->levelIndex << std::endl;
                }
            }
            std::cout << std::endl;
        }
        // fermeture du dossier
        closedir(dir);
    }
    else
    {
        std::cout << "could not open dir" << std::endl;
        perror("opendir");
        /* could not open directory */
    }

    Text::setAsciiTable(&m_asciiTable);
    Text::setSizeOfChar({22, 30});

    Text *pscore = new Text("Score: 0");
    Text *plives = new Text("x 3");
    plives->setPos({330, 20});

    m_gameui.add("pscore", pscore, 1);
    m_gameui.add("plives", plives, 1);

    m_vaus = new Vaus(8, Texture(m_spriteAtlas, {384, 176}, {92, 16}), {m_game_surf->size().x - 100, 5}, {92, 16});
    m_balls.push_back(new Ball(Texture(m_spriteAtlas, {49, 67}, {14, 10}), {0, 0}, {14, 10}));
    m_players.push_back(Player(0, 1, 3, false, true, false, false, false));

    resetPosition();
}

Game::~Game()
{
    SDL_DestroyWindow(m_window);
    delete m_vaus;
}

bool Game::menu()
{
    SDL_Surface *logo_surf = SDL_LoadBMP("./Di-Anorak.bmp");
    if (logo_surf == NULL)
    {
        std::cerr << __FUNCTION__
                  << SDL_GetError() << std::endl;
    }
    Surface logo(logo_surf);
    logo.setPos({20,50});
    m_players.at(0).setLifes(3);
    m_current_level = m_level;
    bool clicked = false;
    bool ret;

    std::vector<Button *> buttons;
    std::vector<Text *> texts;

    Button *start_bt = new Button(Texture(m_spriteAtlas, {400, 400}, {100, 50}));
    start_bt->onClick([&](int i) {
        ret = true;
    });
    start_bt->setPos({(m_win_surf->size().x / 2) - ((22 * 5) / 2), 200});

    Button *quit_bt = new Button(Texture(m_spriteAtlas, {400, 400}, {100, 50}));
    quit_bt->onClick([&](int i) {
        ret = false;
    });
    quit_bt->setPos({(m_win_surf->size().x / 2) - ((22 * 4) / 2), 300});

    buttons.push_back(start_bt);
    buttons.push_back(quit_bt);

    Text *start_txt = new Text("START", start_bt);
    Text *quit_txt = new Text("QUIT", quit_bt);

    texts.push_back(start_txt);
    texts.push_back(quit_txt);

    SDL_Event event;
    while (!clicked)
    {
        while (!clicked && SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                int mx, my;
                for (auto b : buttons)
                {
                    SDL_GetMouseState(&mx, &my);
                    SDL_Rect r = b->toSDLRect();
                    if (mx >= r.x && mx <= r.x + r.w && my >= r.y && my <= r.y + r.h)
                    {
                        std::cout << "clicked" << std::endl;
                        b->clicked(0);
                        clicked = true;
                    }
                }
                break;
            case SDL_QUIT:
                clicked = true;
                ret = false;
            default:
                break;
            }
        }

        SDL_UpdateWindowSurface(m_window);

        m_win_surf->refresh();
        logo.draw(m_win_surf->toSDLSurface_ptr());
        for (auto b : buttons)
            b->draw(m_win_surf->toSDLSurface_ptr());
        for (auto t : texts)
            t->draw(m_win_surf->toSDLSurface_ptr());
    }
    return ret;
}

Code Game::gameLoop()
{

    SubWindow subwin_pause("Continue", "Menu", "Game paused...", m_win_surf, m_window);
    SubWindow subwin_next("Next", "Exit", "Go to next level", m_win_surf, m_window);
    SubWindow subwin_lose("Menu", "Exit", "You lose...", m_win_surf, m_window);
    SubWindow subwin_win("Menu", "Exit", "You win!!!", m_win_surf, m_window);

    Code quit = CONTINUE;
    SDL_Event event;

    m_nbIndestructableBricks = 0;
    bool m_firstLaunch = true;

    for (auto it = m_current_level->bricks.begin(); it != m_current_level->bricks.end(); it++)
    {
        if ((*it)->getBrickType() == 14)
            m_nbIndestructableBricks++;
    }

    genBackgroundSurface();
    resetPosition();

    while (quit == CONTINUE)
    {
        if (m_current_level == NULL) // si erreur de pointeur sur le niveau
        {
            std::cout << "null!" << std::endl;
            quit = EXIT;
        }
        if (m_current_level->bricks.size() - m_nbIndestructableBricks == 0) // si toutes les bricks ont été détruites
        {
            if (m_current_level->next) // s'il existe un niveau suivant, on y va
            {
                // on change de scene
                if (subwin_next.show())
                    quit = EXIT; // quit
                else
                {
                    nextLevel();
                    m_firstLaunch=true;
                }
            }
            else // sinon le joueur a gagné
            {
                if (subwin_win.show())
                    quit = EXIT; // quit
                else
                    quit = MENU; // retour au menu
            }
        }
        if (m_players.at(0).lifes() == 0) // si le joueur n'a plus de vie
        {
            if (subwin_lose.show())
                quit = EXIT; // quit
            else
                quit = MENU; // retour au menu
        }

        /***** INPUTS *****/

        while (quit == CONTINUE && SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = EXIT;
                break;
            case SDL_KEYDOWN: //si une touche de clavier est enfoncée
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT: //right arrow
                    if (m_vaus->direction() == 0)
                        m_vaus->setDirection(1);
                    break;
                case SDLK_LEFT: //left arrow
                    if (m_vaus->direction() == 0)
                        m_vaus->setDirection(-1);
                    break;
                    break;
                case SDLK_p:
                    if (subwin_pause.show())
                        quit = MENU;
                    break;
                case SDLK_n:
                    // on change de scene
                    if (subwin_next.show())
                        quit = EXIT; // quit
                    else
                    {
                        nextLevel();
                        m_firstLaunch=true;
                    }
                    break;
                case SDLK_SPACE:
                    if (m_players.at(0).magnet() == true && m_balls.at(0)->force().x == 0.0 && m_balls.at(0)->force().y == 0.0)
                    {
                        float coeff = ((m_balls.at(0)->pos().x + m_balls.at(0)->size().x / 2) - (m_vaus->pos().x + m_vaus->size().x / 2)) * (64.0 / (m_vaus->size().x / 2)); //coeff de distance entre le centre du m_vaus et la balle
                        float cosinus = cos(coeff * PI / 180.0);                                                                                                             //cosinus de ce coeff en degré
                        float sinus = sin(coeff * PI / 180.0);

                        m_balls.at(0)->setSpeed(m_balls.at(0)->speed() * 1.01);

                        m_balls.at(0)->setForce({sinus * m_balls.at(0)->speed(), -cosinus * m_balls.at(0)->speed()}); //on accélère la balle

                        if (m_firstLaunch)
                        {
                            m_players.at(0).setMagnet(false);
                            m_firstLaunch = false;
                        }
                    }
                    else if(m_players.at(0).laser() == true)
                    {
                        m_lasers.push_back(new Laser(m_vaus->pos(),m_spriteAtlas,{(float)m_vaus->pos().x,(float)m_vaus->pos().y}));
                        m_lasers.push_back(new Laser({m_vaus->pos().x+m_vaus->size().x-12,m_vaus->pos().y+m_vaus->size().y},m_spriteAtlas,{(float)(m_vaus->pos().x+m_vaus->size().x-12),(float)m_vaus->pos().y}));
                    }
                    break;
                }
                break;
            case SDL_KEYUP: //si une touche de clavier est relachée
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT: //right arrow
                    if (m_vaus->direction() == 1)
                        m_vaus->setDirection(0);
                    break;
                case SDLK_LEFT: //left arrow
                    if (m_vaus->direction() == -1)
                        m_vaus->setDirection(0);
                    break;
                }
                break;

            default:
                break;
            }
        }

        /***** MOUVEMENTS *****/

        // Vaus
        if (m_vaus->direction() != 0)
        {
            float diff = m_vaus->moveVaus(m_game_surf->toSDLSurface_ptr());
            if (m_players.at(0).magnet() == true && m_balls.at(0)->force().x == 0.0 && m_balls.at(0)->force().y == 0.0)
            {
                Vec2f move = {diff, 0.0};
                Vec2f f = m_balls.at(0)->fpos().operator+(move);
                m_balls.at(0)->setFpos(f);
                int x = (int)f.x;
                int y = (int)f.y;
                m_balls.at(0)->setPos({x, y});
            }
        }

        for(auto ball = m_balls.begin() ; ball != m_balls.end(); ball++)
        {
            if ((*ball)->doesMove() == true)
            {
                if((*ball)->moveBall(m_game_surf->toSDLSurface_ptr(), *m_vaus,m_current_level->cylindrical,&m_players.at(0))==false)   //on bouge la balle, si elle touche la bas, le joueur a perdu une vie et on reset les positions
                {
                    if(m_balls.size()==1)
                    {
                        resetPosition();
                        m_firstLaunch=true;
                    }
                    else
                    {
                        
                        m_balls.erase(ball);
                        if(m_balls.at(0)!=(*ball))
                            ball--;
                        if(m_balls.size()==1)
                            m_players.at(0).setDivide(false);
                    }
                }
                Vec2i collisionPos = (*ball)->checkCollision(m_current_level->bricks,&m_players.at(0),m_current_level->levelIndex);
                if (collisionPos.x != -1 && collisionPos.y != -1)
                {
                    spawnBonus(collisionPos);
                }
            }
        }

        // Bonus
        for (auto bonus = m_bonuses.begin(); bonus != m_bonuses.end(); bonus++)
        {
            int bonusIndex = (*bonus)->move(m_game_surf->toSDLSurface_ptr(), *m_vaus);
            if (bonusIndex != -1)
            {
                if (bonusIndex < 5)
                {
                    setBonus(bonusIndex, &m_players.at(0));
                }
                else if (bonusIndex == 5)
                {
                    if (subwin_next.show())
                        quit = EXIT;
                    else
                        nextLevel();
                    break;
                }
                else if (bonusIndex == 6)
                {
                    m_players.at(0).setLifes(m_players.at(0).lifes() + 1);
                    setBonus(-1, &m_players.at(0));
                }
                m_bonuses.erase(bonus);
                bonus--;
            }
        }


        // Laser
        for (auto laser = m_lasers.begin(); laser != m_lasers.end(); laser++)
        {
            (*laser)->move(m_game_surf->toSDLSurface_ptr(), *m_vaus);
            Vec2i collisionPos = (*laser)->checkCollision(m_current_level->bricks,&m_players.at(0),m_current_level->levelIndex,m_balls.at(0));
            if (collisionPos.x != -1 && collisionPos.y != -1)
            {
                m_lasers.erase(laser);
                laser--;
                if (collisionPos.x > -1 && collisionPos.y > -1)
                {
                    spawnBonus(collisionPos);
                }
            }
        }


        // mise à jour du text
        dynamic_cast<Text *>(m_gameui.getByTag("pscore"))->setText("Score: " + std::to_string(m_players.at(0).score()));
        dynamic_cast<Text *>(m_gameui.getByTag("plives"))->setText("x " + std::to_string(m_players.at(0).lifes()));

        // rendu de la scène
        render();
    }
    return quit;
}

void Game::setBonus(int bonusIndex, Player *player)
{
    player->setSlow(false);
    player->setMagnet(false);
    player->setLaser(false);
    if (bonusIndex != 3 && player->expand() == true)
    {
        player->setExpand(false);
        m_vaus = new Vaus(8, Texture(m_spriteAtlas, {384, 176}, {92, 16}), {m_vaus->pos().x + 18, m_vaus->pos().y}, {92, 16});
    }
    player->setDivide(false);

    switch (bonusIndex)
    {
        case 0:
            player->setSlow(true);
            break;
        case 1:
            player->setMagnet(true);
            break;
        case 2:
            player->setLaser(true);
            break;
        case 3:
            {
                if(player->expand()==false)
                    m_vaus = new Vaus(8, Texture(m_spriteAtlas, {384, 240}, {128, 16}), {m_vaus->pos().x-18, m_vaus->pos().y}, {128, 16});
                player->setExpand(true);
                break;
            }
        case 4:
            {
                player->setDivide(true);
                float cosinus120 = cos(120 * PI / 180.0);
                float cosinus240 = cos(240 * PI / 180.0);
                float sinus120 = sin(120 * PI / 180.0);
                float sinus240 = sin(240 * PI / 180.0);
                m_balls.push_back(new Ball(Texture(m_spriteAtlas, {49, 67}, {14, 10}), m_balls.at(0)->pos(), {14, 10},true,true,{sinus120,-cosinus120},m_balls.at(0)->fpos(),m_balls.at(0)->speed()));
                m_balls.push_back(new Ball(Texture(m_spriteAtlas, {49, 67}, {14, 10}), m_balls.at(0)->pos(), {14, 10},true,true,{sinus240,-cosinus240},m_balls.at(0)->fpos(),m_balls.at(0)->speed()));
                break;
            }
        default:
            break;
    }
}

void Game::render()
{
    mtime_t t = getMTime();

    // SDL update
    SDL_UpdateWindowSurface(m_window);
    m_win_surf->refresh();
    m_game_surf->refresh();

    // on déssine la surface du bg sur la fenêtre
    m_background_surf->draw(m_win_surf->toSDLSurface_ptr());

    // dessine des bricks
    for (auto b : m_current_level->bricks)
    {
        b->draw(m_game_surf->toSDLSurface_ptr(), t);
    }

    // dessine l'ui
    m_gameui.draw(m_win_surf->toSDLSurface_ptr());
    // dessine l'icone vaus pour les vies
    Texture(m_spriteAtlas, {384, 176}, {92, 16}).draw(m_win_surf->toSDLSurface_ptr(), {m_game_surf->size().x - 100, 5}, {92, 16});

    // dessine le vaisseau
    m_vaus->draw(m_game_surf->toSDLSurface_ptr());

    // dessine les balls
    for (auto ball : m_balls)
    {
        ball->draw(m_game_surf->toSDLSurface_ptr());
    }

    // dessine les bonus
    for (auto bonus : m_bonuses)
    {
        bonus->draw(m_game_surf->toSDLSurface_ptr(), t);
    }

    // dessine les lasers
    for (auto laser : m_lasers)
    {
        laser->draw(m_game_surf->toSDLSurface_ptr(), t);
    }

    // dessine la surface de jeu sur la fenêtre
    m_game_surf->draw(m_win_surf->toSDLSurface_ptr());
}

void Game::genBackgroundSurface()
{
    int tex_x = 64 + m_current_level->background * 64;
    int tex_y = 128 + 64;

    for (int y = 0; y < m_game_surf->size().y; y += BG_TILE_SIZE)
    {
        for (int x = 0; x < m_game_surf->size().x; x += BG_TILE_SIZE)
        {
            // dessine le patch de texture correspondant de l'atlas dans la surface du bg
            Texture(m_spriteAtlas, {tex_x, tex_y}, {BG_TILE_SIZE, BG_TILE_SIZE}).draw(m_background_surf->toSDLSurface_ptr(), {x, y}, {BG_TILE_SIZE, BG_TILE_SIZE});
        }
    }
}

void Game::resetPosition()
{
    m_vaus->setPos({((m_game_surf->size().x) / 2) - 46, m_game_surf->size().y - 50});
    m_vaus->Object::setSize({92, 16});

    m_balls.clear();
    m_balls.push_back(new Ball(Texture(m_spriteAtlas, {49, 67}, {14, 10}), {0, 0}, {14, 10}));

    m_balls.at(0)->setPos({(m_vaus->pos().x+m_vaus->size().x/2)+10, m_game_surf->size().y - 60});
    m_balls.at(0)->setFpos({(float)((m_vaus->pos().x+m_vaus->size().x/2)+10), (float)m_game_surf->size().y - 60});
    m_balls.at(0)->setSize({14, 10});
    m_balls.at(0)->setMove(true);
    m_balls.at(0)->setCollider(false);
    m_balls.at(0)->setForce({0.0, 0.0});
    m_balls.at(0)->setSpeed(0.5);

    setBonus(1, &m_players.at(0));

    m_bonuses.clear();
    m_lasers.clear();
    m_firstLaunch=true;

}

void Game::nextLevel()
{
    resetPosition();
    m_current_level = m_current_level->next;
    m_nbIndestructableBricks = 0;
    m_firstLaunch = true;
    for (auto it = m_current_level->bricks.begin(); it != m_current_level->bricks.end(); it++)
    {
        if ((*it)->getBrickType() == 14)
            m_nbIndestructableBricks++;
    }
    genBackgroundSurface();
}

void Game::spawnBonus(Vec2i pos)
{
    float r = ((double) rand() / (RAND_MAX));
    if(r<=0.9)     //15% de chance de faire apparaitre un bonus
    {
        float x = (float)pos.x;
        float y = (float)pos.y;

        int rBonus = ((double) rand() / (RAND_MAX))*7;
        m_bonuses.push_back(new Bonus(pos,rBonus,m_spriteAtlas,{x,y}));
    }
}

Level *Game::parseFile(const std::string &filename, int lvlIndex)
{

    Level *lvl = new Level;

    lvl->levelIndex = lvlIndex;

    std::cout << "filename: " << filename << std::endl;
    std::ifstream file(filename);
    std::string line;

    int numLine = 0;
    int a, b;
    int i = 0;
    while (std::getline(file, line) && numLine < 28)
    {
        std::istringstream iss(line);
        //std::cout << "line: " << line << std::endl;
        switch (numLine)
        {
        case 0: // game size
            if (iss >> a >> b)
            {
                lvl->gameSize = Vec2i(a, b);
            }
            else
            {
                // throw error
                return NULL;
            }
            break;
        case 1:
            if (iss >> a)
            {
                lvl->cylindrical = static_cast<bool>(a);
            }
            else
            {
                // throw error
                return NULL;
            }
            break;
        case 2:
            if (iss >> a)
            {
                lvl->background = a;
            }
            else
            {
                // throw error
                return NULL;
            }
            break;
        default:
            while (iss >> a)
            {
                if (a != 0)
                {
                    Vec2i pos = {((i % lvl->gameSize.x) * BRICK_SIZE_X) + (m_win_surf->size().x - lvl->gameSize.x * BRICK_SIZE_X) / 2, (i / lvl->gameSize.x) * BRICK_SIZE_Y};
                    if (a < 13 && a > 0) // static
                    {
                        lvl->bricks.push_back(new StaticBrick(pos, a, m_spriteAtlas, 0));
                    }
                    else if (a == 13 || a == 14) // animated
                    {
                        if (a == 14)
                            lvl->bricks.push_back(new AnimatedBrick(pos, a, m_spriteAtlas, -1));
                        else
                            lvl->bricks.push_back(new AnimatedBrick(pos, a, m_spriteAtlas, 2 + ((int)+((lvl->levelIndex - 1) / 8))));
                    }
                    else
                    {
                        // throw error
                        return NULL;
                    }
                }
                i++;
            }
        }
        numLine++;
    }

    std::cout << "recorded " << lvl->bricks.size() << " bricks" << std::endl;
    lvl->next = NULL;

    return lvl;
}