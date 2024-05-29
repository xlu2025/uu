#include <ncurses.h>
#include "obstacle.h"

Obstacle::Obstacle(int x, int y) : x(x), y(y) {}

int Obstacle::getX() {
    return x;
}

int Obstacle::getY() {
    return y;
}

void Obstacle::draw() {
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(4));
    mvprintw(y, x, "#");
    attron(COLOR_PAIR(4));
}
