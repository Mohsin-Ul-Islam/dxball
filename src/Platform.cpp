#include "dxball/Platform.h"

Platform::Platform(int w, int h, Color c = Color::White, int ms = 10) {
  width = w;
  height = h;
  color = c;
  movespeed = ms;
  position.x = 1920 / 2.0 - (w / 2.0);
  position.y = 1080 - 80;

  platform.setSize(Vector2f(width, height));
  platform.setFillColor(color);
  platform.setOrigin(width / 2.0, height / 2.0);
  platform.setPosition(position);
}

Platform::Platform() {}

Platform::~Platform() {}

void Platform::moveRight() {
  position = platform.getPosition();
  position.x += movespeed;
  platform.setPosition(position);
}

void Platform::moveLeft() {
  position = platform.getPosition();
  position.x -= movespeed;
  platform.setPosition(position);
}

void Platform::render(RenderWindow& w) { w.draw(platform); }
