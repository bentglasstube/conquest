#include "game.h"

#include <cstdlib>
#include <ctime>

#include "title_screen.h"

int main(int, char*) {
  Game::Config config;

  config.graphics.title = "Ludum Dare 37";
  config.graphics.width = 1280;
  config.graphics.height = 720;
  config.graphics.fullscreen = true;

  TitleScreen *s = new TitleScreen();

  std::srand(std::time(0));

  Game game(config);
  game.loop(s);

  return 0;
}
