//
// Created by piotr on 22/12/2021.
//

#ifndef FAGEL_ENGINE_PLAYER_H_
#define FAGEL_ENGINE_PLAYER_H_
#include <utility>

#include "../neural_net/neural_net.h"
#include "../window/coord.h"

class Player {
public:
  Player(const Coord &position, unsigned id)
      : position_(position), unique_id_(id), brain_(3, {9, 4}, 1) {
    brain_.FillRandom();
    brain_.GetActivationFunction(-1) = ActivationFunction::SIGMOID;
  }
  Player(const Coord &position, const Coord &screen_size, unsigned id,
         const NeuralNet &father)
      : position_(position), unique_id_(id), brain_(father),
        screen_size_(screen_size) {}

  void Kill(int kill_frame) {
    kill_frame_ = kill_frame;
    is_alive_ = false;
  }
  unsigned int GetUniqueId() const { return unique_id_; }
  bool IsAlive() const { return is_alive_; }
  const Coord &GetPosition() const { return position_; }
  double GetVelocity() const { return velocity_; }
  const NeuralNet &GetBrain() const { return brain_; }
  void AddVelocity(double vel) {
    if (IsAlive())
      velocity_ += vel;
  }
  int GetSize() const { return size_; }

  void Iterate(Coord next_hole_position) {
    if (!IsAlive())
      return;

    if (current_jump_buffer_ <= 0) {
      if (Brain(next_hole_position)) {
        velocity_ = -jump_height_;
        current_jump_buffer_ = jump_buffer_length_;
      } else
        current_jump_buffer_--;
    } else
      current_jump_buffer_--;

    position_.y = position_.y + velocity_;
  }

  bool Brain(Coord next_hole) {
    matrix::Matrix<double> input(3, 1);

    //    input.Get(0) = (double)(position_.x) / (double)screen_size_.x;
    input.Get(0) = (double)(next_hole.x) / (double)screen_size_.x;

    input.Get(1) = (double)(position_.y) / (double)screen_size_.y;
    input.Get(2) = (double)(next_hole.y) / (double)screen_size_.y;

//    input.Get(3) = velocity_ / 100;

    return brain_.FeedForward(input)[0] > 0.5;
  }

  double jump_height_ = 9;
  int size_ = 10;
  Coord position_;
  int jump_buffer_length_ = 20;
  int kill_frame_ = 0;
  double velocity_ = 0;
  bool is_alive_ = true;

protected:
  Coord screen_size_;
  int current_jump_buffer_ = 0;
  NeuralNet brain_;
  unsigned unique_id_;
};

#endif // FAGEL_ENGINE_PLAYER_H_
