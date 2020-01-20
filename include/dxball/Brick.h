#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Brick
{
  public:

    int width;
    int height;
    int life_count;
    Vector2f position;
    RectangleShape brick;
    Color color;
    bool destroy;

    Brick();
    ~Brick();
    void init();
    void render(RenderWindow& w);

};

#endif
