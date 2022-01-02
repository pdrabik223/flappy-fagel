//
// Created by piotr on 22/12/2021.
//

#include "player.h"
Player::Player(const Coord &position, const Coord &screen_size, unsigned int id,
               const NeuralNet &father)
    : position_(position), unique_id_(id), brain_(father),
      screen_size_(screen_size) {}
void Player::Kill(int kill_frame) {
  kill_frame_ = kill_frame;
  is_alive_ = false;
}
void Player::AddVelocity(double vel) {
  if (IsAlive())
    velocity_ += vel;
}
void Player::Iterate(Coord next_hole_position) {
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
bool Player::Brain(Coord next_hole) {
  matrix::Matrix<double> input(3, 1);

  //    input.Get(0) = (double)(position_.x) / (double)screen_size_.x;
  input.Get(0) = (double)(next_hole.x) / (double)screen_size_.x;

  input.Get(1) = (double)(position_.y) / (double)screen_size_.y;
  input.Get(2) = (double)(next_hole.y - position_.y) / (double)screen_size_.y;

  //    input.Get(3) = velocity_ / 100;

  return brain_.FeedForward(input)[0] > 0.5;
}
