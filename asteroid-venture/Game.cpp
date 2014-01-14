#include "Game.h"

Game::Game()
: console(new Console("Asteroid Venture", 100, 50)), in_menu(true), in_game(false), fire_held(false),
  spawn_time(0), high_score(0)
{
    // Check for a high score, read it in.
    std::ifstream file("high.score", std::ios::binary);
    while (file.is_open() && !file.eof() && file.good()) file.read(reinterpret_cast<char*>(&high_score), sizeof(int));
    file.close();
}
Game::~Game() {}

void Game::pushEntity(Entity *_entity, const bool _push_back)
{
    console->pushGraphic(_entity, _push_back);
    entities.push_back(_entity);
}
void Game::clearEntities()
{
    console->clearGraphics();
    entities.clear();
}
void Game::pushAsteroid()
{
    time_t new_spawn = clock(); // Spawning of said asteroids.
    if (new_spawn >= spawn_time) {
        spawn_time = new_spawn + rand() % 1000; + 250;
        for (int i = 0; i < rand() % 1 + 1; ++i) {
            pushEntity(new Asteroid(94, rand() % 40 + 5, -(rand() % 2 + 1)));
        }
    }
}

void Game::setupGame() // Set up new game.
{
    in_game = true;
    in_menu = false;

    pushEntity(player = new Fighter(0, 23));
    console->pushGraphic(score_text = new Text(0, 0, 0x0A));
    console->pushGraphic(new Text(42, 0, 0x0A, "Asteroid Venture"));
    console->pushGraphic(lives_text = new Text(92, 0, 0x0A));
    console->pushGraphic(debug = new Text(50, 49, 0x0D));


    char str1[64] = { '\0' };
    sprintf(str1, "High Score: %i", high_score);
    console->pushGraphic(new Text(0, 49, 0x0E, str1));

    srand(time(nullptr));
}
void Game::endGame() // Clean up after game and prepare end screen.
{
    const int score = player->getScore();
    clearEntities();

    const char *str1 = "You were smashed to bits by asteroids.";
    char str2[64] = { '\0' };
    sprintf(str2, "In the end, you scored %i.", score);

    console->pushGraphic(new Text(50 - strlen(str1) / 2, 24, 0x0C, str1));
    console->pushGraphic(new Text(50 - strlen(str2) / 2, 25, 0x0A, str2));

    if (score > high_score) { // If they've set a new score, tell them!
        high_score = score;
        std::ofstream file("high.score", std::ios::binary);
        file.write(reinterpret_cast<const char*>(&high_score), sizeof(int));
        file.close();
        const char *str3 = "Congratulations, you've set a new high score!";
        console->pushGraphic(new Text(50 - strlen(str3) / 2, 26, 0x0E, str3));
    }
    end_screen = true;
}
void Game::drawGame()
{
    const COORD &fighter_pos = player->getPos();
    if (player->isAlive()) { // Controls.
        if (console->keys[VK_UP] && fighter_pos.Y > 2) {
            player->updatePos(0, -1);
        }
        else if (console->keys[VK_DOWN] && fighter_pos.Y < 49 - 7) {
            player->updatePos(0, 1);
        }
        if (console->keys[VK_LEFT] && fighter_pos.X > 0) {
            player->updatePos(-1, 0);
        }
        else if (console->keys[VK_RIGHT] && fighter_pos.X < 100 - 8) {
            player->updatePos(1, 0);
        }
        if (console->keys[VK_CONTROL] && !fire_held && player->getActiveLasers() < Fighter::MAX_LASERS) { // Check if we can fire a laser.
            PlaySoundA("audio/pew.wav", NULL, SND_ASYNC | SND_NODEFAULT); // Do stuff if we can.
            fire_held = true;
            player->updateActiveLasers(1);
            pushEntity(new Laser(fighter_pos.X + 7, fighter_pos.Y + 3, 2));
        }
        else if (!console->keys[VK_CONTROL]) {
            fire_held = false; // If we're not holding control, we can shoot again.
        }
    }
    for (auto it = entities.begin(); it != entities.end(); ++it) { // Update every entity and erase those which want to be deleted.
        Entity *it_ptr = (*it);
        const bool in_screen = console->inScreen(*it_ptr);
        if (!in_screen || it_ptr->shouldDelete()) {
            switch (it_ptr->getType()) {
            case Entity::LASER:
                player->updateActiveLasers(-1); // If a laser goes offscreen, deduct an active laser.
                break;
            case Entity::ASTEROID:
                if (!in_screen) player->updateScore(-5);
                break;
            }

            // Delete entities marked for deletion.
            auto p_it = it; p_it--;
            console->eraseGraphic(it_ptr);
            delete it_ptr;
            entities.erase(it);
            it = p_it;
            continue;
        }
        const int it_type = it_ptr->getType();
        if (it_type == Entity::PICKUP) {
            reinterpret_cast<Pickup *>(it_ptr)->pickup(player);
        }
        else if (it_type == Entity::ASTEROID && player->isAlive() && !player->isInvulnerable() && it_ptr->inScreen(*player)) {
            it_ptr->setDelete(true);

            const COORD centre = player->getCentre();
            pushEntity(new Explosion(centre.X, centre.Y));

            if (player->getLives() <= 0) { // End the game is we've run out of lives.
                endGame();
                return;
            }
            player->kill();
        }
        else if (it_type == Entity::LASER) {
            for (auto it2 = entities.begin(); it2 != entities.end(); ++it2) {
                Entity *it2_ptr = (*it2);
                if (it2_ptr->shouldDelete()) continue;

                const int it2_type = it2_ptr->getType();
                if (it2_type == Entity::ASTEROID && it_ptr->inScreen(*it2_ptr)) {
                    it_ptr->kill();
                    it2_ptr->kill();

                    const COORD centre = it2_ptr->getCentre(); // Centre an explosion and play an exploding-like sound.

                    if ((rand() % 20 == 0)) {
                        pushEntity(new LifePickup(centre.X, centre.Y), false);
                    }

                    pushEntity(new Explosion(centre.X, centre.Y), false);

                    player->updateScore(10); // Update the score.
                }
            }
        }
        it_ptr->think();
    }
    
    pushAsteroid(); // Push some asteroids to the screen. Duh.

    // Updating of text.
    score_text->setText("Score: %i", player->getScore());
    lives_text->setText("Lives: %i", player->getLives());
    debug->setText("Active Lasers: %i", player->getActiveLasers());
}
void Game::drawEndScreen()
{
    if (console->keys[VK_RETURN]) { // On hitting enter, clear up and go to the menu.
        console->clearGraphics();
        end_screen = false;
        setupMenu();
        pressed_time = clock() + 250;
    }
}
void Game::drawMenu()
{
    time_t curtick = clock();
    if (curtick > pressed_time) {
        if (console->keys[VK_RETURN]) { // Menu selection.
            switch (menu_select) {
            case 0:;
                endMenu();
                return;
            case 1:
                exit(0);
                return;
            }
        }
        else if (console->keys[VK_UP]) {
            pressed_time = curtick + 250;
            PlaySoundA("audio/eee.wav", 0, SND_ASYNC | SND_NODEFAULT);
            menu_select = menu_select - 1 < 0 ? 1 : menu_select - 1;
        }
        else if (console->keys[VK_DOWN]) {
            pressed_time = curtick + 250;
            PlaySoundA("audio/eee.wav", 0, SND_ASYNC | SND_NODEFAULT);
            menu_select = menu_select + 1 > 1 ? 0 : menu_select + 1;
        }
    }
    switch (menu_select) {
        case 0:
            quit_text->setColour(0x02);
            new_game_text->setColour(0x0A);
            break;
        case 1:
            new_game_text->setColour(0x02);
            quit_text->setColour(0x0A);
            break;
    }
}
void Game::setupMenu() // Setting up of menu.
{
    in_menu = true; 
    in_game = false;
    menu_select = 0;
    const char *str1 = "Asteroid Ventures"; // Couldn't be arsed to count the number of characters.
    console->pushGraphic(new Text(50 - strlen(str1) / 2, 22, 0x0A, str1));
    console->pushGraphic(new_game_text = new Text(50 - 4, 24, 0x0A, "New Game"));
    console->pushGraphic(quit_text = new Text(50 - 4, 25, 0x02, "Quit Game"));
}
void Game::endMenu()
{
    clearEntities();
    setupGame();
}

void Game::run()
{
    setupMenu();
    while (true) { // Render the screen, then determine which screen we're on and draw appropriately.
        Sleep(30); // 30 fps!
        console->render();
        if (end_screen) {
            drawEndScreen();
        }
        else if (in_menu) {
            drawMenu();
        }
        else if (in_game) {
            drawGame();
        }
    }
}