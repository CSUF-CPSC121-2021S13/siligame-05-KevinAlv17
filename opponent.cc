#include "opponent.h"
#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game.h"
#include "game_element.h"

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

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  int count = 0;
  if (count == 15) {
    std::unique_ptr<OpponentProjectile> oppTile =
        std::make_unique<OpponentProjectile>(GetX() + (GetWidth() / 2),
                                             GetY() + GetHeight());
    count = 0;
    return std::move(oppTile);
  } else {
    count++;
    return nullptr;
  }
}
