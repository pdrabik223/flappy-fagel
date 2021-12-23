//
// Created by piotr on 22/12/2021.
//

#ifndef FAGEL_ENGINE_FAGEL_ENGINE_H_
#define FAGEL_ENGINE_FAGEL_ENGINE_H_
//#include "coord.h"
#include "player.h"
#include <vector>

class Engine {
public:
  Engine(int screen_height, int screen_width);
  void Iterate();
  const std::vector<Player> &GetPlayers() const;
  const std::vector<Coord> &GetHoles() const;
  void AddHole() {
    if (holes_.size() * (hole_width_ + distance_between_holes_) > screen_width_)
      return;
    Coord new_hole;
    new_hole.x = screen_width_ + hole_width_ / 2;

    if (holes_.empty())
      new_hole.y = screen_height_ / 2;

    else
      new_hole.y =
          holes_.back().y + (rand() % (hole_size_ * 4)) - (hole_size_ * 2);
    holes_.push_back(new_hole);
  }

  int hole_size_ = 30;
  int hole_width_ = 10;
  int distance_between_holes_ = 80;

  int player_size_ = 10;

  int screen_height_;
  int screen_width_;

private:
  static bool CheckCollision(const Player &player);

protected:
  double gravity_strength_;
  unsigned no_players_;
  std::vector<Player> players_;
  std::vector<Coord> holes_;
};

#endif // FAGEL_ENGINE_FAGEL_ENGINE_H_
