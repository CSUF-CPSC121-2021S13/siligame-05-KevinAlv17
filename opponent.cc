#include "opponent.h"
#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "game.h"

void Opponent::Draw(graphics::Image& screen) {
  screen.DrawCircle(GetX() + 23, GetY() + 23, 23, 79, 244, 27);
  screen.DrawCircle(GetX() + 23, GetY() + 23, 16, 255, 255, 255);
  screen.DrawCircle(GetX() + 23, GetY() + 23, 13, 255, 0, 0);
  screen.DrawCircle(GetX() + 23, GetY() + 23, 8, 0, 0, 0);
}

void OpponentProjectile::Draw(graphics::Image& screen) {
  screen.DrawRectangle(GetX(), GetY(), 5, 5, 103, 186, 58);
}

void Opponent::Move(const graphics::Image& moving) {
  if (GameElement::IsOutOfBounds(moving)) {
    is_active_ = false;
  } else {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  }
}

void OpponentProjectile::Move(const graphics::Image& moving) {
  if (GameElement::IsOutOfBounds(moving)) {
    is_active_ = false;
  } else {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  }
}

