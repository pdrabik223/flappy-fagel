//
// Created by piotr on 17/12/2021.
//

#ifndef CPPGO_SFML_WINDOW_COORD_H_
#define CPPGO_SFML_WINDOW_COORD_H_
struct Coord {
  Coord() : x(0), y(0) {}
  Coord(int x, int y) : x(x), y(y) {}
  int x;
  int y;
  size_t operator()(size_t width) const { return y * width + x; }
};
#endif // CPPGO_SFML_WINDOW_COORD_H_
