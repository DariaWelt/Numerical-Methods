#include "Polynom.h"
Polynom::~Polynom() {
  weight.~vector();
}

Polynom::Polynom(std::vector<double> weight): weight(weight) {}

Polynom Polynom::operator=(Polynom const& m) {
  this->weight = m.weight;
  return *this;
}
Polynom Polynom::operator+(Polynom const& P) {
  Polynom result(this->weight);
  size_t size = P.weight.size();
  if (weight.size() < size) {
    result.weight.resize(size, 0);
  }
  for (size_t i = 0; i < size; ++i) {
    result.weight[i] += P.weight[i];
  }
  return result;
}
Polynom Polynom::operator*(Polynom const& P) {
  size_t size1 = weight.size();
  size_t size2 = P.weight.size();
  Polynom result(std::vector<double>(size1 + size2 - 1, 0));
  for (size_t i = 0; i < size1; ++i) {
    for (size_t j = 0; j < size2; ++j) {
      result.weight[i + j] += weight[i] * P.weight[j];
    }
  }
  return result;
}
Polynom Polynom::operator*(double k) {
  Polynom P(weight);
  for (size_t i = 0; i < weight.size(); ++i)
    P.weight[i] *= k;
  return P;
}
Polynom Polynom::operator/(double k) {
  Polynom P(weight);
  for(size_t i = 0; i < weight.size(); ++i)
    P.weight[i] /= k;
  return P;
}

void Polynom::print(FILE* stream) {
  int size = weight.size();
  for (int i = 0; i < size - 1; ++i) {
    fprintf(stream, "%.20lf * (x^(%i)) + ", weight[i], i);
  }
  fprintf(stream, "%.20lf * (x^(%i));", weight[size - 1], size - 1);
}
double Polynom::get_val(double x) {
  double res = 0;
  int size = weight.size();
  for (int i = 0; i < size; ++i) {
    res += weight[i] * pow(x, i);
  }
  return res;
}
std::vector<double> Polynom::get_weights() {
  return weight;
}