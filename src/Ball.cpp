#include "dxball/Ball.h"

#include <iostream>

Ball::Ball(int r, int ms = 10, Color c = Color::Blue) {
  radius = r;
  color = c;
  position.x = 1920 / 2 - r;
  position.y = 1080 - 110;

  ms_y = -ms;
  ms_x = 0;

  ball.setRadius(radius);
  ball.setFillColor(color);
  ball.setPosition(position);
}

float Ball::getCollisionAngle(const RectangleShape &obstacle) {
  int xmax = obstacle.getPosition().x + obstacle.getSize().x / 2;
  int xmin = obstacle.getPosition().x - obstacle.getSize().x / 2;
  int ymax = obstacle.getPosition().y + obstacle.getSize().y / 2;
  int ymin = obstacle.getPosition().y - obstacle.getSize().y / 2;

  position = ball.getPosition();

  if ((position.x - radius < xmax || position.x + radius < xmax) &&
      (position.x + radius > xmin || position.x - radius > xmin) &&
      position.y + radius < ymax && position.y + radius > ymin) {
    return -((obstacle.getPosition().x - position.x) / obstacle.getSize().x +
             0.1);
  }
  return 0;
}

void Ball::render(RenderWindow &w) { w.draw(ball); }

void Ball::move() {
  position.x = ball.getPosition().x + ms_x;
  position.y = ball.getPosition().y + ms_y;

  ball.setPosition(position);
}

Ball::~Ball() {}

void Ball::setHorizontalVelocity(const int &v) { ms_x = v; }

void Ball::setVerticalVelocity(const int &v) { ms_y = v; }
