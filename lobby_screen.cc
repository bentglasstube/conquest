#include "lobby_screen.h"

void LobbyScreen::init() {
  backdrop_.reset(new Backdrop("lobbybg.png"));
}

bool LobbyScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  // handle input

  // update text?  I don't know what will go here really

  return true;
}

void LobbyScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);

  // draw attendant
  // draw player
  // draw opponent
}

Screen* LobbyScreen::next_screen() {
  // determine mini game to play and load that screen next

  // placeholder
  return NULL;
}

void LobbyScreen::set_game_state(GameState state) {
  state_ = state;
}
