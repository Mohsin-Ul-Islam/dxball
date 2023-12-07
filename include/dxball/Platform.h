#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Platform {
 public:
  int width;
  int height;
  int movespeed;
  Vector2f position;
  RectangleShape platform;
  Color color;

  Platform();
  Platform(int, int, Color, int);
  ~Platform();
  void moveRight();
  void moveLeft();
  void render(RenderWindow& w);
};

#endif
