#pragma once

#include "audio.h"
#include "font.h"
#include "graphics.h"

class AppearingText {
  public:

    AppearingText(const std::string& text);

    void update(Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics, const Font* font, int x, int y, int color) const;

    bool done() const;
    void finish();

  private:

    int count_;
    std::string text_;
};
