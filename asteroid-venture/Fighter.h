#pragma once

#include "Entity.h"
#include <ctime>

class Fighter : public Entity
{
protected:
    bool alive, invulnerable, flashing;
    int score, lives, active_lasers;
    time_t respawn_time, invulnerability_time, invulnerability_flash_time;
public:
    static const int MAX_LASERS = 4;
    static const int MAX_LIVES = 3;
    static const char GRAPHIC[];

    Fighter(const short, const short);
    ~Fighter();

    void think();

    void updatePos(const short, const short);
    void updateScore(const int);
    void updateLives(const int);
    void updateActiveLasers(const int);

    int getScore() const;
    int getLives() const;
    int getActiveLasers() const;
    const COORD& getPos();

    bool isAlive() const;
    bool isInvulnerable() const;

    void kill();
    void spawn();
};