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
#include "NukePickup.h"
#include "InvulnerabilityPickup.h"
#include "RapidFirePickup.h"

#include <fstream>    // File I/O
#include <random>

class Game
{
private:
    Console *console;
    Text *score_text, *lives_text, *pause_text;
    //Text *debug;
    Fighter *player;

    std::list<Entity *> entities;

    bool in_menu, in_game, end_screen, help_screen, in_pause;
    bool fire_held;

    Text *new_game_text, *quit_text, *help_text;
    time_t spawn_time, pressed_time;

    const int MAX_MENU_OPTIONS = 3;
    int menu_select, high_score;

    std::mt19937 rng;

    int random(const int, const int);

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

    void setupHelp();
    void endHelp();
    void drawHelp();
public:
    Game();
    ~Game();

    void run();
};