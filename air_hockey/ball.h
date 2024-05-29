#ifndef BALL_H
#define BALL_H

#include <vector>
#include "slider.h"
#include "zone.h"
#include "obstacle.h"

class Ball {
public:
    Ball(int goalWidth);
    void reset();
    bool update(Slider& player1, Slider& player2, std::vector<Obstacle>& obstacles);
    void draw();
    int getLastTouchedBy();

private:
    int x, y;
    int dx, dy;
    int goalWidth;
    int lastTouchedBy;
};

#endif
