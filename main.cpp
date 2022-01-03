//
// Created by piotr on 22/12/2021.
//
#include "fagel/fagel_engine.h"
#include "neural_net.h"
#include "window.h"
#include <iostream>
#include <stdio.h>
#include <time.h>

std::string CurrentDateTime() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%d.%m.%Y-%H.%M.%S", &tstruct);

  return buf;
}

std::string GenName(const std::string &directory, int score) {
  std::string name = directory;
  //  auto end = std::chrono::system_clock::now();
  //  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  name += CurrentDateTime();
  //  name.erase(name.size() - 1);
  //  for (auto &i : name)
  //    if (i == ' ')
  //      i = '_';
  name += "-score-" + std::to_string(score);

  return name;
}

int main() {
  srand(1);

  //  NeuralNet deep_thot("../deep_thot");

  NeuralNet deep_thot(3, {9, 5}, 1);
  deep_thot.GetActivationFunction(0) = ActivationFunction::SIGMOID;
  deep_thot.GetActivationFunction(1) = ActivationFunction::SIGMOID;
  deep_thot.GetActivationFunction(2) = ActivationFunction::SIGMOID;

  Player best_fagel;
  Window screen(800, 800);
  for (int i = 1; i < 1500; i++) {
    FagelEngine game(800, 800);

    game.SpawnPlayers(deep_thot);

    while (game.CountLiveFagels() != 0 && game.GetPoints() < 100) {
      //      if (i > 500)
      screen.PushFrame(View(game));
      game.Iterate();
    }

    best_fagel = game.GetBestPlayer();
    deep_thot = best_fagel.GetBrain();

    std::clog << "iteration: " << i
              << " longest live: " << best_fagel.kill_frame_
              << " points earned: " << best_fagel.points_ << "\n";
    if (game.GetPoints() >= 100)
      break;
  }
  deep_thot.SaveToFile(GenName("../best_fagels/", best_fagel.points_));

  printf("yey");
  return 0;
}