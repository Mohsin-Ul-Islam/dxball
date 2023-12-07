#ifndef RUN_STATE_H
#define RUN_STATE_H

#include <SFML/Audio/Sound.hpp>
#include <deque>

#include "include/dxball/Ball.h"
#include "include/dxball/Brick.h"
#include "include/dxball/Consumable.h"
#include "include/dxball/GameState.h"
#include "include/dxball/Platform.h"

class RunState : public GameState {
 public:
  RunState();

  RunState(std::string ffp, std::string bsf, std::string psf);

  void pause() override;
  void unpause() override;
  void tick(const float &deltaTime) override;
  void render(sf::RenderWindow &window) override;

  ~RunState() {}

 private:
  void init();

  bool isPaused;

  int screenWidth = 1920;
  int screenHeight = 1080;

  sf::Text stats;
  unsigned long score;

  std::string fontFilePath;
  std::string brickSoundFilePath;
  std::string platformSoundFilePath;

  sf::Sound brickSound;
  sf::Sound platformSound;

  Ball ball;
  Platform platform;

  std::deque<Brick> bricks;
  std::deque<Consumable> drops;
};

#endif  // RUN_STATE_H
