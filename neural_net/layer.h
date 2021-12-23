//
// Created by piotr on 16/12/2021.
//

#ifndef NEURAL_NETS_CPP_NEURAL_NET_LAYER_H_
#define NEURAL_NETS_CPP_NEURAL_NET_LAYER_H_

#include "../matrix/matrix.h"
#include <iostream>

class Layer {
public:
  explicit Layer(unsigned layer_size) {
    nodes_ = matrix::Matrix<double>(layer_size, 1);
    activated_nodes_ = matrix::Matrix<double>(layer_size, 1);
  }

protected:
  matrix::Matrix<double> nodes_;
  matrix::Matrix<double> activated_nodes_;
};

#endif // NEURAL_NETS_CPP_NEURAL_NET_LAYER_H_
