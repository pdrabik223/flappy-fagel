//
// Created by piotr on 22/12/2021.
//

#ifndef FAGEL_ENGINE_PLAYER_H_
#define FAGEL_ENGINE_PLAYER_H_
#include "coord.h"
class Player {
public:
  Player(const Coord &position, unsigned id)
      : position_(position), unique_id_(id), is_alive_(true), velocity_(0) {}

  void Kill() { is_alive_ = false; }
  unsigned int GetUniqueId() const { return unique_id_; }
  bool IsAlive() const { return is_alive_; }
  const Coord &GetPosition() const { return position_; }
  double GetVelocity() const { return velocity_; }
  void AddVelocity(double vel) { velocity_ += vel; }
  void Iterate(){}

protected:
  unsigned unique_id_;
  bool is_alive_;
  Coord position_;
  double velocity_;
};


#endif // FAGEL_ENGINE_PLAYER_H_
