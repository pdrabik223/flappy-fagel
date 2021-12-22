//
// Created by piotr on 22/12/2021.
//

#include "engine.h"
Engine::Engine(unsigned int screen_height, unsigned int screen_width)
    : screen_height_(screen_height), screen_width_(screen_width),
      gravity_strength_(1), no_players_(1) {
  for (int i = 0; i < no_players_; i++) {
    players_.emplace_back(10, screen_height / 2, i);
  }
}
void Engine::Iterate() {
  for (auto player : players_) {
    player.AddVelocity(-gravity_strength_);
    player.Iterate();
  }
}
