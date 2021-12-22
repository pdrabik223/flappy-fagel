//
// Created by piotr on 05/10/2021.
//

#ifndef COA_SFML_WINDOW_WINDOW_H_
#define COA_SFML_WINDOW_WINDOW_H_

#include <SFML/Window/Event.hpp>

#include "coord.h"
#include <mutex>
#include <queue>
#include <vector>
#include "view.h"

class Window {
 public:
  Window() = delete;
  Window(int width, int height);
  Window(const sf::Vector2<float> &position, int width, int height);
  Window(const Window &other);
  Window &operator=(const Window &other);
  View PopFrame();
  void PushFrame(const View &new_frame);


  int GetQueueSize();
  ~Window() {
    screen_thread_->join();
    delete screen_thread_;
  }
  void SetWindowLabel(const std::string &label);

 protected:

  /// main window loop
  void MainLoop();

  int width_;
  int height_;

  std::string current_window_title_ = "CoA";

  std::mutex event_queue_mutex_;
  std::queue<View> frame_queue_;
  std::thread *screen_thread_;
  int display_refresh_rate_ = 15;
  sf::Event event_;

  /// position of window on the screen
  sf::Vector2<float> position_;
};

#endif//COA_SFML_WINDOW_WINDOW_H_
