#pragma once

#include "backdrop.h"
#include "font.h"
#include "spritemap.h"

#include "appearing_text.h"
#include "minigame_screen.h"

class RPSScreen : public MinigameScreen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

  private:

    enum class Stage { Choose, Animate, Result, Conclusion };
    enum class Choice { Rock, Paper, Scissors };

    void choose(Choice choice);
    void score();

    static std::string choice_name(Choice choice);

    Stage stage_;
    int timer_;
    int p1score_, p2score_;
    Choice p1choice_, p2choice_;

    std::unique_ptr<Font> font_;
    std::unique_ptr<Backdrop> backdrop_;
    std::unique_ptr<SpriteMap> arms_;
    std::unique_ptr<AppearingText> text_;
};
