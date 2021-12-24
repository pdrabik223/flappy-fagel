//
// Created by piotr on 19/11/2021.
//

#include "linear_layer.h"

Linear::Linear(size_t previous_layer_height, size_t layer_height,
               ActivationFunction activation_function)
    : weights_(layer_height, previous_layer_height), biases_(layer_height, 1),
      activation_function_(activation_function), nodes_(layer_height, 1) {}

void Linear::FillRandom() {

  for (int i = 0; i < biases_.GetHeight(); i++)
    for (int j = 0; j < biases_.GetWidth(); j++)
      biases_.Get(i, j) = ((double)rand() / (double)RAND_MAX) / 100.0;

  for (int i = 0; i < weights_.GetHeight(); i++)
    for (int j = 0; j < weights_.GetWidth(); j++)
      weights_.Get(i, j) = ((double)rand() / (double)RAND_MAX) / 100.0;
}

const matrix::Matrix<double> &Linear::GetNodes() const { return nodes_; }

matrix::Matrix<double> &Linear::GetWeights() { return weights_; }

matrix::Matrix<double> &Linear::GetBiases() { return biases_; }

matrix::Matrix<double> &
Linear::ApplyActivationFunction(const matrix::Matrix<double> &target_vector,
                                ActivationFunction function_type) {

  if (!target_vector.IsVector())
    throw "incorrect shape";

  activated_nodes_ = target_vector;
  switch (function_type) {
  case ActivationFunction::RELU:
    for (int i = 0; i < target_vector.GetHeight(); i++)
      activated_nodes_.Get(i) = Relu(target_vector.Get(i));
    break;

  case ActivationFunction::SIGMOID:
    for (int i = 0; i < target_vector.GetHeight(); i++)
      activated_nodes_.Get(i) = Sigmoid(target_vector.Get(i));
    break;

  case ActivationFunction::SOFTMAX:
    double sum = 0.0;
    for (int i = 0; i < target_vector.GetHeight(); i++)
      sum += exp(target_vector.Get(i));
    if (sum == 0)
      sum = 1;
    for (int i = 0; i < target_vector.GetHeight(); i++)
      activated_nodes_.Get(i) = exp(activated_nodes_.Get(i)) / sum;

    break;
  }

  return activated_nodes_;
}
double Linear::Relu(double val) {
  if (val <= 0)
    return 0;
  else
    return val;
}

const matrix::Matrix<double> &Linear::GetActivatedNodes() const {
  return activated_nodes_;
}
matrix::Matrix<double>
Linear::ApplyReluDerivative(const matrix::Matrix<double> &vector_a) {

  if (!vector_a.IsVector())
    throw "incorrect vector shape";

  matrix::Matrix<double> solution(vector_a.GetHeight(), 1);

  for (int i = 0; i < vector_a.GetHeight(); i++)
    for (int j = 0; j < vector_a.GetWidth(); j++)
      solution.Get(i, j) = (Linear::ReluDerivative(vector_a.Get(i, j)));

  return solution;
}
matrix::Matrix<double>
Linear::ApplySigmoidDerivative(const matrix::Matrix<double> &vector_a) {

  if (!vector_a.IsVector())
    throw "incorrect vector shape";

  matrix::Matrix<double> solution(vector_a.GetHeight(), 1);

  for (int i = 0; i < vector_a.GetHeight(); i++)
    for (int j = 0; j < vector_a.GetWidth(); j++)
      solution.Get(i, j) = (Linear::SigmoidDerivative(vector_a.Get(i, j)));

  return solution;
}
matrix::Matrix<double>
Linear::ApplyDerivative(const matrix::Matrix<double> &vector_a,
                        ActivationFunction activation_function) {
  switch (activation_function) {

  case ActivationFunction::RELU:
    return ApplyReluDerivative(vector_a);

  case ActivationFunction::SIGMOID:
    return ApplySigmoidDerivative(vector_a);

  case ActivationFunction::SOFTMAX:
    return vector_a;
  }
  return vector_a;
}
double Linear::ReluDerivative(double val) {
  if (val <= 0)
    return 0.0;
  else
    return 1.0;
}
double Linear::SigmoidDerivative(double val) {
  return Sigmoid(val) * (1 - Sigmoid(val));
}
double Linear::Sigmoid(double val) { return (1.0 - 1.0 / (1.0 + exp(val))); }

ActivationFunction &Linear::GetActivationFunction() {
  return activation_function_;
}
Linear::Linear(const matrix::Matrix<double> &weights,
               const matrix::Matrix<double> &biases,
               ActivationFunction activation_function)
    : activation_function_(activation_function), weights_(weights),
      biases_(biases), nodes_(weights_.GetHeight(), 1),
      activated_nodes_(weights_.GetHeight(), 1) {}
