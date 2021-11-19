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
#include "dxball/Player.h"

using namespace sf;

class Drop {
 public:
  int m_speed;
  CircleShape drop;

  Drop(int radius, Color color, int speed, Vector2f position) {
    m_speed = speed;
    drop.setRadius(radius);
    drop.setFillColor(color);
    drop.setPosition(position);
  }
  void move() {
    drop.setPosition(drop.getPosition().x, drop.getPosition().y + m_speed);
  }
  ~Drop() {}
  void render(RenderWindow& w) { w.draw(drop); }
  bool isColliding(const RectangleShape& obstacle) {
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
};

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
    default_font.loadFromFile("../assets/Roboto-Regular.ttf");
    bsb.loadFromFile("../assets/sounds/glass.ogg");
    psb.loadFromFile("../assets/sounds/sonar.ogg");
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

  Player* platform = new Player(160, 10, Color(223, 77, 2), 10);
  Ball* ball = new Ball(10, 15, Color::Blue);
  std::deque<Brick> bricks(total_bricks);
  std::deque<Drop> drops;
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
      }
    }

    ball->move();

    for (int i = 0; i < drops.size(); i++) {
      drops.at(i).move();
    }

    platform->player.setPosition(Mouse::getPosition().x,
                                 platform->player.getPosition().y);

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

    float ratio = ball->isColliding(platform->player);
    if (ratio != 0) {
      platform_sound.play();
      // log(toString(rand() % 255));
      ball->setHorizontalVelocity((ratio)*ball->getVerticalVelocity());
      ball->setVerticalVelocity(-ball->getVerticalVelocity());
      int r = rand() % 255;
      int g = rand() % 255;
      int b = rand() % 255;
      // std::cout<<"rgb("<<r<<","<<g<<","<<b<<")"<<std::endl;
      ball->self()->setFillColor(Color(r, g, b));
      total_bounces += 1;
    }

    for (int i = 0; i < bricks.size(); i++) {
      float ratio = ball->isColliding(*bricks[i].self());
      if (ratio != 0) {
        ball->setHorizontalVelocity((-ratio) * ball->getVerticalVelocity());
        ball->setVerticalVelocity(-ball->getVerticalVelocity());
        brick_sound.play();
        if (bricks[i].getLifeCount() == 0) {
          if (rand() % 100 <= 40) {
            drops.push_back(Drop(13, Color(250, 250, 250), 8,
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
      if (drops.at(i).isColliding(platform->player)) {
        drops.erase(drops.begin() + i);
        platform->player.setSize(Vector2f(platform->player.getSize().x + 10,
                                          platform->player.getSize().y));
        platform->player.setOrigin(platform->player.getSize().x / 2,
                                   platform->player.getSize().y / 2);
        score += 3;
      }
    }
    if (level_time >= 20) {
      level_time = 0;
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
