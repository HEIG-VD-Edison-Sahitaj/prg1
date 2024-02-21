/* ---------------------------
Labo        |   PRG1-L4 - Snake game
Author(s)   |   Agron Markaj - David Schildböck - Edison Sahitaj
Start date  |   24.11.2023
Deadline    |   05.12.2023 (2359)
Goal        |   File with the functions for the game
Note        |   The program may do some weird things in the terminal (all dark for a very shot time for example), but it's working
Source      |   For the random part -> https://stackoverflow.com/a/7560564
--------------------------- */

#include "game.h"
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

/* ---------------------------
Name        | randomCoordinates
Parameter(s)| Game& game - reference to the struct game
Return      | Coordinates
Goal        | Generate random coordinates for food, avoiding the current position of the snake and the board's edge.
--------------------------- */
Coordinates randomCoordinates(Game &game) {
    bool isUnique;
    Food food;
    random_device rd;
    do {
        mt19937 gen(rd());

        uniform_int_distribution<> dis(1, Game::l - 2);
        uniform_int_distribution<> dis2(1, Game::h - 2);
        food.coordinates.x = static_cast<size_t>(dis(gen));
        food.coordinates.y = static_cast<size_t>(dis2(gen));
        if (game.board[food.coordinates.y][food.coordinates.x] == ' ' or
            game.board[food.coordinates.y][food.coordinates.x] == '\000') {
            isUnique = true;
        }
    } while (!isUnique);

    return food.coordinates;
}

/* ---------------------------
Name        | foodEaten
Parameter(s)| Game& game - reference to the strcut game
Return      | bool
Goal        | Check if the snake has eaten food and perform corresponding actions (increase score, etc.).
--------------------------- */
bool foodEaten(Game &game) {
    if (game.snake.length.second.x == game.food.coordinates.x and
        game.snake.length.second.y == game.food.coordinates.y) {
        game.food.coordinates = randomCoordinates(game);
        game.score++;
        game.board[game.food.coordinates.y][game.food.coordinates.x] = '*';
        return true;
    }
    return false;

}

/* ---------------------------
Name        | changeSnakeDirection
Parameter(s)| Game& game - reference to the struct game, char key - key pressed to change direction
Return      | void
Goal        | Change the snake's direction based on the pressed key, avoiding complete reversal.
--------------------------- */
void changeSnakeDirection(Game &game, char key) {
    switch (key) {
        case 'w':
            if (game.snake.direction != 's') {
                game.snake.direction = key;
            }
            break;
        case 'd':
            if (game.snake.direction != 'a') {
                game.snake.direction = key;
            }
            break;
        case 's':
            if (game.snake.direction != 'w') {
                game.snake.direction = key;
            }
            break;
        case 'a':
            if (game.snake.direction != 'd') {
                game.snake.direction = key;
            }
            break;
        default:
            break; //instruction never reached in our code
    }
}

/* ---------------------------
Name        | moveSnake
Parameter(s)| Game& game - reference to the struct game
Return      | void
Goal        | Move the snake on the board based on its current direction.
--------------------------- */
void moveSnake(Game &game) {
    Coordinates tmpCoordinates;
    Coordinates oldCoordinates = game.snake.length.second;

    game.board[game.snake.length.first.back().y][game.snake.length.first.back().x] = ' '; // to remove the snake's trail

    for (Coordinates &coord: game.snake.length.first) {
        tmpCoordinates = coord;
        coord = oldCoordinates;
        oldCoordinates = tmpCoordinates;
    }

    if (foodEaten(game)) {
        game.snake.length.first.push_back(oldCoordinates);
    }

    switch (game.snake.direction) {
        case 'w':
            game.snake.length.second.y--;
            game.board[game.snake.length.second.y][game.snake.length.second.x] = '^';
            break;
        case 'd':
            game.snake.length.second.x++;
            game.board[game.snake.length.second.y][game.snake.length.second.x] = '>';
            break;
        case 's':
            game.snake.length.second.y++;
            game.board[game.snake.length.second.y][game.snake.length.second.x] = 'v';
            break;
        case 'a':
            game.snake.length.second.x--;
            game.board[game.snake.length.second.y][game.snake.length.second.x] = '<';
            break;
    }
}

