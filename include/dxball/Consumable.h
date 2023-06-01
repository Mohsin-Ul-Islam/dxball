#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Consumable {
 public:
  int m_speed;
  CircleShape drop;

  Consumable(int radius, Color color, int speed, Vector2f position);
  void move();
  ~Consumable();
  void render(RenderWindow& w);
  bool isColliding(const RectangleShape& obstacle);
};

#endif
