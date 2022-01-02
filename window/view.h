//
// Created by piotr on 24/10/2021.
//

#ifndef THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
#define THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
#include "../fagel/fagel_engine.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
class View {
public:
  View() = default;
  explicit View(const FagelEngine &engine);
  View(const View &other) = default;
  View &operator=(const View &other) = default;

  virtual void Draw(sf::RenderWindow &window);
  std::vector<sf::CircleShape> players_;
  std::vector<sf::RectangleShape> obstacles_;
  std::vector<sf::Text> labels_;
  static sf::Font font_;
};
#endif // THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