/* ---------------------------
Name        | isGameOver
Parameter(s)| Game& game - reference to the struct game
Return      | bool
Goal        | Return the state of the game.
--------------------------- */
bool isGameOver(Game &game) {
    return game.gameOver;
}

/* ---------------------------
Name        | score
Parameter(s)| Game& game - reference to the struct game
Return      | int
Goal        | Return the score of the player.
--------------------------- */
int score(Game &game) {
    return game.score;
}

/* ---------------------------
Name        | render
Parameter(s)| Game& game - reference to the struct game
Return      | void
Goal        | Display the current state of the game board, including the snake, food, and borders.
--------------------------- */
void render(Game &game) {

    for (auto &i: game.snake.length.first) {
        game.board[i.y][i.x] = 'O';

        // Game over if snake is colliding with itself
        if (i.x == game.snake.length.second.x and i.y == game.snake.length.second.y) {
            game.board[game.snake.length.second.y][game.snake.length.second.x] = 'X';
            game.gameOver = true;
        }
    }

    // Game over if snake is colliding with the board's edge
    if (game.snake.length.second.x == 0 or game.snake.length.second.x == Game::l - 1 or
        game.snake.length.second.y == 0 or game.snake.length.second.y == Game::h - 1) {
        game.board[game.snake.length.second.y][game.snake.length.second.x] = 'X';
        for (auto &i: game.snake.length.first) {
            game.board[i.y][i.x] = ' ';
        }
        game.gameOver = true;
    }

    for (auto &i: game.board) {
        for (size_t j = 0; j < Game::l; j++) {
            cout << i[j];
        }
        cout << endl;
    }
}

/* ---------------------------
Name        | initBoard
Parameter(s)| Game& game - reference to the struct game
Return      | void
Goal        | Initialize the game board with dimensions specified in the struct game.
--------------------------- */
void initBoard(Game &game) {
    const char plus = '+';
    const char minus = '-';
    const char bar = '|';

    for (size_t i = 0; i < Game::h; i++) {
        for (size_t j = 0; j < Game::l; j++) {
            if (i == 0 || i == Game::h - 1) {
                if (j == 0 || j == Game::l - 1)
                    game.board[i][j] = plus;
                else
                    game.board[i][j] = minus;
            } else if (j == 0 || j == Game::l - 1)
                game.board[i][j] = bar;
            else
                game.board[i][j] = ' ';
        }
    }
}

/* ---------------------------
Name        | initSnake
Parameter(s)| none
Return      | Snake
Goal        | Initialize the snake at the center of the board with an initial direction and predefined length.
--------------------------- */
Snake initSnake() {
    Snake snake;
    Coordinates coordinates;
    auto centerL = static_cast<size_t>(ceil(Game::l / 2));
    auto centerH = static_cast<size_t>(ceil(Game::h / 2));
    coordinates.x = centerL;
    coordinates.y = centerH;
    snake.length.second = coordinates;
    coordinates.x--;
    snake.length.first.push_back(coordinates);
    coordinates.x--;
    snake.length.first.push_back(coordinates);
    snake.direction = 'd';
    return snake;
}

/* ---------------------------
Name        | initGame
Parameter(s)| none
Return      | Game
Goal        | Initialize and return a new struct game with all necessary components (snake, food, etc.).
--------------------------- */
Game initGame() {
    Game game;
    game.snake = initSnake();
    game.food.coordinates = randomCoordinates(game);
    game.score = 0;
    game.gameOver = false;
    initBoard(game);
    game.board[game.snake.length.second.y][game.snake.length.second.x] = '>';
    for (auto &i: game.snake.length.first) {
        game.board[i.y][i.x] = 'O';
    }
    game.board[game.food.coordinates.y][game.food.coordinates.x] = '*';
    for (auto &i: game.board) {
        for (size_t j = 0; j < Game::l; j++) {
            cout << i[j];
        }
        cout << endl;
    }
    return game;
}
