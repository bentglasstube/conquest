#pragma once

#include <memory>

#include "backdrop.h"
#include "input.h"
#include "font.h"
#include "graphics.h"
#include "screen.h"

#include "email_screen.h"

class TitleScreen : public Screen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

    Screen* next_screen();

  private:

    std::unique_ptr<Backdrop> backdrop_;
    std::unique_ptr<Font> font_;

};
