//
// Created by piotr on 22/12/2021.
//

#ifndef FAGEL_ENGINE_PLAYER_H_
#define FAGEL_ENGINE_PLAYER_H_
#include <utility>

#include "../window/coord.h"
#include "../neural_net/neural_net.h"
class Player {
public:
  Player(const Coord &position, unsigned id)
      : position_(position), unique_id_(id), is_alive_(true), velocity_(0),
        brain_(3, {9, 4}, 1) {
    brain_.FillRandom();
    brain_.GetActivationFunction(-1) = ActivationFunction::SIGMOID;
  }

  void Kill() { is_alive_ = false; }
  unsigned int GetUniqueId() const { return unique_id_; }
  bool IsAlive() const { return is_alive_; }
  const Coord &GetPosition() const { return position_; }
  double GetVelocity() const { return velocity_; }
  void AddVelocity(double vel) { velocity_ += vel; }
  int GetSize() const { return size_; }

  void Iterate(Coord next_hole_position) {
    if (Brain(next_hole_position))
      velocity_ += jump_height_;

    position_.y = position_.y + velocity_;
  }

  bool Brain(Coord next_hole_distance) {
    matrix::Matrix<double> input(3, 1);
    input.Get(0) = (double)next_hole_distance.x - position_.x;
    input.Get(1) = (double)next_hole_distance.y - position_.y;
    input.Get(2) = velocity_;
    return brain_.FeedForward(input)[0] > 0.5;
  }

protected:
  double jump_height_ = 10;
  int size_ = 10;
  NeuralNet brain_;
  unsigned unique_id_;
  bool is_alive_;
  Coord position_;
  double velocity_;
};

#endif // FAGEL_ENGINE_PLAYER_H_
