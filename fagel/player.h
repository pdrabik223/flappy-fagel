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
  Player() : position_(), unique_id_(0), brain_(3, {9, 4}, 1){};
  Player(const Coord &position, unsigned id)
      : position_(position), unique_id_(id), brain_(3, {9, 4}, 1) {
    brain_.FillRandom();
    brain_.GetActivationFunction(-1) = ActivationFunction::SIGMOID;
  }
  Player(const Coord &position, const Coord &screen_size, unsigned id,
         const NeuralNet &father);

  void Kill(int kill_frame);
  unsigned int GetUniqueId() const { return unique_id_; }
  bool IsAlive() const { return is_alive_; }
  const Coord &GetPosition() const { return position_; }
  double GetVelocity() const { return velocity_; }
  const NeuralNet &GetBrain() const { return brain_; }
  void AddVelocity(double vel);
  int GetSize() const { return size_; }

  void Iterate(Coord next_hole_position);

  bool Brain(Coord next_hole);

  double jump_height_ = 10;
  int size_ = 10;
  Coord position_;
  int jump_buffer_length_ = 0;
  int kill_frame_ = 0;
  double velocity_ = 0;
  bool is_alive_ = true;
  int points_ = 0;

  unsigned unique_id_;

protected:
  Coord screen_size_;
  int current_jump_buffer_ = 0;
  NeuralNet brain_;
};

#endif // FAGEL_ENGINE_PLAYER_H_
