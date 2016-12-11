#include "person.h"

Person::Person(Facing facing, float x, float y) : frame_(0), facing_(facing), walking_(true), x_(x), y_(y) {
  sprites_.reset(new SpriteMap("walk.png", 8, 176, 416));
}

void Person::update(unsigned int elapsed) {
  frame_ += elapsed;

  if (walking_) {
    // TODO fix walk speed
    x_ += elapsed * 0.15f * (facing_ == Facing::Left ? -1 : 1);
  }
}

void Person::draw(Graphics& graphics) const {
  const int f = (frame_ / 100) % 8;
  sprites_->draw_ex(graphics, walking_ ? f : 0, x_, y_, facing_ == Facing::Left, 0.00, 0, 0);
}

void Person::start_walking() {
  walking_ = true;
}

void Person::stop_walking() {
  walking_ = false;
}

float Person::get_x() const {
  return x_;
}
