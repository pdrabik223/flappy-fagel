//
// Created by piotr on 21/11/2021.
//

#ifndef NEURAL_NETS_CPP_MATRIX_MATRIX_H_
#define NEURAL_NETS_CPP_MATRIX_MATRIX_H_
#include <cassert>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

struct PyId {
  PyId(int position) : id(position) {}

  int id;
  unsigned ConvertId(unsigned size) const {
    if (id < 0)
      return size + id;
    else
      return id;
  };
};

namespace matrix {

struct Shape {
  Shape(size_t height, size_t width);
  Shape() : width(0), height(0){};

  size_t height;
  size_t width;

  bool operator==(const Shape &rhs) const;
  bool operator!=(const Shape &rhs) const;

  friend std::ostream &operator<<(std::ostream &os, const Shape &shape);
  friend std::istream &operator>>(std::istream &in, Shape &shape) {

    in.ignore(8);
    in >> shape.height;
    in.ignore(7);
    in >> shape.width;

    return in;
  }
};

template <class T> class Matrix {

public:
  Matrix() : shape_(0, 0) { data_ = {}; };
  Matrix(size_t height, size_t width);
  explicit Matrix(const std::vector<std::vector<T>> &data);

  Matrix(const Matrix &) = default;
  Matrix &operator=(const Matrix &) = default;

  void Transpose();

  T &operator[](PyId i) {
    if (!IsVector())
      throw "only vectors can be accessed via this handle";
    return data_[ToInt(i.ConvertId(shape_.height), unsigned(0))];
  }

  /// access specific value by reference
  /// \param i the 'height' part
  /// \param j the 'width' part
  /// \return targeted value
  T &Get(PyId i, PyId j) {
    return data_[ToInt(i.ConvertId(shape_.height), j.ConvertId(shape_.width))];
  };

  /// access specific value by reference
  /// \param i the 'height' part
  /// \param j the 'width' part
  /// \return targeted value
  T Get(PyId i, PyId j) const {
    return data_[ToInt(i.ConvertId(shape_.height), j.ConvertId(shape_.width))];
  };

  /// access specific value by reference
  /// !if matrix an not be represented as a vector the function will result in
  /// error \param i the 'height' part \return targeted value
  T &Get(PyId i) {
    if (!IsVector())
      throw "only vectors can be accessed via this handle";
    return data_[ToInt(i.ConvertId(shape_.height), unsigned(0))];
  };

  /// access specific value by reference
  /// !if matrix an not be represented as a vector the function will result in
  /// error \param i the 'height' part \return targeted value
  T Get(PyId i) const {
    if (!IsVector())
      throw "only vectors can be accessed via this handle";
    return data_[ToInt(i.ConvertId(shape_.height), unsigned(0))];
  };
  /// access specific value by reference
  /// \param i the 'height' part
  /// \param j the 'width' part
  /// \return targeted value
  //  T &Get(size_t i, size_t j) { return data_[ToInt(i, j)]; };

  /// overrides every value in matrix and changes it to given val
  /// \param val the new state of every val in matrix
  void Fill(T val) {
    for (auto &number : data_)
      number = val;
  };

  /// overrides every value in matrix and changes it to 0
  void Clear() { Fill(T(0)); };

  size_t GetWidth() const;
  size_t GetHeight() const;
  const Shape &GetShape() const;

  const std::vector<T> &GetData() const;

  void Add(const T &other);
  void Add(const Matrix<T> &other);

  void Sub(const Matrix<T> &other);

  void Mul(const T &other);
  void Mul(const Matrix<T> &other);

  void Div(const T &other);
  bool operator==(const Matrix &rhs) const;
  bool operator!=(const Matrix &rhs) const;

  bool IsVector() const { return shape_.width == 1; }

  //  template <class T>
  std::vector<T> &RawData() { return data_; }

  void AppendToFile(std::fstream &os) {
    os << "shape_: " << shape_ << " data_: ";
    for (auto &i : data_)
      os << i << ' ';
  }
  void ReadFromFile(std::fstream &os) {
    os.ignore(9);
    os >> shape_;
    os.ignore(8);

    for (int i = 0; i < shape_.height; i++)
      for (int j = 0; j < shape_.width; j++) {
        T buffer;
        os >> buffer;
        data_.push_back(buffer);
      }
  }

  friend std::fstream &operator<<(std::fstream &os, const Matrix &matrix);
  friend std::fstream &operator>>(std::fstream &os, Matrix &matrix);

private:
  /// convert position in 2d space, to its 1D notation
  /// \param i the 'height' part
  /// \param j the 'width' part
  /// \return 1D conversion of given point
  size_t ToInt(int i, int j) const;

  /// convert position in 2d space, to its 1D notation
  /// \param i the 'height' part
  /// \param j the 'width' part
  /// \return 1D conversion of given point
  size_t ToInt(size_t i, size_t j) const;

protected:
  /// point a(0,0) is in left top corner, just like normal matrix
  /// width a.k.a. j part of a(i,j) symbol
  Shape shape_;
  std::vector<T> data_;
};

template <class T> size_t Matrix<T>::ToInt(int i, int j) const {
  assert(i >= 0 && j >= 0);
  assert(i < GetHeight() && j < GetWidth());
  return i * GetWidth() + j;
}

template <class T> size_t Matrix<T>::ToInt(size_t i, size_t j) const {
  assert(i < GetHeight() && j < GetWidth());
  return i * GetWidth() + j;
}
template <class T> size_t Matrix<T>::GetWidth() const { return shape_.width; }
template <class T> size_t Matrix<T>::GetHeight() const { return shape_.height; }

template <class T> const std::vector<T> &Matrix<T>::GetData() const {
  return data_;
}

template <class T>
Matrix<T>::Matrix(size_t height, size_t width) : shape_(height, width) {
  data_.reserve(width * height);
  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++)
      data_.push_back(T());
}
template <class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> &data)
    : shape_(data.size(), data.begin()->size()) {
  shape_.width = data.begin()->size();

  for (auto &i : data)
    if (i.size() != GetWidth())
      throw "passed data matrix must have correctly defined size";

  shape_.height = data.size();

  data_.reserve(GetWidth() * GetHeight());

  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++)
      data_.push_back(data[i][j]);
}

