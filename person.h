#pragma once

#include <memory>

#include "spritemap.h"

class Person {
  public:

    enum class Facing { Left, Right };

    Person(Facing facing, float x, float y);

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;

    void set_facing(Facing facing);
    void start_walking();
    void stop_walking();

    float get_x() const;

  private:

    int frame_;
    Facing facing_;
    bool walking_;
    float x_, y_;

    std::unique_ptr<SpriteMap> sprites_;
};
