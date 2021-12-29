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

sf::Font View::font_;

View::View(const Engine &engine) {
  if (!font_.loadFromFile("../window/Georama-Medium.ttf"))
    throw "bad file";

  for (auto &player : engine.GetPlayers()) {
    players_.emplace_back(engine.player_size_);
    players_.back().setPosition(player.position_.x, player.position_.y);
    players_.back().setFillColor(GenColor());
  }
  for (auto &pipe : engine.GetHoles()) {
    sf::Vector2f size{(float)engine.hole_width_, (float)engine.screen_height_};

    sf::Vector2f lower_pipe_leftmost_corner{
        (float)pipe.x - (engine.hole_width_ / 2),
        (float)pipe.y + (engine.hole_size_ / 2)};

    pipes_.emplace_back(size);
    pipes_.back().setPosition(lower_pipe_leftmost_corner);
    pipes_.back().setFillColor(sf::Color(0, 255, 255));

    sf::Vector2f upper_pipe_leftmost_corner{
        (float)pipe.x - ((float)engine.hole_width_ / 2),
        (float)pipe.y - ((float)engine.hole_size_ / 2) -
            (float)engine.screen_height_};

    pipes_.emplace_back(size);
    pipes_.back().setPosition(upper_pipe_leftmost_corner);
    pipes_.back().setFillColor(sf::Color(0, 255, 255));
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

  for (auto &i : pipes_)
    window.draw(i);

  for (auto &i : players_)
    window.draw(i);

//  for (auto &i : labels_)
//    window.draw(i);
}