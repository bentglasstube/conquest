#pragma once

#include <memory>

#include "backdrop.h"
#include "font.h"
#include "screen.h"

#include "appearing_text.h"
#include "game_state.h"
#include "person.h"

class LobbyScreen : public Screen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;
    Screen* next_screen();

    void set_game_state(GameState state);

  private:

    int stage_;

    GameState state_;

    std::unique_ptr<Font> font_;
    std::unique_ptr<Backdrop> backdrop_;
    std::unique_ptr<Person> player_, enemy_;
    std::unique_ptr<AppearingText> text_;
};
