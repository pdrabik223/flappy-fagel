//
// Created by piotr on 19/11/2021.
//

#ifndef NEURAL_NETS_CPP_NEURTAL_NET_NEURALNET_H_
#define NEURAL_NETS_CPP_NEURTAL_NET_NEURALNET_H_

#include "linear_layer.h"
#include <fstream>
#include <string>

struct Nabla {
  Nabla() : weights(), biases() {}
  Nabla(const matrix::Matrix<matrix::Matrix<double>> &weights,
        const matrix::Matrix<matrix::Matrix<double>> &biases)
      : weights(weights), biases(biases) {}
  matrix::Matrix<matrix::Matrix<double>> weights;
  matrix::Matrix<matrix::Matrix<double>> biases;

  void operator+=(const Nabla &other) {

    if (weights.GetHeight() == 0) {
      weights = other.weights;
      biases = other.biases;
    } else {
      for (int i = 0; i < weights.GetHeight(); i++)
        weights.Get(i).Add(other.weights.Get(i));
      for (int i = 0; i < biases.GetHeight(); i++)
        biases.Get(i).Add(other.biases.Get(i));
    }
  }
  void operator/=(const int value) {
    for (int i = 0; i < weights.GetHeight(); i++)
      weights.Get(i).Div(value);
    for (int i = 0; i < biases.GetHeight(); i++)
      biases.Get(i).Mul(value);
  }
};

class NeuralNet {

public:
  /// \param hidden_layer_sizes array of  uint numbers that represent
  /// consecutive layer sizes
  NeuralNet(size_t input_layer_size,
            const std::vector<size_t> &hidden_layer_sizes,
            size_t output_layer_size);

  NeuralNet(size_t input_layer_size, size_t output_layer_size);

  NeuralNet(const NeuralNet &other) = default;
  NeuralNet(const std::string &path) { LoadFromFile(path); }

  /// sets all weights and biases to random value ranging from 0 to 1
  void FillRandom();

  void Show();

  matrix::Matrix<double> FeedForward(const matrix::Matrix<double> &input);

  Nabla PropagateBackwards(const matrix::Matrix<double> &error);

  void Update(Nabla nabla, double learning_rate);

  matrix::Matrix<double>
  CostFunction(const matrix::Matrix<double> &expected_output) const;
  matrix::Matrix<double>
  PowCostFunction(const matrix::Matrix<double> &expected_output) const;

  const matrix::Matrix<double> &Activations(PyId id) const;

  const matrix::Matrix<double> &Nodes(PyId id) const;
  matrix::Matrix<double> &Weights(PyId id);
  matrix::Matrix<double> &Biases(PyId id);

  ActivationFunction &GetActivationFunction(PyId id);

  Linear &GetLayer(unsigned layer_id) { return network_layers_[layer_id]; }

  size_t LayersCount() const { return network_layers_.size(); }

  void SaveToFile(const std::string &file_path);
  void LoadFromFile(const std::string &file_path);

protected:
  size_t input_layer_size_;
  matrix::Matrix<double> input_values_;
  std::vector<Linear> network_layers_;
};
static std::string ToString(ActivationFunction func) {
  switch (func) {
  case ActivationFunction::RELU:
    return "Relu";
  case ActivationFunction::SIGMOID:
    return "Sigmoid";
  case ActivationFunction::SOFTMAX:
    return "Softmax";
    break;
  }
}
#endif // NEURAL_NETS_CPP_NEURTAL_NET_NEURALNET_H_
