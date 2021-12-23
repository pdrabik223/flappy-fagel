//
// Created by piotr on 19/11/2021.
//

#include "neural_net.h"

NeuralNet::NeuralNet(size_t input_layer_size,
                     const std::vector<size_t> &hidden_layer_sizes,
                     size_t output_layer_size)
    : input_layer_size_(input_layer_size) {

  network_layers_.emplace_back(input_layer_size, hidden_layer_sizes[0],
                               ActivationFunction::RELU);

  for (int i = 1; i < hidden_layer_sizes.size(); i++) {
    network_layers_.emplace_back(hidden_layer_sizes[i - 1],
                                 hidden_layer_sizes[i],
                                 ActivationFunction::RELU);
  }

  network_layers_.emplace_back(hidden_layer_sizes.back(), output_layer_size,
                               ActivationFunction::RELU);
}
NeuralNet::NeuralNet(size_t input_layer_size, size_t output_layer_size)
    : input_layer_size_(input_layer_size) {

  network_layers_.emplace_back(input_layer_size, output_layer_size,
                               ActivationFunction::RELU);
}

matrix::Matrix<double>
NeuralNet::FeedForward(const matrix::Matrix<double> &input) {

  input_values_ = input;

  matrix::Matrix<double> buffer(input);

  //  matrix::Matrix<double> input_matrix(input);

  for (auto &network_layer : network_layers_)
    buffer = network_layer.FeedForward(buffer);

  return buffer;
}
void NeuralNet::Show() {

  std::cout << "input layer size: " << input_layer_size_ << std::endl;

  for (int i = 0; i < LayersCount() - 1; i++) {
    network_layers_[i].Show();
    std::cout << std::endl;
  }

  std::cout << "output layer ";
  network_layers_.back().Show();
  std::cout << std::endl;
}

void NeuralNet::FillRandom() {
  for (auto &hidden_layer : network_layers_) {
    hidden_layer.FillRandom();
  }
}

// There are only two hard things in Computer Science:
//  cache invalidation and naming things.
//
//                                      -- Phil Karlton
Nabla NeuralNet::PropagateBackwards(const matrix::Matrix<double> &error) {

  matrix::Matrix<matrix::Matrix<double>> nabla_b(LayersCount(), 1);
  matrix::Matrix<matrix::Matrix<double>> nabla_w(LayersCount(), 1);

  //  matrix::Matrix<double> expected_matrix(matrix::ConvertToMatrix(error));

  // output layer
  matrix::Matrix<double> delta = HadamardProduct(
      error, Linear::ApplyDerivative(Nodes(-1), GetActivationFunction(-1)));
  nabla_b[-1] = delta;

  nabla_w[-1] = Mul(delta, Transpose(Activations(-2)));

  // hidden layers

  for (int l = 2; l <= LayersCount(); l++) {

    const matrix::Matrix<double> kSp =
        Linear::ApplyDerivative(Nodes(-l), GetActivationFunction(-l));

    delta = HadamardProduct(Mul(matrix::Transpose(Weights(1 - l)), delta), kSp);

    nabla_b[-l] = delta;

    nabla_w[-l] = Mul(delta, matrix::Transpose(Activations(-1 - l)));
  }

  return {nabla_w, nabla_b};
}

matrix::Matrix<double>
NeuralNet::CostFunction(const matrix::Matrix<double> &expected_output) const {

  matrix::Matrix<double> error(expected_output.GetHeight(), 1);

  error = Sub(Activations(-1), expected_output);

  return error;
}
matrix::Matrix<double> NeuralNet::PowCostFunction(
    const matrix::Matrix<double> &expected_output) const {
  matrix::Matrix<double> error(expected_output.GetHeight(), 1);

  error = Sub(Activations(-1), expected_output);
  matrix::Matrix<double> sign(error.GetHeight(), 1);
  for (int i = 0; i < error.GetHeight(); ++i) {
    if (error[i] < 0)
      sign[i] = -1;
    else
      sign[i] = 1;
  }
  error = matrix::HadamardProduct(error, error);
  error = matrix::HadamardProduct(error, sign);

  return error;
}
void NeuralNet::Update(Nabla nabla, double learning_rate) {
  // -------- apply changes -------

  for (int l = 1; l <= LayersCount(); l++) {

    Weights(-l).Sub(Mul(nabla.weights.Get(-l), learning_rate));

    Biases(-l).Sub(Mul(nabla.biases.Get(-l), learning_rate));
  }
}
const matrix::Matrix<double> &NeuralNet::Activations(PyId id) const {
  if (id.id == -LayersCount() - 1)
    return input_values_;
  return network_layers_[id.ConvertId(LayersCount())].GetActivatedNodes();
}
const matrix::Matrix<double> &NeuralNet::Nodes(PyId id) const {

  if (id.id == -LayersCount() - 1)
    return input_values_;
  return network_layers_[id.ConvertId(LayersCount())].GetNodes();
}
matrix::Matrix<double> &NeuralNet::Weights(PyId id) {

  return network_layers_[id.ConvertId(LayersCount())].GetWeights();
}
matrix::Matrix<double> &NeuralNet::Biases(PyId id) {

  return network_layers_[id.ConvertId(LayersCount())].GetBiases();
}
ActivationFunction &NeuralNet::GetActivationFunction(PyId id) {

  return network_layers_[id.ConvertId(LayersCount())].GetActivationFunction();
}
void NeuralNet::SaveToFile(const std::string &file_path) {
  std::fstream file;
  file.open(file_path + ".txt", std::ios::out);
  file << input_layer_size_ << "\n";
  file << LayersCount() << "\n";

  for (int i = 0; i < LayersCount(); i++) {
    network_layers_[i].GetWeights().AppendToFile(file);
    file << "\n";
    network_layers_[i].GetBiases().AppendToFile(file);
    file << "\n";
    file << (int)network_layers_[i].GetActivationFunction();
    file << "\n";
  }
  file.close();
}
void NeuralNet::LoadFromFile(const std::string &file_path) {
  std::fstream file;
  file.open(file_path + ".txt", std::ios::in);
  file >> input_layer_size_;
  input_values_ = matrix::Matrix<double>(input_layer_size_, 1);
  int network_layers_count;
  file >> network_layers_count;
  for (int i = 0; i < network_layers_count; i++) {
    matrix::Matrix<double> weights;
    matrix::Matrix<double> biases;
    int activation_function;

    weights.ReadFromFile(file);
    biases.ReadFromFile(file);
    file >> activation_function;
    network_layers_.emplace_back(weights, biases,
                                 ActivationFunction(activation_function));
  }
}
