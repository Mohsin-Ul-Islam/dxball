#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>

class GameState {
 public:
  // function to pause the current game state
  virtual void pause() = 0;

  // function to unpause the current game state
  virtual void unpause() = 0;

  // draw the current game state
  virtual void render(sf::RenderWindow& window) = 0;

  // this will be called once every frame
  // `deltaTime` denotes the time it took for the last frame to finish
  virtual void tick(const float& deltaTime) = 0;
};

#endif  // GAMESTATE_H
