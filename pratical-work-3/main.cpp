#include <iostream>
#include <cstdlib>
#include <array>
#include <vector>
#include "console_io.h"
#include "game.h"

int main() {
   console_io::init();

   auto game = initGame();

   while (not isGameOver(game)) {
      // Wait for a 200 ms, meaning the game runs at 5 FPS (frames per second)
      console_io::sleep(200);

      if (console_io::key_was_hit()) {
         changeSnakeDirection(game, console_io::get_char_key());
      }

      moveSnake(game);

      console_io::clear_screen();

      render(game);
   }

   std::cout << "\nGame over!\nScore: "
             << score(game) << std::endl;

   // Stop console from closing instantly
   std::cin.ignore();

   console_io::end();
}
