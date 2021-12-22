//
// Created by piotr on 24/10/2021.
//

#ifndef THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
#define THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
//#include "../go.h"
#include "coord.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#define BACKGROUND_COLOR sf::Color(27, 29, 28) // good gray
//#define FOREGROUND_COLOR sf::Color(104,255,66) // good green
//#define FOREGROUND_COLOR sf::Color(0,255,255) //  good cyan
#define FOREGROUND_COLOR sf::Color(247, 56, 56) // good red

struct Dot {
  enum class State { WHITE, BLACK, FREE };
  //
  //  Dot(const Coord &placement, Go::Rock rock) : placement(placement) {
  //    switch (rock) {
  //
  //    case Go::Rock::WHITE:
  //      state = State::WHITE;
  //      break;
  //    case Go::Rock::BLACK:
  //      state = State::BLACK;
  //      break;
  //    case Go::Rock::NONE:
  //      state = State::FREE;
  //      break;
  //    }
  //  };

  Dot(const Dot &other) = default;
  Dot &operator=(const Dot &other) = default;

  const Coord &GetPlacement() const;
  void Draw(sf::RenderWindow &window, const sf::Vector2f &screen_placement);

  Coord placement;
  State state = State::FREE;
  float radius = 20;
};

class View {
public:
  View() = default;
  View(const View &other) = default;
  View &operator=(const View &other) = default;
  //  View(const Go &game);
  void Draw(sf::RenderWindow &window);
  void DisplayLabel(int label, sf::Vector2f placement, float dot_radius,
                    bool is_occupied, sf::RenderWindow &window);

protected:
  Coord shape_;
  std::vector<Dot> dots_;

  static sf::Font font_;
};
#endif // THELOCKSCREENQUESTION_SFML_WINDOW_VIEW_H_
