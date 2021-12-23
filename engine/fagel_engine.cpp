//
// Created by piotr on 22/12/2021.
//

#include "fagel_engine.h"
Engine::Engine(int screen_height, int screen_width)
    : screen_height_(screen_height), screen_width_(screen_width),
      gravity_strength_(1), no_players_(1) {
  for (unsigned int i = 0; i < no_players_; i++) {
    players_.push_back({Coord(10, screen_height / 2), i});
  }
}
void Engine::Iterate() {
  AddHole();
  for (auto &hole : holes_)
    hole.x -= 1;

  for (auto &player : players_) {
    player.AddVelocity(-gravity_strength_);
    player.Iterate(holes_.front());
    if (CheckCollision(player))
      player.Kill();

    if (player.GetPosition().y < 0)
      player.Kill();
  }
}
bool Engine::CheckCollision(const Player &player) {
  return false;
  //  Coord circle_distance ;
  //
  //  circle_distance .x = abs(circle.x - rect.x);
  //  circle_distance.y = abs(circle.y - rect.y);
  //
  //  if (circle_distance.x > (rect.width / 2 + circle.r)) {
  //    return false;
  //  }
  //  if (circle_distance.y > (rect.height / 2 + circle.r)) {
  //    return false;
  //  }
  //
  //  if (circle_distance.x <= (rect.width / 2)) {
  //    return true;
  //  }
  //  if (circle_distance.y <= (rect.height / 2)) {
  //    return true;
  //  }
  //
  //  cornerDistance_sq = (circle_distance.x - rect.width / 2) ^
  //                      2 + (circle_distance.y - rect.height / 2) ^ 2;
  //
  //  return (cornerDistance_sq <= (circle.r ^ 2));
}
const std::vector<Player> &Engine::GetPlayers() const { return players_; }
const std::vector<Coord> &Engine::GetHoles() const { return holes_; }
