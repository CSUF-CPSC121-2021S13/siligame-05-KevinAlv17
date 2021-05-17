#include "player.h"
#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

void Player::Move(const graphics::Image& moving) {}

void PlayerProjectile::Move(const graphics::Image& moving) {
  if (GameElement::IsOutOfBounds(moving)) {
    is_active_ = false;
  } else {
    SetX(GetX() + 1);
    SetY(GetY() + 1);
  }
}

void Player::Draw(graphics::Image& screen) {
  screen.DrawCircle(GetX() + 24, GetY() + 25, 23, 251, 245, 0);
  screen.DrawCircle(GetX() + 15, GetY() + 15, 4, 0, 0, 0);
  screen.DrawCircle(GetX() + 32, GetY() + 15, 4, 0, 0, 0);
  screen.DrawRectangle(GetX() + 10, GetY() + 34, 30, 3, 0, 0, 0);
  screen.DrawRectangle(GetX() + 10, GetY() + 30, 3, 7, 0, 0, 0);  // left smile
  screen.DrawRectangle(GetX() + 37, GetY() + 30, 3, 7, 0, 0, 0);  // right smile
}

void PlayerProjectile::Draw(graphics::Image& screen) {
  screen.DrawRectangle(GetX(), GetY(), 5, 5, 1, 23, 255);
}
