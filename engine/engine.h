//
// Created by piotr on 22/12/2021.
//

#ifndef FAGEL_ENGINE_ENGINE_H_
#define FAGEL_ENGINE_ENGINE_H_
#include "coord.h"
#include "player.h"
#include <vector>

class Engine {
public:
  Engine(unsigned int screen_height, unsigned int screen_width);
  void Iterate();

protected:
  double gravity_strength_;
  unsigned screen_height_;
  unsigned screen_width_;
  unsigned no_players_;
  std::vector<Player> players_;
};

#endif // FAGEL_ENGINE_ENGINE_H_
