#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

void Game::Init() {
  game_screen.AddMouseEventListener(*this);
  game_screen.AddAnimationEventListener(*this);
  player.GameElement::SetX(player.GameElement::GetX() + 5);
  player.GameElement::SetY(player.GameElement::GetY() + 5);
}

void Game::Start() { game_screen.ShowUntilClosed(); }

void Game::CreateOpponents() {
  opponents_.push_back(std::make_unique<Opponent>(100, 100));
}

void Game::MoveGameElements() {
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive() == true) {
      player_projectiles_[i]->Move(game_screen);
    }
  }
  for (int j = 0; j < opponent_projectiles_.size(); j++) {
    if (opponent_projectiles_[j]->GetIsActive() == true) {
      opponent_projectiles_[j]->Move(game_screen);
    }
  }
  for (int k = 0; k < opponents_.size(); k++) {
    if (opponents_[k]->GetIsActive() == true) {
      opponents_[k]->Move(game_screen);
    }
  }
  if (player.GetIsActive()) {
    player.Move(game_screen);
  }
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents_.size(); i++) {
    std::unique_ptr<OpponentProjectile> oppTile =
        std::make_unique<OpponentProjectile>(opponents_[i]->GetX(),
                                             opponents_[i]->GetY());
    if (opponents_[i]->LaunchProjectile() != nullptr) {
      opponent_projectiles_.push_back(std::move(oppTile));
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (player.IntersectsWith(opponent_projectiles_[i].get())) {
      player.SetIsActive(false);
      opponent_projectiles_[i]->SetIsActive(false);
      HasLost_ = true;
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    for (int j = 0; j < opponents_.size(); j++) {
      if (opponents_[j]->IntersectsWith(player_projectiles_[i].get())) {
        player_projectiles_[i]->SetIsActive(false);
        opponents_[j]->SetIsActive(false);
        if (player.GetIsActive() == true) {
          score++;
        }
      }
    }
  }
  for (int i = 0; i < opponents_.size(); i++) {
    if (player.IntersectsWith(opponents_[i].get())) {
      player.SetIsActive(false);
      opponents_[i]->SetIsActive(false);
      HasLost_ = true;
    }
  }
}

void Game::OnMouseEvent(const graphics::MouseEvent& event) {
  if (event.GetX() <= game_screen.GetWidth() && 0 <= event.GetX() &&
      event.GetY() <= game_screen.GetHeight() && 0 <= event.GetY()) {
    player.SetX(event.GetX() - 25);
    player.SetY(event.GetY() - 25);
  }
  if (event.GetMouseAction() == graphics::MouseAction::kPressed ||
      event.GetMouseAction() == graphics::MouseAction::kDragged) {
    player_projectiles_.push_back(std::make_unique<PlayerProjectile>(
        player.GetX() + player.GetWidth(), player.GetY()));
  }
}

void Game::RemoveInactive() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive() == false) {
      opponents_.erase(opponents_.begin() + i);
      i--;
    }
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive() == false) {
      opponent_projectiles_.erase(opponent_projectiles_.begin() + i);
      i--;
    }
  }
  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive() == false) {
      player_projectiles_.erase(player_projectiles_.begin() + i);
      i--;
    }
  }
}

void Game::UpdateScreen() {
  game_screen.DrawRectangle(0, 0, game_screen.GetWidth(),
                            game_screen.GetHeight(), 255, 255, 255);
  game_screen.DrawText(0, 0, "Score: " + std::to_string(score), 5, 0, 0, 0);
  if (player.GetIsActive() == true) {
    player.Draw(game_screen);
  }
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive() == true) {
      opponents_[i]->Draw(game_screen);
    }
  }
  for (int j = 0; j < opponent_projectiles_.size(); j++) {
    if (opponent_projectiles_[j]->GetIsActive() == true) {
      opponent_projectiles_[j]->Draw(game_screen);
    }
  }
  for (int k = 0; k < player_projectiles_.size(); k++) {
    if (player_projectiles_[k]->GetIsActive() == true) {
      player_projectiles_[k]->Draw(game_screen);
    }
  }
  if (HasLost_) {
    game_screen.DrawText(250, 250, "GAME OVER!", 25, 0, 0, 0);
  }
}

void Game::OnAnimationStep() {
  if (opponents_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  game_screen.Flush();
}
