#pragma once

#include <memory>

#include "screen.h"

#include "game_state.h"

class MinigameScreen : public Screen {
  public:

    virtual void init();
    virtual bool update(const Input& input, Audio& audio, unsigned int elapsed) = 0;
    virtual void draw(Graphics& graphics) const = 0;

    Screen* next_screen();

    void set_game_state(GameState state);
    void player_won();
    void player_lost();

  private:

    GameState state_;
    bool complete_;

};
