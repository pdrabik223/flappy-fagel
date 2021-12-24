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
  Engine(int screen_width, int screen_height);
  void Iterate();
  const std::vector<Player> &GetPlayers() const;
  const std::vector<Coord> &GetHoles() const;
  void DeleteHole() {
    if (holes_.empty())
      return;
    if (holes_.begin()->x < 45)
      holes_.erase(holes_.begin());
  }
  void AddHole() {

    if (holes_.size() * (hole_width_ + distance_between_holes_) > screen_width_)
      return;

    Coord new_hole;

    if (holes_.empty()) {
      new_hole.x = screen_width_;
      new_hole.y = screen_height_ / 2;
    } else {
      new_hole.x =
          holes_.back().x + (hole_width_ / 2) + distance_between_holes_;
      new_hole.y =
          holes_.back().y + (rand() % (hole_size_ * 4)) - (hole_size_ * 2);
    }
    holes_.push_back(new_hole);
  }

  int hole_size_ = 50;
  int hole_width_ = 20;
  int distance_between_holes_ = 120;

  int player_size_ = 10;

  int screen_height_;
  int screen_width_;

  double gravity_strength_ = 0.4;
  int jump_buffer_ = 15;

private:
   bool CheckCollision(Player &player);

protected:
  int frame = 0;
  unsigned no_players_;
  std::vector<Player> players_;
  std::vector<Coord> holes_;
};

#endif // FAGEL_ENGINE_FAGEL_ENGINE_H_
