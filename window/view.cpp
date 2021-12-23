//
// Created by piotr on 24/10/2021.
//
#include "view.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <iostream>
#define PI 3.14159265
sf::Color GenColor() {
  const unsigned char kBottomEdge = 50;
  const unsigned char kUpperEdge = 200;

  return {
      static_cast<sf::Uint8>(rand() % (kUpperEdge - kBottomEdge) + kBottomEdge),
      static_cast<sf::Uint8>(rand() % (kUpperEdge - kBottomEdge) + kBottomEdge),
      static_cast<sf::Uint8>(rand() % (kUpperEdge - kBottomEdge) + kBottomEdge),
      90};
}

View::View(const Engine &engine) {
  for (auto &player : engine.GetPlayers()) {
    players_.emplace_back(engine.player_size_);
    players_.back().setFillColor(GenColor());
  }
  for (auto &pipe : engine.GetHoles()) {
    sf::Vector2f size{(float)engine.hole_width_, (float)engine.screen_height_};

    sf::Vector2f lower_pipe_leftmost_corner{
        (float)pipe.x - (engine.hole_width_ / 2),
        (float)pipe.y + (engine.hole_size_ / 2)};

    pipes_.emplace_back(lower_pipe_leftmost_corner);
    pipes_.back().setSize(size);
    pipes_.back().setFillColor(sf::Color(0, 255, 255));

    sf::Vector2f upper_pipe_leftmost_corner{
        (float)pipe.x - (engine.hole_width_ / 2),
        (float)pipe.y + (engine.hole_size_ / 2) - engine.screen_height_};

    pipes_.emplace_back(upper_pipe_leftmost_corner);
    pipes_.back().setSize(size);
    pipes_.back().setFillColor(sf::Color(0, 255, 255));
  }
}
void View::Draw(sf::RenderWindow &window) {
  for (auto &i : pipes_)
    window.draw(i);
  for (auto &i : players_)
    window.draw(i);
}