#ifndef OPPONENT_H
#define OPPONENT_H
#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : GameElement(0, 0, 5, 5) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& moving) override;
  
  std::unique_ptr<OpponentProjectile> LaunchProjectile() {
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

 private:
  int count = 0;
};

class Opponent : public GameElement {
 public:
  Opponent() : GameElement(0, 0, 45, 45) {}

  Opponent(const int& x, const int& y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image& screen) override;
  void Move(const graphics::Image& moving) override;

  std::unique_ptr<OpponentProjectile> LaunchProjectile();

};
#endif
