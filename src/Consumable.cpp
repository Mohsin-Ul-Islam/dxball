#include "dxball/Consumable.h"

Consumable::Consumable(int radius, Color color, int speed, Vector2f position) {
  m_speed = speed;
  drop.setRadius(radius);
  drop.setFillColor(color);
  drop.setPosition(position);
}

void Consumable::move() {
  drop.setPosition(drop.getPosition().x, drop.getPosition().y + m_speed);
}

Consumable::~Consumable() {}

void Consumable::render(RenderWindow& w) { w.draw(drop); }

bool Consumable::isColliding(const RectangleShape& obstacle) {
  int xmax = obstacle.getPosition().x + obstacle.getSize().x / 2;
  int xmin = obstacle.getPosition().x - obstacle.getSize().x / 2;
  int ymax = obstacle.getPosition().y + obstacle.getSize().y / 2;
  int ymin = obstacle.getPosition().y - obstacle.getSize().y / 2;

  int radius = drop.getRadius();
  if ((drop.getPosition().x - radius < xmax ||
       drop.getPosition().x + radius < xmax) &&
      (drop.getPosition().x + radius > xmin ||
       drop.getPosition().x - radius > xmin) &&
      drop.getPosition().y + radius < ymax &&
      drop.getPosition().y + radius > ymin) {
    return true;
  }
  return false;
}
