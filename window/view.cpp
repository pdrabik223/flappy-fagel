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

sf::Font View::font_;
void Dot::Draw(sf::RenderWindow &window, const sf::Vector2f &screen_placement) {

  sf::CircleShape circle(radius);
  circle.setPointCount(30);

  switch (state) {
  case State::WHITE:
    circle.setFillColor(sf::Color::White);
    break;
  case State::BLACK:
    circle.setFillColor(sf::Color::Black);
    break;
  case State::FREE:
    return;
  }
  circle.setPosition({screen_placement.x, screen_placement.y});
  circle.setScale({1, 1});

  window.draw(circle);
}
const Coord &Dot::GetPlacement() const { return placement; }

//View::View(const Go &game) : shape_(game.GetSizeX(), game.GetSizeY()) {
//
//  if (!font_.loadFromFile("../sfml_window/Georama-Medium.ttf"))
//    throw "bad file";
//  dots_.reserve(game.GetSize());
//
//  for (int y = 0; y < shape_.y; y++)
//    for (int x = 0; x < shape_.x; x++)
//      dots_.push_back({{x, y}, game.Get({x}, {y})});
//}

void View::Draw(sf::RenderWindow &window) {
  window.clear({40, 40, 40});

  float dot_radius;

  dot_radius = (window.getSize().x / shape_.x < window.getSize().y / shape_.y
                    ? window.getSize().x / shape_.x
                    : window.getSize().y / shape_.y);

  dot_radius /= 15;

  sf::Vector2f dot_shift = {((float)window.getSize().x / (float)shape_.x),
                            ((float)window.getSize().y / (float)shape_.y)};

  sf::Vector2f frame_shift = {dot_shift.x / 2 - dot_radius * 2,
                              dot_shift.y / 2 - dot_radius * 2};

  int i = 0;
  for (auto dot : dots_) {

    sf::Vector2f placement = {
        (float)frame_shift.x + (dot.GetPlacement().x * dot_shift.x) +
            dot_radius,
        (float)frame_shift.y + (dot.GetPlacement().y * dot_shift.y) +
            dot_radius};

    dot.radius = dot_radius;

    dot.Draw(window, placement);
    //    DisplayLabel(i++, placement, dot_radius, dot.state ==
    //    Dot::State::OCCUPIED,
    //                 window);
  }
}
void View::DisplayLabel(int label, sf::Vector2f placement, float dot_radius,
                        bool is_occupied, sf::RenderWindow &window) {
  std::string raw_text = std::to_string(label);
  sf::Text text(raw_text, font_);

  text.setPosition(
      {placement.x + (dot_radius * 3), placement.y - (dot_radius * 3)});
  text.setCharacterSize(dot_radius * 3);
  //  text.setStyle(sf::Text::Bold);

  if (is_occupied)
    text.setFillColor(FOREGROUND_COLOR);
  else
    text.setFillColor(sf::Color::White);
  window.draw(text);
}
