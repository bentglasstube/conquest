#include "title_screen.h"

void TitleScreen::init() {
  text_.reset(new Text("text.png"));
  backdrop_.reset(new Backdrop("title.png"));
}

bool TitleScreen::update(const Input& input, Audio&, unsigned int) {
  if (input.any_pressed()) {
    return false;
  }

  return true;
}

void TitleScreen::draw(Graphics& graphics) const {
  const int x = graphics.width() / 2;
  const int y = graphics.height() / 2;

  backdrop_->draw(graphics);
  text_->draw(graphics, "Press any key", x, y, Text::Alignment::CENTER);
}

Screen* TitleScreen::next_screen() {
  return new EmailScreen();
}
