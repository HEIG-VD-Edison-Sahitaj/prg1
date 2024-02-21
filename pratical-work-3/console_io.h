#ifndef SNAKE_CONSOLE_IO_H
#define SNAKE_CONSOLE_IO_H

namespace console_io {

   void init();

   void end();

   void clear_screen();

   char get_char_key();

   int key_was_hit();

   void sleep(int millis);
}

#endif //SNAKE_CONSOLE_IO_H
