#include <ncurses.h>
#include <cstdlib>
#include "zone.h"
#include "ball.h"

Ball::Ball(int goalWidth) : goalWidth(goalWidth) {
	reset();
}

void Ball::reset() {
	x = COLS / 2;
	y = LINES / 2;
	dx = (rand() % 2 == 0) ? 1 : -1;
	dy = (rand() % 2 == 0) ? 1 : -1;
	lastTouchedBy = 0;
}

bool Ball::update(Slider& player1, Slider& player2, std::vector<Obstacle>& obstacles) {

	x += dx;
	y += dy;

	if (x <= 0 || x >=COLS-1) dx = -dx;
	if (y <= 0 || y >= LINES - 1) dy = -dy;

	if (y == player1.getY() && x >= player1.getX() && x < player1.getX() + player1.getSize()) {
		dy = -dy;
	}
	if (y == player2.getY() && x >= player2.getX() && x < player2.getX() + player2.getSize()) {
		dy = -dy;
	}

	if (y == 0 && (x > (COLS - goalWidth) / 2 && x <(COLS + goalWidth) / 2)) {
		lastTouchedBy = 2;
		return true;
	}
	if (y == LINES - 1 && (x > (COLS - goalWidth) / 2 && x <(COLS + goalWidth) / 2)) {
		lastTouchedBy = 1;     
		return true;
	}

	for (auto& obs : obstacles) {
		if (x == obs.getX() && y == obs.getY()) {
			dx = -dx;
			dy = -dy;
		}
	}

	return false;
}

void Ball::draw() {
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvprintw(y, x, "O");
	attroff(COLOR_PAIR(3));
}

int Ball::getLastTouchedBy() {
	return lastTouchedBy;
}

