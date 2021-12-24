//
// Created by piotr on 22/12/2021.
//

#include "fagel_engine.h"
Engine::Engine(int screen_width, int screen_height)
    : screen_height_(screen_height), screen_width_(screen_width) {
  for (unsigned int i = 0; i < no_players_; i++) {
    players_.emplace_back(Coord(50, screen_height / 2 + (rand() % 100) - 50),
                          i);
  }
}
void Engine::Iterate() {
  DeleteHole();
  AddHole();

  for (auto &hole : holes_)
    hole.x -= 1;

  for (auto &player : players_) {
    if (!player.IsAlive()) {
      if (player.position_.x > 0)
        player.position_.x--;
    } else {
      player.AddVelocity(gravity_strength_);
      player.Iterate(holes_.front());

      if (CheckCollision(player))
        player.Kill(frame);

      if (player.GetPosition().y < 0) {
        player.Kill(frame);
        player.position_.y = 0;
      }
      if (player.GetPosition().y >= screen_height_) {
        player.Kill(frame);
        player.position_.y = screen_height_ - 3;
      }
    }
  }
  frame++;
}
bool Engine::CheckCollision(Player &player) {
  // check if the player ISN'T in range of barrier a.k.a. touches the pipe

  const int &player_x = player.position_.x;
  const int &player_y = player.position_.y;

  const int &hole_x = holes_.begin()->x;
  const int &hole_y = holes_.begin()->y;

  if (player_x + player_size_ < hole_x - (hole_width_ / 2) ||
      player_x - player_size_ > hole_x + (hole_width_ / 2))
    return false;

  if (player_y - player_size_ > hole_y - (hole_size_ / 2) &&
      player_y + player_size_ < hole_y + (hole_size_ / 2))
    return false;

  return true;

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
  return false;
}
const std::vector<Player> &Engine::GetPlayers() const { return players_; }
const std::vector<Coord> &Engine::GetHoles() const { return holes_; }
