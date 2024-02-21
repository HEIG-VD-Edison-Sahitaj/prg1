#include "console_io.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>

#ifdef _WIN32

#include <conio.h>

namespace console_io {

   void clear_screen() {
      system("cls");
   }

   char get_char_key() {
      return getch();
   }

   void init() {
      // nothing to do
   }

   void end() {
      // nothing to do
   }

   int key_was_hit() {
      return kbhit();
   }

   void sleep(int millis) {
      _sleep(millis);
   }
}
#else

#include <sys/types.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
namespace console_io {

   char get_char_key() {
      return static_cast<char>(getchar());
   }

   void change_mode(int dir) {
      static struct termios oldt, newt;

      if (dir == 1) {
         tcgetattr(STDIN_FILENO, &oldt);
         newt = oldt;
         newt.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
         tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      } else {
         tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      }
   }

   void init() { change_mode(1); }

   void end() { change_mode(0); }

   int key_was_hit() {
      struct timeval tv;
      fd_set rdfs;

      tv.tv_sec = 0;
      tv.tv_usec = 0;

      FD_ZERO(&rdfs);
      FD_SET (STDIN_FILENO, &rdfs);

      select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);

      return FD_ISSET(STDIN_FILENO, &rdfs);
   }

   void sleep(int millis) {
      usleep(static_cast<useconds_t>(millis * 1000));
   }

   void clear_screen() {
      system("clear");
   }
}
#endif