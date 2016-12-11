#include "email_screen.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "generators.h"
#include "lobby_screen.h"

void EmailScreen::init() {
  font_.reset(new Font("Roboto-Regular.ttf", 14));
  backdrop_.reset(new Backdrop("emailui.png"));

  reading_ = false;
  selected_ = 0;

  std::time_t t = std::time(0);
  std::tm* time = std::localtime(&t);
  clock_ms_ = 1000 * (time->tm_sec + time->tm_min * 60 + time->tm_hour * 3600);
}

bool EmailScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (reading_) {
    // reading email controls

    const Email email = emails_[selected_];

    if (input.key_pressed(SDL_SCANCODE_ESCAPE)) {
      reading_ = false;
      audio.play_sample("select.wav");
    }

    if (input.key_pressed(SDL_SCANCODE_D)) {
      reading_ = false;
      emails_.erase(emails_.begin() + selected_);
      if (selected_ > emails_.size() - 1) selected_ = emails_.size() - 1;

      audio.play_sample("delete.wav");
    }

    if (email.conference && input.key_pressed(SDL_SCANCODE_RETURN)) {
      audio.play_sample("register.wav");
      return false;
    }

  } else {
    // inbox controls

    if (input.key_pressed(SDL_SCANCODE_W) || input.key_pressed(SDL_SCANCODE_UP)) {
      if (selected_ > 0) {
        --selected_;
        audio.play_sample("select.wav");
      }
    }

    if (input.key_pressed(SDL_SCANCODE_S) || input.key_pressed(SDL_SCANCODE_DOWN)) {
      if (selected_ < emails_.size() - 1) {
        ++selected_;
        audio.play_sample("select.wav");
      }
    }

    if (input.key_pressed(SDL_SCANCODE_RETURN)) {
      if (selected_ < emails_.size()) {
        reading_ = true;
        audio.play_sample("select.wav");
      }
    }

    // simulate getting new mail
    if (emails_.size() < 10) {
      if (std::rand() % 100 == 1) {

        if (state_.lost_previous) {
          emails_.push_back(Email::make_angry_boss_email(state_.lives));
          state_.lost_previous = false;
        } else if (state_.lives > 0) {
          emails_.push_back(Email::make_conference_email(current_month()));
        }

        audio.play_sample("newmail.wav");
      }
    }
  }

  clock_ms_ += elapsed;

  return true;
}

void EmailScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);

  const int y = 80;
  const int x = 144;
  const int green = 0x00e756ff;

  if (reading_) {
    // draw single email

    const Email email = emails_[selected_];

    font_->draw(graphics, "From:", x, y, green);
    font_->draw(graphics, "Subject: ", x, y + 16, green);

    font_->draw(graphics, email.from, x + 64, y, green);
    font_->draw(graphics, email.subject, x + 64, y + 16, green);

    font_->draw(graphics, email.body, x, y + 48, green);

    // TODO only show "register" on conference emails
    font_->draw(graphics, "D: delete   ESC: inbox   ENTER: register", x, y + 416, green);

  } else {
    // draw email inbox

    for (int i = 0; i < emails_.size(); ++i) {
      const int yi = y + 40 * i;

      const Email email = emails_[i];

      if (selected_ == i) font_->draw(graphics, ">", x, yi + 8, green);

      font_->draw(graphics, email.from, x + 12, yi, green);
      font_->draw(graphics, email.subject, x + 12, yi + 16, green);
    }

    font_->draw(graphics, "UP/DOWN: select   ENTER: read", x, y + 416, green);
  }

  // draw the clock
  draw_hand(graphics, 50, clock_ms_ / 43200000.0f , 0x1d2b53ff);
  draw_hand(graphics, 70, clock_ms_ / 3600000.0f , 0x1d2b53ff);
  draw_hand(graphics, 70, clock_ms_ / 60000.0f, 0xff004dff);

  // draw the calendar
  font_->draw(graphics, current_month(), 1000, 330, 0x1d2b53ff);
}

Screen* EmailScreen::next_screen() {
  if (state_.lives > 0) {
    LobbyScreen* screen = new LobbyScreen();
    screen->set_game_state(state_);
    return screen;
  } else {
    // game over, do high score screen or something
    return NULL;
  }
}

void EmailScreen::set_game_state(GameState state) {
  state_ = state;
}

EmailScreen::Email::Email() : from(""), subject(""), body(""), conference(false) {}

EmailScreen::Email EmailScreen::Email::make_conference_email(const std::string& month) {
  EmailScreen::Email email;

  const std::string conf_name = Generators::generate_conference_name();

  email.from = Generators::generate_name();
  email.subject = Generators::generate_conference_email_subject(conf_name);
  email.body = Generators::generate_conference_email_body(conf_name, email.from, month);
  email.conference = true;

  return email;
}

EmailScreen::Email EmailScreen::Email::make_angry_boss_email(int lives) {
  EmailScreen::Email email;

  email.from = Generators::generate_name();
  email.subject = Generators::generate_angry_email_subject();
  email.body = Generators::generate_angry_email_body(email.from, lives);

  return email;
}

void EmailScreen::draw_hand(Graphics& graphics, int length, float value, int color) const {
  const float pi = 3.14159;

  const int cx = 1028, cy = 173;

  const int hx = cx + length * std::cos(value * 2 * pi - pi / 2.0f);
  const int hy = cy + length * std::sin(value * 2 * pi - pi / 2.0f);

  graphics.draw_line(cx, cy, hx, hy, color);
}

std::string EmailScreen::current_month() const {
  return month_names_[state_.month];
}

const std::vector<std::string> EmailScreen::month_names_ = {
  "January", "February", "March", "April", "May", "June", "July", "August",
  "September", "October", "November", "December",
};