template <class T>
static Matrix<T> Add(const Matrix<T> &matrix_a, const T &value) {
  Matrix<T> addition(matrix_a);
  for (int i = 0; i < matrix_a.GetHeight(); i++)
    for (int j = 0; j < matrix_a.GetWidth(); j++)
      addition.Get(i, j) += value;
  return addition;
}

template <class T> void Matrix<T>::Add(const T &other) {
  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++)
      Get(i, j) += other;
}

template <class T>
static Matrix<T> Add(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b) {
  if (matrix_a.GetWidth() != matrix_b.GetWidth())
    throw "incorrect matrix shape";

  if (matrix_a.GetHeight() != matrix_b.GetHeight())
    throw "incorrect matrix shape";
  Matrix<T> addition(matrix_a);
  for (int i = 0; i < matrix_a.GetHeight(); i++)
    for (int j = 0; j < matrix_a.GetWidth(); j++)
      addition.Get(i, j) += matrix_b.Get(i, j);
  return addition;
}
template <class T>
static Matrix<T> Sub(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b) {

  if (matrix_a.GetWidth() != matrix_b.GetWidth() ||
      matrix_a.GetHeight() != matrix_b.GetHeight())
    throw "incorrect matrix shape";

  Matrix<T> addition(matrix_a);

  for (int i = 0; i < addition.GetHeight(); i++)
    for (int j = 0; j < addition.GetWidth(); j++)
      addition.Get(i, j) -= matrix_b.Get(i, j);

  return addition;
}

template <class T> void Matrix<T>::Add(const Matrix<T> &other) {
  if (other.shape_ != shape_)
    throw "incorrect vector shape";

  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++)
      Get(i, j) += other.Get(i, j);
}

template <class T> void Matrix<T>::Sub(const Matrix<T> &other) {
  if (GetShape() != other.GetShape())
    throw "incorrect matrix shape";

  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++)
      Get(i, j) -= other.Get(i, j);
}

template <class T> void Matrix<T>::Mul(const T &other) {
  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++)
      Get(i, j) *= other;
}

template <class T> void Matrix<T>::Mul(const Matrix<T> &other) {
  if (GetWidth() != other.GetHeight())
    throw "incorrect matrix sizes";

  Matrix<T> multiplication(GetHeight(), other.GetWidth());

  for (int i = 0; i < multiplication.GetHeight(); i++)
    for (int j = 0; j < multiplication.GetWidth(); j++) {
      for (int k = 0; k < GetWidth(); k++)
        multiplication.Get(i, j) += Get(i, k) * other.Get(k, j);
    }
  *this = multiplication;
}

