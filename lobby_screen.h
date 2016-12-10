#pragma once

#include <memory>

#include "backdrop.h"
#include "screen.h"

#include "game_state.h"

class LobbyScreen : public Screen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;
    Screen* next_screen();

    void set_game_state(GameState state);

  private:

    std::unique_ptr<Backdrop> backdrop_;

    GameState state_;
};
