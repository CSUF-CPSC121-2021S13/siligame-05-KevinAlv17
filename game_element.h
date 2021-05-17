#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H
#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), height_(height), width_(width) {}
  virtual void Draw(graphics::Image& game_screen) {
    game_screen.DrawRectangle(x_, y_, 5, 5, graphics::Color(0, 0, 0));
  }

  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

  int GetX() const { return x_; }
  int GetY() const { return y_; }

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  void SetIsActive(bool is_active) { is_active_ = is_active; }
  bool GetIsActive() const { return is_active_; }

  virtual void Move(const graphics::Image& moving) = 0;
  bool IntersectsWith(GameElement* game);
  bool IsOutOfBounds(const graphics::Image& gamescreen);

 protected:
  int x_ = 0;
  int y_ = 0;
  int width_ = 50;
  int height_ = 50;
  bool is_active_ = true;
};
#endif