template <class T>
static Matrix<T> Mul(const Matrix<T> &matrix_a, const Matrix<T> &matrix_b) {
  if (matrix_a.GetWidth() != matrix_b.GetHeight())
    throw "incorrect matrix sizes";

  Matrix<T> multiplication(matrix_a.GetHeight(), matrix_b.GetWidth());

  for (int i = 0; i < multiplication.GetHeight(); i++)
    for (int j = 0; j < multiplication.GetWidth(); j++) {
      for (int k = 0; k < matrix_a.GetWidth(); k++)
        multiplication.Get(i, j) += matrix_a.Get(i, k) * matrix_b.Get(k, j);
    }
  return multiplication;
}
template <class T>
static Matrix<T> Mul(const Matrix<T> &matrix_a, const T &value) {

  Matrix<T> multiplication(matrix_a);

  for (int i = 0; i < multiplication.GetHeight(); i++)
    for (int j = 0; j < multiplication.GetWidth(); j++) {
      multiplication.Get(i, j) *= value;
    }
  return multiplication;
}

template <class T> bool Matrix<T>::operator==(const Matrix &rhs) const {
  return GetWidth() == rhs.GetWidth() && GetHeight() == rhs.GetHeight() &&
         data_ == rhs.data_;
}
template <class T> bool Matrix<T>::operator!=(const Matrix &rhs) const {
  return !(rhs == *this);
}
template <class T> void Matrix<T>::Transpose() {

  auto copy(*this);

  std::swap(shape_.width, shape_.height);
  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++) {
      Get(i, j) = copy.Get(j, i);
    }
}
template <class T> const Shape &Matrix<T>::GetShape() const { return shape_; }
template <class T> void Matrix<T>::Div(const T &other) {
  for (int i = 0; i < GetHeight(); i++)
    for (int j = 0; j < GetWidth(); j++)
      Get(i, j) /= other;
}
template <class T>
std::fstream &operator<<(std::fstream &os, const matrix::Matrix<T> &matrix) {
  os << "shape_: " << matrix.shape_ << " data_: ";
  for (auto &i : matrix.data_)
    os << i << ' ';

  return os;
}
template <class T>
std::fstream &operator>>(std::fstream &os, matrix::Matrix<T> &matrix) {
  os.ignore(9);
  os >> matrix.shape_;
  os.ignore(8);

  for (int i = 0; i < matrix.shape_.height; i++)
    for (int j = 0; j < matrix.shape_.width; j++) {
      T buffer;
      os >> buffer;
      matrix.data_.push_back(buffer);
    }
  return os;
}

template <class T> matrix::Matrix<T> Transpose(const matrix::Matrix<T> &other) {
  matrix::Matrix<T> transposed_matrix(other);
  transposed_matrix.Transpose();
  return transposed_matrix;
}

template <class T>
static matrix::Matrix<T> HadamardProduct(const matrix::Matrix<T> &vector_a,
                                         const matrix::Matrix<T> &vector_b) {

  if (!vector_a.IsVector())
    throw "incorrect vector shape";

  if (!vector_b.IsVector())
    throw "incorrect vector shape";

  if (vector_a.GetHeight() != vector_b.GetHeight())
    throw "incorrect vector dimensions";

  matrix::Matrix<T> hadamard_product(vector_b.GetHeight(), vector_a.GetWidth());

  for (int i = 0; i < hadamard_product.GetHeight(); i++)
    for (int j = 0; j < hadamard_product.GetWidth(); j++)
      hadamard_product.Get(i, j) = vector_a.Get(i, j) * vector_b.Get(i, j);

  return hadamard_product;
}

template <class T>
static matrix::Matrix<T> ConvertToMatrix(const std::vector<T> &vector) {

  matrix::Matrix<T> matrix(vector.size(), 1);
  matrix.RawData() = vector;

  return matrix;
}

} // namespace matrix
template <class T> static std::string ToString(const matrix::Matrix<T> &other) {
  std::string output = "[[";

  for (int i = 0; i < other.GetHeight(); i++) {
    for (int j = 0; j < other.GetWidth(); j++) {

      if (j < other.GetWidth() - 1)
        output += std::to_string(other.Get(i, j)) + ", ";
      else
        output += std::to_string(other.Get(i, j)) + "]";
    }
    if (i < other.GetHeight() - 1)
      output += ",\n[";
  }
  output += ']';

  return output;
}

template <class T> static std::string ToString(const std::vector<T> &other) {
  std::string output = "[";

  for (int j = 0; j < other.size(); j++)
    if (j < other.size() - 1)
      output += std::to_string(other[j]) + ", ";
    else
      output += std::to_string(other[j]);

  output += "]";

  return output;
}
template <class T> T Sum(matrix::Matrix<T> &target) {
  T sum = 0.0;
  for (auto i : target.RawData())
    sum += abs(i);
  return sum;
}
#endif // NEURAL_NETS_CPP_MATRIX_MATRIX_H_
