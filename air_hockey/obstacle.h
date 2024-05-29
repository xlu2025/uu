#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
public:
    Obstacle(int x, int y);
    int getX();
    int getY();
    void draw();

private:
    int x, y;
};

#endif
