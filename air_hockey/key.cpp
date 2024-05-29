#include <ncurses.h>
#include <cstdlib>
#include "key.h"
#include "slider.h"

void processInput(int ch, Slider& player1, Slider& player2, bool& paused) {
    switch (ch) {
    case KEY_LEFT:
        player1.moveLeft();
        break;
    case KEY_RIGHT:
        player1.moveRight();
        break;
    case KEY_UP:
        player1.moveUp();
        break;
    case KEY_DOWN:
        player1.moveDown();
        break;
    case 'w':
        player2.moveUp();
        break;
    case 'a':
        player2.moveLeft();
        break;
    case 's':
        player2.moveDown();
        break;
    case 'd':
        player2.moveRight();
        break;
    case 'p':
    case 'P':
        paused = !paused;
        break;
    case 'q':
    case 'Q':
        endwin();
        exit(0);
    }
}
