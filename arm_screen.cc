#include "arm_screen.h"

#include "generators.h"

void ArmWrestleScreen::init() {
  angle_ = 0.0f;
  next_button_ = 0;

  backdrop_.reset(new Backdrop("wrestlebg.png"));
  arms_.reset(new Sprite("wrestlearms.png", 0, 0, 64, 192));
  font_.reset(new Font("Roboto-Regular.ttf"));
}

#define ANGLE_INCREMENT 0.1f
#define ANGLE_THRESHOLD 1.570796f

bool ArmWrestleScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (text_) {
    text_->update(audio, elapsed);

    if (input.key_pressed(SDL_SCANCODE_SPACE)) {
      if (text_->done()) {
        return false;
      } else {
        text_->finish();
      }
    }
  } else {

    angle_ -= ANGLE_INCREMENT * elapsed / 100.0f;

    if (input.key_pressed(SDL_SCANCODE_F)) {
      if (next_button_ == 0) {
        angle_ += ANGLE_INCREMENT;
        next_button_ = 1;
      } else {
        angle_ -= ANGLE_INCREMENT;
      }
    }

    if (input.key_pressed(SDL_SCANCODE_J)) {
      if (next_button_ == 1) {
        angle_ += ANGLE_INCREMENT;
        next_button_ = 0;
      } else {
        angle_ -= ANGLE_INCREMENT;
      }
    }

    if (angle_ < -ANGLE_THRESHOLD) {
      player_lost();
      audio.play_sample("armhit.wav");
      text_.reset(new AppearingText(Generators::generate_gloat()));
    } else if (angle_ > ANGLE_THRESHOLD) {
      player_won();
      audio.play_sample("armhit.wav");
      text_.reset(new AppearingText(Generators::generate_concession()));
    }
  }

  return true;
}

void ArmWrestleScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);
  arms_->draw_ex(graphics, 610, 352, false, -angle_, 32, 96);
  font_->draw(graphics, "Alternate F and J quickly!", 576, 500, 0xfff1e8ff);
  if (text_) text_->draw(graphics, font_.get(), 950, 100, 0xfff1e8ff);
}
