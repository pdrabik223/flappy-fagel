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
  Engine(int screen_width, int screen_height, const NeuralNet &prometheus);

  void Iterate();
  const std::vector<Player> &GetPlayers() const;
  const std::vector<Coord> &GetHoles() const;

  void SpawnPlayers(const NeuralNet &prometheus);
  bool DeleteHole() {
    if (holes_.empty())
      return false;
    if (holes_.begin()->x < 45) {
      holes_.erase(holes_.begin());
      points_++;
      return true;
    }
    return false;
  }

  NeuralNet NextGen(const NeuralNet &father) {
    NeuralNet next_gen(father);

    for (int i = 0; i < next_gen.LayersCount(); i++) {
      for (int x = 0; x < next_gen.Weights(i).GetHeight(); x++)
        for (int y = 0; y < next_gen.Weights(i).GetWidth(); y++)
          if (rand() % 2 == 0)
            next_gen.Weights(i).Get(x, y) +=
                ((double)rand() / (double)RAND_MAX) * learning_rate_;
          else
            next_gen.Weights(i).Get(x, y) -=
                ((double)rand() / (double)RAND_MAX) * learning_rate_;

      for (int x = 0; x < next_gen.Biases(i).GetHeight(); x++)
        if (rand() % 2 == 0)
          next_gen.Biases(i).Get(x) +=
              ((double)rand() / (double)RAND_MAX) * learning_rate_;
        else
          next_gen.Biases(i).Get(x) -=
              ((double)rand() / (double)RAND_MAX) * learning_rate_;
    }
    return next_gen;
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

      if (new_hole.y <= hole_size_)
        new_hole.y = hole_size_;
      else if (new_hole.y >= screen_height_ - hole_size_)
        new_hole.y = screen_height_ - hole_size_;
    }
    holes_.push_back(new_hole);
  }
  int CountLiveFagels() {
    int sum = 0;
    for (auto &p : players_)
      if (p.IsAlive())
        sum++;
    return sum;
  }

  Player GetBestPlayer() const {
    int best_player_id = 0;

    for (int i = 0; i < players_.size(); i++)
      if (players_[i].kill_frame_ > players_[best_player_id].kill_frame_)
        best_player_id = i;
    return players_[best_player_id];
  }
  int hole_size_ = 150;
  int hole_width_ = 5;
  int distance_between_holes_ = 305;

  int player_size_ = 10;

  int screen_height_;
  int screen_width_;

  double gravity_strength_ = 0.4;

  unsigned no_players_ = 1000;
  double learning_rate_ = 0.1;
  int GetPoints() const;
  int GetFrame() const;

private:
  bool CheckCollision(Player &player);

protected:
  int points_ = 0;
  int frame_ = 0;
  std::vector<Player> players_;
  std::vector<Coord> holes_;
};

#endif // FAGEL_ENGINE_FAGEL_ENGINE_H_
