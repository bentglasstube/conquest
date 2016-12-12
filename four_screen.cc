#include "four_screen.h"

#include "generators.h"

void FourScreen::init() {

  turn_ = 1;

  backdrop_.reset(new Backdrop("tablebg.png"));
  gameboard_.reset(new Sprite("connect4.png", 0, 0, 576, 576));
  font_.reset(new Font("Roboto-Regular.ttf", 14));
}

bool FourScreen::update(const Input& input, Audio& audio, unsigned int elapsed) {
  if (!board_.done()) {

    if (turn_ == -1) {
      if (input.key_pressed(SDL_SCANCODE_1)) place_piece(audio, 0);
      if (input.key_pressed(SDL_SCANCODE_2)) place_piece(audio, 1);
      if (input.key_pressed(SDL_SCANCODE_3)) place_piece(audio, 2);
      if (input.key_pressed(SDL_SCANCODE_4)) place_piece(audio, 3);
      if (input.key_pressed(SDL_SCANCODE_5)) place_piece(audio, 4);
      if (input.key_pressed(SDL_SCANCODE_6)) place_piece(audio, 5);
      if (input.key_pressed(SDL_SCANCODE_7)) place_piece(audio, 6);
    } else {
      place_piece(audio, choose_move());
    }

  } else {

    if (text_) {
      text_->update(audio, elapsed);

      if (input.any_pressed()) {
        if (text_->done()) {
          if (board_.winner() == 0) {
            turn_ = -1;
            board_.reset();
            text_.reset(NULL);
          } else {
            return false;
          }
        } else {
          text_->finish();
        }
      }
    } else {
      if (board_.winner() == 1) {
        player_lost();
        text_.reset(new AppearingText(Generators::generate_gloat()));
      } else if (board_.winner() == -1) {
        player_won();
        text_.reset(new AppearingText(Generators::generate_concession()));
      } else if (board_.full()) {
        text_.reset(new AppearingText(Generators::generate_rematch()));
      }
    }
  }

  return true;
}

void FourScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);

  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 6; ++j) {
      const int p = board_.at(i, j);
      if (p != 0) {
        const SDL_Rect r = { 416 + i * 64, 480 - j * 64, 64, 64 };
        const int color = p == 1 ? 0xff004dff : 0xfff024ff;
        graphics.draw_rect(&r, color, true);
      }
    }
  }

  gameboard_->draw(graphics, 352, 96);

  if (text_) text_->draw(graphics, font_.get(), 928, 32, 0xfff1e8ff);
}

void FourScreen::place_piece(Audio& audio, int col) {
  if (board_.place(col, turn_)) {
    turn_ *= -1;
    audio.play_sample("4.wav");
  }
}

int FourScreen::choose_move() {
  int best = 99999;
  int col = -1;
  for (int i = 0; i < 7; ++i) {
    if (board_.place(i, turn_)) {
      int score = minimax(board_, 5, -turn_);
      if (score < best) {
        best = score;
        col = i;
      }
      board_.remove(i);
    }
  }
  return col;
}

int FourScreen::minimax(Board& board, int depth, int player) {
  if (depth == 0 || board.done()) return board.evaluate(player);

  int best = -99999;

  for (int col = 0; col < 7; ++col) {
    if (board.place(col, player)) {
      int score = -minimax(board, depth - 1, -player);
      if (score > best) best = score;
      board.remove(col);
    }
  }

  return best;
}

FourScreen::Board::Board() {
  reset();
}

void FourScreen::Board::reset() {
  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 6; ++j) {
      cells_[i][j] = 0;
    }
  }
}

bool FourScreen::Board::place(int col, int p) {
  for (int j = 0; j < 6; ++j) {
    if (cells_[col][j] == 0) {
      cells_[col][j] = p;
      return true;
    }
  }
  return false;
}

void FourScreen::Board::remove(int col) {
  for (int j = 5; j >= 0; --j) {
    if (cells_[col][j] != 0) {
      cells_[col][j] = 0;
      return;
    }
  }
}

int FourScreen::Board::evaluate(int player) const {
  const int w = winner();
  if (w == player) return 1000;
  if (w == -player) return -1000;

  int value = 0;

  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 2; ++j) {
      const int vert = sum(i, j, 0, 1);
      if (vert == 4) value += 1000;
      if (vert == -4) value -= 1000;
      if (vert == 3) value += 100;
      if (vert == -3) value -= 100;

      if (i < 3) {
        const int diag = sum(i, j, 1, 1);
        if (diag == 4) value += 1000;
        if (diag == -4) value -= 1000;
        if (diag == 3) value += 100;
        if (diag == -3) value -= 100;
      }

      if (i > 2) {
        const int diag = sum(i, j, -1, 1);
        if (diag == 4) value += 1000;
        if (diag == -4) value -= 1000;
        if (diag == 3) value += 100;
        if (diag == -3) value -= 100;
      }
    }
  }

  for (int j = 0; j < 6; ++j) {
    for (int i = 0; i < 3; ++i) {
      const int horz = sum(i, j, 1, 0);
      if (horz == 4) value += 1000;
      if (horz == -4) value -= 1000;
      if (horz == 3) value += 100;
      if (horz == -3) value -= 100;
    }
  }

  return value * player;
}

int FourScreen::Board::at(int col, int row) const {
  return cells_[col][row];
}

int FourScreen::Board::sum(int col, int row, int dc, int dr) const {
  int sum = 0;
  for (int k = 0; k < 4; ++k) {
    sum += at(col + dc * k, row + dr * k);
  }
  return sum;
}

bool FourScreen::Board::full() const {
  for (int i = 0; i < 7; ++i) {
    if (cells_[i][5] == 0) return false;
  }
  return true;
}

bool FourScreen::Board::done() const {
  return full() || winner() != 0;
}

int FourScreen::Board::winner() const {
  for (int i = 0; i < 7; ++i) {
    for (int j = 0; j < 3; ++j) {
      const int vert = sum(i, j, 0, 1);
      if (vert == 4) return 1;
      if (vert == -4) return -1;

      if (i < 4) {
        const int diag = sum(i, j, 1, 1);
        if (diag == 4) return 1;
        if (diag == -4) return -1;
      }

      if (i > 2) {
        const int diag = sum(i, j, -1, 1);
        if (diag == 4) return 1;
        if (diag == -4) return -1;
      }
    }
  }

  for (int j = 0; j < 6; ++j) {
    for (int i = 0; i < 4; ++i) {
      const int horz = sum(i, j, 1, 0);
      if (horz == -4) return -1;
      if (horz == 4) return 1;
    }
  }

  return 0;
}

bool FourScreen::Board::draw() const {
  return full() && winner() == 0;
}
