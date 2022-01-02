//
// Created by piotr on 24/10/2021.
//
#include "view.h"
#include <SFML/Graphics/CircleShape.hpp>

#include <cmath>
#include <iostream>
sf::Color GenColor() {
  const unsigned char kBottomEdge = 50;
  const unsigned char kUpperEdge = 200;
  //  return sf::Color::Red;
  return {
      static_cast<sf::Uint8>(rand() % (kUpperEdge - kBottomEdge) + kBottomEdge),
      static_cast<sf::Uint8>(rand() % (kUpperEdge - kBottomEdge) + kBottomEdge),
      static_cast<sf::Uint8>(rand() % (kUpperEdge - kBottomEdge) +
                             kBottomEdge)};
}
sf::Color Rainbow(float value, float max_value) {

  int witch_third = value / (max_value / 3.0);

  double height_in_radians;
  switch (witch_third) {
  case 0:
    height_in_radians = value * 3.1415 / (max_value / 3) / 2;

    return sf::Color(cos(height_in_radians) * 255, sin(height_in_radians) * 255,
                     0);
  case 1:
    value -= max_value / 3;
    height_in_radians = value * 3.1415 / (max_value / 3) / 2;
    return sf::Color(0, cos(height_in_radians) * 255,
                     sin(height_in_radians) * 255);

  case 2:
    value -= 2 * max_value / 3;
    height_in_radians = value * 3.1415 / (max_value / 3) / 2;
    return sf::Color(sin(height_in_radians) * 255, 0,
                     cos(height_in_radians) * 255);
  }

  return {255, 0, 0};
}

sf::Font View::font_;

View::View(const FagelEngine &engine) {
  if (!font_.loadFromFile("../window/Georama-Medium.ttf"))
    throw "bad file";

  for (auto &player : engine.GetPlayers()) {
    players_.emplace_back(engine.player_size_);
    players_.back().setPosition(player.position_.x, player.position_.y);
    players_.back().setFillColor(Rainbow(player.unique_id_,engine.no_players_));
  }
  for (auto &pipe : engine.GetHoles()) {
    sf::Vector2f size{(float)engine.hole_width_, (float)engine.screen_height_};

    sf::Vector2f lower_pipe_leftmost_corner{
        (float)pipe.x - (engine.hole_width_ / 2),
        (float)pipe.y + (engine.hole_size_ / 2)};

    obstacles_.emplace_back(size);
    obstacles_.back().setPosition(lower_pipe_leftmost_corner);
    obstacles_.back().setFillColor(sf::Color(0, 255, 255));

    sf::Vector2f upper_pipe_leftmost_corner{
        (float)pipe.x - ((float)engine.hole_width_ / 2),
        (float)pipe.y - ((float)engine.hole_size_ / 2) -
            (float)engine.screen_height_};

    obstacles_.emplace_back(size);
    obstacles_.back().setPosition(upper_pipe_leftmost_corner);
    obstacles_.back().setFillColor(sf::Color(0, 255, 255));
  }

  std::string raw_test = std::to_string(engine.GetPoints());

  sf::Text text(raw_test, font_);
  text.setCharacterSize(30);
  text.setPosition((float)engine.screen_width_ - 100, 5);
  text.setFillColor(sf::Color::White);

  labels_.push_back(text);
}
void View::Draw(sf::RenderWindow &window) {
  window.clear(sf::Color(28, 28, 28));

  for (auto &i : obstacles_)
    window.draw(i);

  for (auto &i : players_)
    window.draw(i);

//  for (auto &i : labels_)
//    window.draw(i);
}