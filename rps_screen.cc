#include "rps_screen.h"

void RPSScreen::init() {
  font_.reset(new Font("Roboto-Regular.ttf"));
  backdrop_.reset(new Backdrop("rpsbg.png"));
  arms_.reset(new SpriteMap("arms.png", 6, 480, 432));

  timer_ = 0;
  p1score_ = p2score_ = 0;
  p1choice_ = p2choice_ = Choice::Rock;
}

bool RPSScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (timer_ > 0) timer_ -= elapsed;

  switch (stage_) {

    case Stage::Choose:

      if (input.key_pressed(SDL_SCANCODE_R)) {
        choose(Choice::Rock);
      } else if (input.key_pressed(SDL_SCANCODE_P)) {
        choose(Choice::Paper);
      } else if (input.key_pressed(SDL_SCANCODE_S)) {
        choose(Choice::Scissors);
      }

      break;

    case Stage::Animate:

      if (timer_ <= 0) {
        score();
        stage_ = Stage::Result;
        timer_ = 1000;

        if (p1choice_ != p2choice_) {
          if (p2score_ > p1score_) {
            text_.reset(new AppearingText("Looks like the room is mine, sucker!"));
          } else if (p1score_ == 1 && p2score_ == 0) {
            text_.reset(new AppearingText("Best two out of three."));
          } else if (p1score_ == 2) {
            text_.reset(new AppearingText("Fine, you can have the room."));
          }
        }
      }

      break;

    case Stage::Result:

      if (text_) {
        text_->update(audio, elapsed);

        if (input.any_pressed()) {
          if (text_->done()) {
            if (p1score_ == 2) {
              player_won();
              return false;
            } else if (p2score_ > p1score_) {
              player_lost();
              return false;
            }

            stage_ = Stage::Choose;
            text_.reset(NULL);
          } else {
            text_->finish();
          }
        }

      } else if (timer_ <= 0) {
        stage_ = Stage::Choose;
      }

      break;
  }

  return true;
}

void RPSScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);

  switch (stage_) {

    case Stage::Choose:

      arms_->draw_ex(graphics, 0, 160, 160, false, 0.00, 0, 0);
      arms_->draw_ex(graphics, 0, 642, 160, true, 0.00, 0, 0);

      font_->draw(graphics, "R: rock", 50, 50, 0xfff1e8ff);
      font_->draw(graphics, "P: paper", 50, 66, 0xfff1e8ff);
      font_->draw(graphics, "S: scissors", 50, 82, 0xfff1e8ff);

      break;

    case Stage::Animate:

      {
        // TODO draw arms flailing a few times
        const int i = ((1500 - timer_) / 100) % 6;
        const int f = i > 3 ? 6 - i : i;

        arms_->draw_ex(graphics, f, 160, 160, false, 0.00, 0, 0);
        arms_->draw_ex(graphics, f, 642, 160, true, 0.00, 0, 0);
      }

      break;

    case Stage::Result:

      {
        int p1f, p2f;

        switch (p1choice_) {
          case Choice::Rock: p1f = 3; break;
          case Choice::Paper: p1f = 5; break;
          case Choice::Scissors: p1f = 4; break;
        }

        switch (p2choice_) {
          case Choice::Rock: p2f = 3; break;
          case Choice::Paper: p2f = 5; break;
          case Choice::Scissors: p2f = 4; break;
        }

        arms_->draw_ex(graphics, p1f, 160, 160, false, 0.00, 0, 0);
        arms_->draw_ex(graphics, p2f, 642, 160, true, 0.00, 0, 0);
      }

      if (text_) {
        text_->draw(graphics, font_.get(), 800, 300, 0xfff1e8ff);
      }

      break;
  }
}

void RPSScreen::choose(Choice choice) {
  // almost definitely not uniform, so players can exploit
  const int r = std::rand() % 3;
  switch (r) {
    case 0:
      p2choice_ = Choice::Rock;
      break;

    case 1:
      p2choice_ = Choice::Paper;
      break;

    case 2:
      p2choice_ = Choice::Scissors;
      break;
  }

  p1choice_ = choice;

  stage_ = Stage::Animate;
  timer_ = 1500;
}

void RPSScreen::score() {
  switch (p1choice_) {

    case Choice::Rock:
      if (p2choice_ == Choice::Scissors) ++p1score_;
      if (p2choice_ == Choice::Paper) ++p2score_;
      break;

    case Choice::Paper:
      if (p2choice_ == Choice::Rock) ++p1score_;
      if (p2choice_ == Choice::Scissors) ++p2score_;
      break;

    case Choice::Scissors:
      if (p2choice_ == Choice::Paper) ++p1score_;
      if (p2choice_ == Choice::Rock) ++p2score_;
      break;

  }
}

std::string RPSScreen::choice_name(Choice choice) {
  switch (choice) {
    case Choice::Rock:     return "Rock";
    case Choice::Paper:    return "Paper";
    case Choice::Scissors: return "Scissors";
    default:               return "Unknown";
  }
}

