#include "appearing_text.h"

#include <cstdlib>

#include "font.h"

#define LETTER_RATE 75

AppearingText::AppearingText(const std::string& text) : count_(0), text_(text) {}

void AppearingText::update(Audio& audio, unsigned int elapsed) {
  count_ += elapsed;

  if (!done() && count_ / LETTER_RATE > (count_ - elapsed) / LETTER_RATE) {
    audio.play_sample("bla" + std::to_string(std::rand() % 7) + ".wav");
  }
}

void AppearingText::draw(Graphics& graphics, const Font* font, int x, int y, int color) const {
  const int letters = count_ / LETTER_RATE;
  if (letters > 0) font->draw(graphics, text_.substr(0, letters), x, y, color);
}

bool AppearingText::done() const {
  return count_ / LETTER_RATE > text_.length();
}

void AppearingText::finish() {
  count_ = LETTER_RATE * text_.length();
}
