/* ---------------------------
Labo        |   PRG1-L4 - Snake game
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   24.11.2023
Deadline    |   05.12.2023 (2359)
Goal        |   Header file to game.cpp
--------------------------- */

#ifndef L4_SNAKE_GAME_GAME_H
#define L4_SNAKE_GAME_GAME_H

#include <cstdlib>
#include <array>
#include <vector>

struct Coordinates{
    std::size_t x{};
    std::size_t y{};
};

struct Snake {
    std::pair<std::vector<Coordinates>, Coordinates> length = {{}, {}};
    char direction{};
};

struct Food{
    Coordinates coordinates{};
};

struct Game{
    Snake snake{};
    Food food{};
    int score{};
    bool gameOver{};
    static const size_t h = 14; // to change if you want a height different
    static const size_t l = 30; // to change if you want a length different
    std::array<std::array<char, l>, h> board{};
};

Game initGame();

bool isGameOver(Game& game);

void changeSnakeDirection (Game& game, char key);

void moveSnake(Game& game);

void render(Game& game);

int score(Game& game);


#endif //L4_SNAKE_GAME_GAME_H
