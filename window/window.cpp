//
// Created by piotr on 05/10/2021.
//

#include "window.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>

void Window::MainLoop() {
  sf::ContextSettings settings;
  //  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(width_, height_), "flappy fagel");

  window.setPosition(sf::Vector2i(position_.x, position_.y));
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  window.display();
  sf::Clock clock;
  is_open_ = true;
  while (window.isOpen()) {

    // check all the window's events that were triggered since the last
    // iteration of the loop
    while (window.pollEvent(event_)) {
      if (event_.type == sf::Event::Closed)
        window.close();
      else if (event_.type == sf::Event::KeyPressed) {
        if (event_.key.code == sf::Keyboard::Escape) {
          window.close();
        }
      }
    }

    if (clock.getElapsedTime().asMilliseconds() < display_refresh_rate_)
      continue;
    clock.restart();

    if (GetQueueSize() != 0) {
      PopFrame().Draw(window);
      window.display();
    } else
      std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  is_open_ = false;
}

Window::Window(int width, int height)
    : height_(height), width_(width), position_(0, 0) {
  screen_thread_ = new std::thread(&Window::MainLoop, this);
}
Window::Window(const sf::Vector2<float> &position, int width, int height)
    : height_(height), width_(width), position_(position) {
  screen_thread_ = new std::thread(&Window::MainLoop, this);
}

View Window::PopFrame() {
  View new_frame;
  const std::lock_guard<std::mutex> kLock(event_queue_mutex_);

  new_frame = frame_queue_.front();
  frame_queue_.pop();

  return new_frame;
}

void Window::PushFrame(const View &new_frame) {

  while (GetQueueSize() > 80)
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

  const std::lock_guard<std::mutex> kLock(event_queue_mutex_);
  frame_queue_.push(new_frame);
}
int Window::GetQueueSize() {
  const std::lock_guard<std::mutex> kLock(event_queue_mutex_);
  return frame_queue_.size();
}
void Window::SetWindowLabel(const std::string &label) {
  current_window_title_ = label;
}
Window &Window::operator=(const Window &other) {
  if (this == &other)
    return *this;
  width_ = other.width_;
  height_ = other.height_;
  current_window_title_ = other.current_window_title_;
  event_ = other.event_;
  frame_queue_ = other.frame_queue_;
  return *this;
}
Window::Window(const Window &other) {
  width_ = other.width_;
  height_ = other.height_;
  current_window_title_ = other.current_window_title_;
  event_ = other.event_;
  frame_queue_ = other.frame_queue_;
}
