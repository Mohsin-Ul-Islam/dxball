#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Brick {
 private:
  int life_count;
  RectangleShape brick;

 public:
  Brick();
  Brick(float, float, Vector2f, Color);
  ~Brick();

  void render(RenderWindow& w);

  // getters
  inline int getLifeCount() const { return this->life_count; };
  inline RectangleShape* self() { return &this->brick; };

  // setters
  void setLifeCount(const int& lc);
};

#endif
