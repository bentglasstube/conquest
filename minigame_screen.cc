#include "minigame_screen.h"

#include "email_screen.h"

void MinigameScreen::init() {
  complete_ = false;
}

Screen* MinigameScreen::next_screen() {
  ++state_.month;

  EmailScreen *screen = new EmailScreen();
  screen->set_game_state(state_);
  return screen;
}

void MinigameScreen::set_game_state(GameState state) {
  state_ = state;
}

void MinigameScreen::player_won() {
  state_.lost_previous = false;
  complete_ = true;
}

void MinigameScreen::player_lost() {
  state_.lost_previous = true;
  --state_.lives;
  complete_ = true;
}
