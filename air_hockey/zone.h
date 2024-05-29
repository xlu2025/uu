#ifndef ZONE_H
#define ZONE_H

#include <vector>
#include "obstacle.h"
#define ZONE_WIDTH 40
#define ZONE_HEIGHT 20
class Zone {
public:
    Zone(int goalWidth);
    void initialize();
    void draw();
    void addObstacle(int x, int y);
    std::vector<Obstacle>& getObstacles();

private:
    int goalWidth;
    std::vector<Obstacle> obstacles;
};

#endif
