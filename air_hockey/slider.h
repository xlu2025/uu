#ifndef SLIDER_H
#define SLIDER_H

class Slider {
public:
    Slider(int player, int size);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void draw();
    int getX() const;
    int getY() const;
    int getSize() const;

private:
    int player;
    int x, y;
    int size;
};

#endif
