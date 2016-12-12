#pragma once

#include <memory>

#include "backdrop.h"
#include "font.h"
#include "sprite.h"

#include "appearing_text.h"
#include "minigame_screen.h"

class ArmWrestleScreen : public MinigameScreen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

  private:

    float angle_;
    int next_button_;

    std::unique_ptr<Backdrop> backdrop_;
    std::unique_ptr<Sprite> arms_;
    std::unique_ptr<Font> font_;
    std::unique_ptr<AppearingText> text_;
};
