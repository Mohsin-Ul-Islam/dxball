#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
 private:
  int radius;
  int ms_x;
  int ms_y;
  Color color;
  Vector2f position;
  CircleShape ball;

 public:
  Ball();
  Ball(int, int, Color);
  ~Ball();
  float isColliding(const RectangleShape &obstacle);
  void render(RenderWindow &w);
  void move();

  // setters
  void setHorizontalVelocity(const int &v);
  void setVerticalVelocity(const int &v);

  // getters
  inline CircleShape *self() { return &this->ball; };
  inline int getHorizontalVelocity() const { return this->ms_x; };
  inline int getVerticalVelocity() const { return this->ms_y; };
};

#endif
