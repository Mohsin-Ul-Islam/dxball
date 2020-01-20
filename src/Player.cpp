#include "dxball/Player.h"

Player::Player(int w, int h,Color c = Color::White, int ms = 10)
{
  width = w;
  height = h;
  color  = c;
  movespeed = ms;
  position.x = 1920/2;
  position.y = 1080 - 80;

  player.setSize(Vector2f(width,height));
  player.setFillColor(color);
  player.setOrigin(width/2,height/2);
  player.setPosition(position);
}

Player::~Player()
{

}

void Player::moveRight()
{
  position.x += movespeed;
  player.setPosition(position);
}

void Player::moveLeft()
{
  position.x -= movespeed;
  player.setPosition(position);
}

void Player::render(RenderWindow& w)
{
  w.draw(player);
}
