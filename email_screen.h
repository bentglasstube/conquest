#pragma once

#include <memory>
#include <vector>

#include "backdrop.h"
#include "font.h"
#include "screen.h"

#include "game_state.h"

class EmailScreen : public Screen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;
    Screen* next_screen();

    void set_game_state(GameState state);

  private:

    class Email {
      public:
        Email();

        static Email make_conference_email(const std::string& month);
        static Email make_angry_boss_email(int lives);
        static Email make_bonus_email(int lives);

        std::string from, subject, body;
        bool conference;
    };

    std::unique_ptr<Font> font_;
    std::unique_ptr<Backdrop> backdrop_;

    std::vector<Email> emails_;

    bool reading_;
    size_t selected_;
    int clock_ms_;
    GameState state_;

    void draw_hand(Graphics& graphics, int length, float value, int color) const;
    std::string current_month() const;

    static const std::vector<std::string> month_names_;
};
