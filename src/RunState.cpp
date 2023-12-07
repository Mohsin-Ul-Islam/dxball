#include "dxball/RunState.h"

#include <SFML/Audio.hpp>
#include <deque>

#include "dxball/Ball.h"
#include "dxball/Brick.h"
#include "dxball/Consumable.h"
#include "dxball/GameState.h"
#include "dxball/Platform.h"

RunState::RunState() { this->init(); }

RunState::RunState(std::string ffp, std::string bsf, std::string psf)
    : fontFilePath(ffp), brickSoundFilePath(bsf), platformSoundFilePath(psf) {
  this->init();
}

void RunState::pause() { this->isPaused = true; }

void RunState::unpause() { this->isPaused = false; }

void RunState::render(sf::RenderWindow &window) {
  for (int i = 0; i < this->bricks.size(); i++) {
    this->bricks[i].render(window);
  }

  for (int i = 0; i < drops.size(); i++) {
    drops.at(i).render(window);
  }

  this->platform.render(window);
  this->ball.render(window);
}

void RunState::tick(const float &deltaTime) {
  if (this->isPaused) {
    this->ball.self()->setPosition(Mouse::getPosition().x,
                                   this->ball.self()->getPosition().y);
    return;
  }

  this->ball.move();
  for (int i = 0; i < this->drops.size(); i++) {
    drops.at(i).move();
  }

  this->platform.platform.setPosition(Mouse::getPosition().x,
                                      platform.platform.getPosition().y);

  if (this->ball.self()->getPosition().x - this->ball.self()->getRadius() <=
      0) {
    this->ball.setHorizontalVelocity(-this->ball.getHorizontalVelocity());
  }

  if (this->ball.self()->getPosition().x + this->ball.self()->getRadius() >=
      this->screenWidth) {
    this->ball.setHorizontalVelocity(-this->ball.getHorizontalVelocity());
  }

  if (this->ball.self()->getPosition().y - this->ball.self()->getRadius() <=
      0) {
    this->ball.setVerticalVelocity(-this->ball.getVerticalVelocity());
  }

  if (this->ball.self()->getPosition().y >=
          this->screenHeight + (this->ball.self()->getRadius() * 2) ||
      bricks.size() <= 0) {
    this->pause();
  }

  float ratio = this->ball.getCollisionAngle(this->platform.platform);
  if (ratio != 0) {
    this->platformSound.play();
    this->ball.setHorizontalVelocity((ratio) *
                                     this->ball.getVerticalVelocity());
    this->ball.setVerticalVelocity(-this->ball.getVerticalVelocity());
  }

  for (int i = 0; i < bricks.size(); i++) {
    float ratio = this->ball.getCollisionAngle(*bricks[i].self());
    if (ratio != 0) {
      this->ball.setHorizontalVelocity((-ratio) *
                                       this->ball.getVerticalVelocity());
      this->ball.setVerticalVelocity(-this->ball.getVerticalVelocity());
      this->brickSound.play();
      if (bricks[i].getLifeCount() == 0) {
        if (rand() % 100 <= 40) {
          drops.push_back(Consumable(13, Color(250, 250, 250), 8,
                                     bricks[i].self()->getPosition()));
          // log("drop");
        }
        bricks.erase(bricks.begin() + i);
        score += 1;
      } else {
        bricks[i].self()->setFillColor(
            Color(rand() % 255, rand() % 255, rand() % 255));
        bricks[i].setLifeCount(bricks[i].getLifeCount() - 1);
      }
    }
  }

  for (int i = 0; i < drops.size(); i++) {
    if (drops.at(i).isColliding(this->platform.platform)) {
      drops.erase(drops.begin() + i);
      this->platform.platform.setSize(
          Vector2f(this->platform.platform.getSize().x + 10,
                   this->platform.platform.getSize().y));
      this->platform.platform.setOrigin(
          this->platform.platform.getSize().x / 2,
          this->platform.platform.getSize().y / 2);
      score += 3;
    }
  }
}

void RunState::init() {
  this->score = 0;
  this->isPaused = false;

  sf::Font font;
  font.loadFromFile(this->fontFilePath);

  sf::SoundBuffer brickSoundBuffer;
  brickSoundBuffer.loadFromFile(this->brickSoundFilePath);

  sf::SoundBuffer platformSoundBuffer;
  platformSoundBuffer.loadFromFile(this->platformSoundFilePath);

  this->brickSound = sf::Sound(brickSoundBuffer);
  this->platformSound = sf::Sound(platformSoundBuffer);

  this->stats.setFont(font);
  this->stats.setFillColor(sf::Color::White);
  this->stats.setCharacterSize(24);

  this->ball = Ball(10, 15, Color::Blue);
  this->platform = Platform(160, 20, Color(223, 77, 2), 10);

  this->bricks.resize(80);

  int brickWidth = 80;
  int brickHeight = 40;
  int numBricksRow = this->screenWidth / brickWidth;

  for (int i = 0; i < this->bricks.size(); i++) {
    bricks[i].self()->setSize(Vector2f(brickWidth, brickHeight));
    bricks[i].self()->setFillColor(Color(255, rand() % 255, rand() % 255));
    bricks[i].self()->setOrigin(brickWidth / 2.0, brickHeight / 2.0);
    bricks[i].setLifeCount(0);

    int posx = i % numBricksRow;
    int posy = i / numBricksRow;

    bricks[i].self()->setPosition(
        Vector2f(posx * brickWidth, 100 + brickHeight + posy * brickHeight));
  }
}
