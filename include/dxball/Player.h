#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{

  public:

    int width;
    int height;
    int movespeed;
    Vector2f position;
    RectangleShape player;
    Color color;

    Player(int,int,Color,int);
    ~Player();
    void moveRight();
    void moveLeft();
    void render(RenderWindow& w);

};

#endif
