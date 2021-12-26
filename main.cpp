//
// Created by piotr on 22/12/2021.
//
#include "fagel_engine.h"
#include "neural_net.h"
#include "window.h"
#include <iostream>

int main() {
  srand(1);

  NeuralNet deep_thot(3, {4, 2}, 1);
  deep_thot.GetActivationFunction(0) = ActivationFunction::SIGMOID;
  deep_thot.GetActivationFunction(1) = ActivationFunction::SIGMOID;
  deep_thot.GetActivationFunction(2) = ActivationFunction::SIGMOID;
  //  deep_thot.GetActivationFunction(3) = ActivationFunction::SIGMOID;

  //  deep_thot.FillRandom();

  double learning_rate = 0.1;
  for (int i = 0; i < 1000; i++) {
    if (i % 250 == 249)
      learning_rate /= 2.0;

    Engine game(800, 600, deep_thot);
    game.learning_rate_ = learning_rate;
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
  Window screen(800, 600);

  for (int i = 0; i < 100; i++) {
    Engine game(800, 600, deep_thot);

    while (game.CountLiveFagels() != 0) {
      screen.PushFrame(game);
      game.Iterate();
    }
    deep_thot = game.GetBestPlayer().GetBrain();
    game.SpawnPlayers(deep_thot);
  }

  printf("yey");
  return 0;
}