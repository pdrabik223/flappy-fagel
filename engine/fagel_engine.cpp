//
// Created by piotr on 22/12/2021.
//

#include "fagel_engine.h"
Engine::Engine(int screen_width, int screen_height)
    : screen_height_(screen_height), screen_width_(screen_width) {}

Engine::Engine(int screen_width, int screen_height, const NeuralNet &prometheus)
    : screen_height_(screen_height), screen_width_(screen_width) {
  players_.emplace_back(Coord(50, screen_height_ / 2),
                        Coord(screen_width_, screen_width_), 0, prometheus);
  SpawnPlayers(prometheus);
}

void Engine::SpawnPlayers(const NeuralNet &prometheus) {
  players_.clear();
  players_.emplace_back(Coord(50, screen_height_ / 2),
                        Coord(screen_width_, screen_height_), 0, prometheus);

  for (unsigned int i = 1; i < no_players_; i++)
    players_.emplace_back(Coord(50, screen_height_ / 2),
                          Coord(screen_width_, screen_height_), i,
                          NextGen(prometheus));
}

void Engine::Iterate() {
  bool award_points = DeleteHole();
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
        player.Kill(frame_);

      if (player.GetPosition().y < 0) {
        player.Kill(frame_);
        player.position_.y = 0;
      }
      if (player.GetPosition().y >= screen_height_) {
        player.Kill(frame_);
        player.position_.y = screen_height_ - 3;
      }
      if (award_points && player.IsAlive())
        player.points_ = points_;
    }
  }
  frame_++;
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
}
const std::vector<Player> &Engine::GetPlayers() const { return players_; }
const std::vector<Coord> &Engine::GetHoles() const { return holes_; }
int Engine::GetPoints() const { return points_; }
int Engine::GetFrame() const { return frame_; }
