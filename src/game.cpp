#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "dxball/Ball.h"
#include "dxball/Brick.h"
#include "dxball/Consumable.h"
#include "dxball/Platform.h"

using namespace sf;

std::string toString(int val) {
  std::stringstream converter;
  converter << val;
  std::string res;
  converter >> res;
  return res;
}

std::string toString(float val) {
  std::stringstream converter;
  converter << std::setprecision(3) << val;
  std::string res;
  converter >> res;
  return res;
}

void log(const std::string& msg) { std::cout << "[-] " << msg << std::endl; }

int main(int argc, char** argv) {
  srand(time(0));

  int screen_width = 1920;
  int screen_height = 1080;
  int total_bricks = 80;

  Clock clock;
  Time time;
  float total_time = 0;
  float level_time = 0;
  int total_bounces = 0;
  SoundBuffer bsb;
  SoundBuffer psb;

  Font default_font;

  try {
    default_font.loadFromFile("./assets/fonts/Roboto-Regular.ttf");
    bsb.loadFromFile("./assets/sounds/glass.ogg");
    psb.loadFromFile("./assets/sounds/sonar.ogg");
  } catch (std::exception e) {
    log("cannot load resources.");
    return 1;
  }

  Sound brick_sound(bsb);
  Sound platform_sound(psb);

  Text stats;

  stats.setFont(default_font);
  stats.setFillColor(Color::White);
  stats.setCharacterSize(24);

  int score = 0;

  RenderWindow window(VideoMode(screen_width, screen_height), "DxBall",
                      Style::Fullscreen);
  window.setFramerateLimit(60);
  window.setMouseCursorVisible(false);

  bool started = false;
  Platform* platform = new Platform(160, 20, Color(223, 77, 2), 10);
  Ball* ball = new Ball(10, 15, Color::Blue);
  std::deque<Brick> bricks(total_bricks);
  std::deque<Consumable> drops;
  int brick_width = 80;
  int brick_height = 40;
  int num_bricks_row = screen_width / brick_width;
  for (int i = 0; i < bricks.size(); i++) {
    bricks[i].self()->setSize(Vector2f(brick_width, brick_height));
    bricks[i].self()->setFillColor(Color(255, rand() % 255, rand() % 255));
    bricks[i].self()->setOrigin(brick_width / 2, brick_height / 2);
    bricks[i].setLifeCount(0);
    // bricks[i].brick.setOrigin(Vector2f(brick_width/2,brick_height/2));
    int posx = i % num_bricks_row;
    int posy = i / num_bricks_row;
    bricks[i].self()->setPosition(
        Vector2f(posx * brick_width, 100 + brick_height + posy * brick_height));
  }

  while (window.isOpen()) {
    time = clock.restart();
    total_time += time.asSeconds();
    level_time += time.asSeconds();
    Event e;

    while (window.pollEvent(e)) {
      if (e.type == Event::Closed) {
        window.close();
      } else if (e.type == Event::MouseButtonPressed) {
        started = true;
      }
    }

    if (started) {
      ball->move();
    }

    for (int i = 0; i < drops.size(); i++) {
      drops.at(i).move();
    }

    platform->platform.setPosition(Mouse::getPosition().x,
                                   platform->platform.getPosition().y);

    if (!started) {
      ball->self()->setPosition(Mouse::getPosition().x,
                                ball->self()->getPosition().y);
    }

    if (ball->self()->getPosition().x - ball->self()->getRadius() <= 0) {
      ball->setHorizontalVelocity(-ball->getHorizontalVelocity());
    }

    if (ball->self()->getPosition().x + ball->self()->getRadius() >=
        screen_width) {
      ball->setHorizontalVelocity(-ball->getHorizontalVelocity());
    }

    if (ball->self()->getPosition().y - ball->self()->getRadius() <= 0) {
      ball->setVerticalVelocity(-ball->getVerticalVelocity());
    }

    if (ball->self()->getPosition().y >=
            screen_height + (ball->self()->getRadius() * 2) ||
        bricks.size() <= 0) {
      window.close();
    }

    float ratio = ball->getCollisionAngle(platform->platform);
    if (ratio != 0) {
      platform_sound.play();
      ball->setHorizontalVelocity((ratio)*ball->getVerticalVelocity());
      ball->setVerticalVelocity(-ball->getVerticalVelocity());
      total_bounces += 1;
    }

    for (int i = 0; i < bricks.size(); i++) {
      float ratio = ball->getCollisionAngle(*bricks[i].self());
      if (ratio != 0) {
        ball->setHorizontalVelocity((-ratio) * ball->getVerticalVelocity());
        ball->setVerticalVelocity(-ball->getVerticalVelocity());
        brick_sound.play();
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
      if (drops.at(i).isColliding(platform->platform)) {
        drops.erase(drops.begin() + i);
        platform->platform.setSize(Vector2f(platform->platform.getSize().x + 10,
                                            platform->platform.getSize().y));
        platform->platform.setOrigin(platform->platform.getSize().x / 2,
                                     platform->platform.getSize().y / 2);
        score += 3;
      }
    }
    stats.setString("Score: " + toString(score) +
                    " | Time: " + toString(total_time) +
                    " seconds | Bounces: " + toString(total_bounces));
    window.clear();
    for (int i = 0; i < bricks.size(); i++) {
      // log("rendering brick number " + toString(i+1) + " (" +
      // toString(bricks[i].self()->getPosition().x) + "," +
      // toString(bricks[i].self()->getPosition().y) + ")");
      bricks[i].render(window);
    }
    for (int i = 0; i < drops.size(); i++) {
      drops.at(i).render(window);
    }

    window.draw(stats);
    platform->render(window);
    ball->render(window);
    window.display();
  }

  return 0;
}
