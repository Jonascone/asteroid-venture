#pragma once

// Render types
#include "Console.h"
#include "Text.h"

// Game types
#include "Fighter.h"
#include "Asteroid.h"
#include "Laser.h"
#include "Explosion.h"
#include "LifePickup.h"

#include <fstream>    // File I/O

class Game
{
private:
    Console *console;
    Text *score_text, *lives_text;
    Text *debug;
    Fighter *player;

    std::list<Entity *> entities;

    bool in_menu, in_game, end_screen;
    bool fire_held;

    Text *new_game_text, *quit_text;
    time_t spawn_time, pressed_time;

    int menu_select, high_score;

    void pushEntity(Entity *, const bool = true);
    void pushAsteroid();
    void clearEntities();

    void setupGame();
    void endGame();
    void drawGame();

    void setupMenu();
    void endMenu();
    void drawMenu();

    void drawEndScreen();

public:
    Game();
    ~Game();

    void run();
};