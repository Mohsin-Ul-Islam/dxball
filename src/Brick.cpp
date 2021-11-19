#include "dxball/Brick.h"

Brick::Brick() {}

Brick::Brick(float width = 80, float height = 40,
             Vector2f position = Vector2f(0, 0), Color c = Color::Blue) {
  brick.setSize(Vector2f(width, height));
  brick.setPosition(position);
  brick.setOrigin(width / 2, height / 2);
  brick.setFillColor(Color::Blue);
}

Brick::~Brick() {}

void Brick::render(RenderWindow& w) { w.draw(brick); }

void Brick::setLifeCount(const int& lc) { this->life_count = lc; }
