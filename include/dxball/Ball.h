#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
  public:

    int radius;
    int ms_x;
    int ms_y;
    Color color;
    Vector2f position;
    CircleShape ball;

    Ball();
    Ball(int,int,Color);
    ~Ball();
    float isColliding(const RectangleShape& obstacle);
    void render(RenderWindow& w);
    void move();

};


#endif
