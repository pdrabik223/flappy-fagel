//
// Created by piotr on 24/10/2021.
//

#ifndef THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
#define THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "../engine/fagel_engine.h"
class View {
public:
  View() = default;
  View(const Engine &engine);
  View(const View &other) = default;
  View &operator=(const View &other) = default;
  //  View(const Go &game);
  virtual void Draw(sf::RenderWindow &window);
  std::vector<sf::CircleShape> players_;
  std::vector<sf::RectangleShape> pipes_;

};
#endif // THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
