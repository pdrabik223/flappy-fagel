//
// Created by piotr on 22/12/2021.
//
#include "fagel_engine.h"
#include "window.h"
#include <iostream>

int main() {
  Window screen(800, 600);
  Engine game(800, 600);

  while (screen.IsOpen()) {
    screen.PushFrame(game);
//    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    game.Iterate();
  }
  printf("yey");
  return 0;
}