#include <ncurses.h>
#include "slider.h"

Slider::Slider(int player, int size) : player(player), size(size) {
    if (player == 1) {
        x = COLS / 2;
        y = LINES -2;
    }
    else {
        x = COLS / 2;
        y = 1;
    }
}

void Slider::moveLeft() {
    if (x > 1) x--;
}

void Slider::moveRight() {
    if (x < COLS - size - 1) x++;
}

void Slider::moveUp() {
    if (y > 1) y--;
}

void Slider::moveDown() {
    if (y < LINES - 2) y++;
}

void Slider::draw() {
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (int i = 0; i < size; ++i) {
        mvprintw(y, x + i, "=");
    } 
    attroff(COLOR_PAIR(1));
}

int Slider::getX() const {
    return x;
}

int Slider::getY() const {
    return y;
}

int Slider::getSize() const {
    return size;
}
