#pragma once

#include <memory>

#include "backdrop.h"
#include "input.h"
#include "graphics.h"
#include "screen.h"
#include "text.h"

#include "email_screen.h"

class TitleScreen : public Screen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

    Screen* next_screen();

  private:

    std::unique_ptr<Text> text_;
    std::unique_ptr<Backdrop> backdrop_;

};
