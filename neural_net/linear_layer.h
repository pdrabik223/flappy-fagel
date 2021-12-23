//
// Created by piotr on 19/11/2021.
//

#ifndef NEURAL_NETS_CPP_NEURAL_NET_LINEAR_LAYER_H_
#define NEURAL_NETS_CPP_NEURAL_NET_LINEAR_LAYER_H_
#include "layer.h"
#include "../matrix/matrix.h"
#include <iostream>

enum class ActivationFunction { RELU, SIGMOID, SOFTMAX };

class Linear {
public:
  Linear(size_t previous_layer_height, size_t layer_height,
         ActivationFunction activation_function);

  Linear(const matrix::Matrix<double> &weights,
         const matrix::Matrix<double> &biases,
         ActivationFunction activation_function);

  Linear(const Linear &other) = default;
  Linear &operator=(const Linear &other) = default;

  /// feed forward values
  matrix::Matrix<double> FeedForward(const matrix::Matrix<double> &input) {
    nodes_ = matrix::Mul(weights_, input);
    nodes_.Add(biases_);
    activated_nodes_ = ApplyActivationFunction(nodes_, activation_function_);
    return activated_nodes_;
  };

  /// sets all weights and biases to random value ranging from 0 to 1
  void FillRandom();

  const matrix::Matrix<double> &GetNodes() const;

  void Show() {
    std::cout << " weights:\n"
              << ToString(weights_) << "\n biases:\n"
              << ToString(biases_) << std::endl;
  };

  matrix::Matrix<double> &GetBiases();

  matrix::Matrix<double> &GetWeights();
  const matrix::Matrix<double> &GetActivatedNodes() const;
  ActivationFunction &GetActivationFunction();

  static matrix::Matrix<double>
  ApplyDerivative(const matrix::Matrix<double> &vector_a,
                  ActivationFunction activation_function);

protected:
  static double Relu(double val);

  static double Sigmoid(double val);

  static double SigmoidDerivative(double val);
  static double ReluDerivative(double val);

  static matrix::Matrix<double>
  ApplySigmoidDerivative(const matrix::Matrix<double> &vector_a);

  static matrix::Matrix<double>
  ApplyReluDerivative(const matrix::Matrix<double> &vector_a);

  matrix::Matrix<double> &
  ApplyActivationFunction(const matrix::Matrix<double> &target_vector,
                          ActivationFunction function_type);

  ActivationFunction activation_function_;
  matrix::Matrix<double> weights_;
  matrix::Matrix<double> biases_;
  matrix::Matrix<double> nodes_;
  matrix::Matrix<double> activated_nodes_;
};

#endif // NEURAL_NETS_CPP_NEURAL_NET_LINEAR_LAYER_H_
