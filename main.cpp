//
// Created by piotr on 22/12/2021.
//
#include "fagel_engine.h"
#include "neural_net.h"
#include "window.h"
#include <iostream>

int main() {
  srand(1);

  NeuralNet deep_thot(3, {9, 4}, 1);
  deep_thot.GetActivationFunction(0) = ActivationFunction::SIGMOID;
  deep_thot.GetActivationFunction(1) = ActivationFunction::SIGMOID;
  deep_thot.GetActivationFunction(2) = ActivationFunction::SIGMOID;
  //  deep_thot.GetActivationFunction(3) = ActivationFunction::SIGMOID;

  //  deep_thot.FillRandom();

  double learning_rate = 0.01;
  Player best_fagel;

  Window screen(800, 800);
  for (int i = 1; i < 1500; i++) {
    Engine game(800, 800);
    //    if (i % 4 == 0)

    if (best_fagel.points_ > 1)
      game.learning_rate_ = learning_rate / pow(10, best_fagel.points_);
    //    else if (best_fagel.points_ > 1)
    //      game.learning_rate_ = learning_rate;
    //    else
    //      game.learning_rate_ = 0.1;

    game.SpawnPlayers(deep_thot);

    while (game.CountLiveFagels() != 0) {
      if (i > 50)
        screen.PushFrame(game);
      game.Iterate();
    }

    best_fagel = game.GetBestPlayer();
    deep_thot = best_fagel.GetBrain();

    std::clog << "iteration: " << i
              << " longest live: " << best_fagel.kill_frame_
              << " points earned: " << best_fagel.points_ << "\n";
    //    game.SpawnPlayers(deep_thot);
  }

  for (int i = 0; i < 100; i++) {
    if (i % 25 == 24)
      learning_rate /= 2.0;

    Engine game(800, 600, deep_thot);
    //    game.learning_rate_ = learning_rate;
    game.SpawnPlayers(deep_thot);

    while (game.CountLiveFagels() != 0) {
      //      screen.PushFrame(game);
      game.Iterate();
    }
    const Player &best_fagel = game.GetBestPlayer();
    std::clog << "iteration: " << i
              << " longest_live: " << best_fagel.kill_frame_ << "\n";
    deep_thot = best_fagel.GetBrain();
  }
  deep_thot.SaveToFile("../deep_thot");

  printf("yey");
  return 0;
}