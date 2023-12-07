#include <SFML/Graphics.hpp>

#include "dxball/RunState.h"

using namespace sf;

int main(int argc, char** argv) {
  srand(time(0));

  Time time;
  Clock clock;

  int screen_width = 1920;
  int screen_height = 1080;

  RenderWindow window(VideoMode(screen_width, screen_height), "DxBall",
                      Style::Default);

  window.setFramerateLimit(60);
  window.setMouseCursorVisible(false);

  RunState state =
      RunState("assets/fonts/Roboto-Regular.ttf", "assets/sounds/glass.ogg",
               "assets/sounds/sonar.ogg");
  state.pause();

  while (window.isOpen()) {
    time = clock.restart();
    Event e;

    while (window.pollEvent(e)) {
      if (e.type == Event::Closed) {
        window.close();
      } else if (e.type == Event::MouseButtonPressed) {
        state.unpause();
      }
    }

    state.tick(time.asSeconds());

    window.clear();
    state.render(window);
    window.display();
  }

  return 0;
}
