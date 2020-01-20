#include "dxball/Brick.h"

Brick::Brick()
{

}

void Brick::init()
{
  brick.setSize(Vector2f(width,height));
  brick.setPosition(position);
  brick.setOrigin(width/2,height/2);
  brick.setFillColor(color);
}

Brick::~Brick()
{

}

void Brick::render(RenderWindow& w)
{
  if(!destroy)
  {
    w.draw(brick);
  }
}
