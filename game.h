#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game() : game_screen(800, 600) {}
  Game(int width, int height) : game_screen(width, height) {}

  graphics::Image &GetGameScreen() { return game_screen; }

  int GetScore() { return score; }

  bool HasLost() { return HasLost_; }

  Player &GetPlayer() { return player; }

  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponents_; }

  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponent_projectiles_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return player_projectiles_;
  }

  void CreateOpponents(); //{
    //Opponent opponent(100, 100);
    //opponents_.push_back(opponent);
  //}

  void CreateOpponentProjectiles(); //{
    //OpponentProjectile opponent_projectile(300, 300);
    //opponent_projectiles_.push_back(opponent_projectile);
  //}

  void CreatePlayerProjectiles(); //{
    //PlayerProjectile player_projectile(500, 500);
    //player_projectiles_.push_back(player_projectile);
  //}
  void Init();
  void UpdateScreen();
  void Start();
  void FilterIntersections();
  void RemoveInactive();
  void OnAnimationStep() override;
  void LaunchProjectiles();
  void OnMouseEvent(const graphics::MouseEvent &event) override;
  void MoveGameElements();

 protected:
  graphics::Image game_screen;
  std::vector<std::unique_ptr<Opponent>> opponents_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponent_projectiles_;
  std::vector<std::unique_ptr<PlayerProjectile>> player_projectiles_;
  Player player;
  int score = 0;
  bool HasLost_ = false;
};

#endif
