#pragma once

#include <memory>

#include "backdrop.h"
#include "font.h"
#include "sprite.h"

#include "appearing_text.h"
#include "minigame_screen.h"

class FourScreen : public MinigameScreen {
  public:

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

  private:

    class Board {
      public:

        Board();

        void reset();
        bool place(int col, int p);
        void remove(int col);
        int evaluate(int player) const;
        int at(int col, int row) const;
        int sum(int col, int row, int dc, int dr) const;
        bool full() const;
        bool done() const;
        int winner() const;
        bool draw() const;

      private:

        int cells_[7][6];

    };

    void place_piece(Audio& audio, int col);
    int choose_move();
    int minimax(Board& board, int depth, int player);

    Board board_;
    int turn_;

    std::unique_ptr<Backdrop> backdrop_;
    std::unique_ptr<Sprite> gameboard_;
    std::unique_ptr<Font> font_;
    std::unique_ptr<AppearingText> text_;
};
