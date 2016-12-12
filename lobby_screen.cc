#include "lobby_screen.h"

#include "font.h"

#include "arm_screen.h"
#include "four_screen.h"
#include "rps_screen.h"

void LobbyScreen::init() {
  stage_ = 0;

  backdrop_.reset(new Backdrop("lobbybg.png"));
  font_.reset(new Font("Roboto-Regular.ttf"));
  player_.reset(new Person(Person::Facing::Right, 0, 200));
  enemy_.reset(new Person(Person::Facing::Left, 1104, 200));

  minigame_ = std::rand() % 3;
}

bool LobbyScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (text_) {
    text_->update(audio, elapsed);
    if (!text_->done() && input.any_pressed()) text_->finish();
  }

  switch (stage_) {

    case 0: // walking up to the counter

      player_->update(elapsed);
      enemy_->update(elapsed);

      if (player_->get_x() > 450) {
        player_->stop_walking();
        enemy_->stop_walking();

        stage_ = 1;
        // TODO randomize text
        text_.reset(new AppearingText("Welcome to the hotel.\nI am sad to say that we have only ONE ROOM available..."));
      }

      break;

    case 1: // attendant speaks

      if (text_->done() && input.any_pressed()) {
        stage_ = 2;
        // TODO randomize text
        text_.reset(new AppearingText("In that case, I challenge you to " + minigame_name()));
      }

      break;

    case 2: // enemy challenges you

      if (text_->done() && input.any_pressed()) return false;

  }

  return true;
}

void LobbyScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);

  player_->draw(graphics);
  enemy_->draw(graphics);

  switch (stage_) {
    case 1:

      text_->draw(graphics, font_.get(), 450, 100, 0xfff1e8ff);
      break;

    case 2:

      text_->draw(graphics, font_.get(), 800, 300, 0xfff1e8ff);
      break;

  }
}

Screen* LobbyScreen::next_screen() {
  MinigameScreen* screen;

  switch (minigame_) {
    case 0: screen = new RPSScreen(); break;
    case 1: screen = new FourScreen(); break;
    case 2: screen = new ArmWrestleScreen(); break;
  }

  screen->set_game_state(state_);
  return screen;
}

void LobbyScreen::set_game_state(GameState state) {
  state_ = state;
}

std::string LobbyScreen::minigame_name() const {
  switch (minigame_) {
    case 0:  return "rock, paper, scissors";
    case 1:  return "connect four";
    case 2:  return "arm wrestling";
    default: return "ERROR UNKNOWN GAME";
  }
}
