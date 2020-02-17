#include "Table_Function.h"
#include <algorithm>

Table_Function::Table_Function(const vector<double>& x, const vector<double>& y, const vector<double>& y1):
  x(x), f_x(y), f1_x(y1), size(x.size()){}
Table_Function::Table_Function(double * a, double* y, double* y1, int _size): size(_size) {
  x = vector<double>(size, 0);
  f_x = vector<double>(size, 0);
  f1_x = vector<double>(size, 0);
  for (int i = 0; i < (int)size; ++i) {
    x[i] = a[i];
    f_x[i] = y[i];
    f1_x[i] = y1[i];
  }
}
/*/ необходимо протестить и исправить ошибки
void Table_Function::Eitken() {
  int size = x_train.size();
  if (size < 2)
    return;
  std::vector<std::vector<double>> memo(size - 1, std::vector<double>(size, 0));
  for (int i = 1; i < size; ++i) {
    for (int start = 0; start <= size - i - 1; ++start) {
      double koeff = (x_train[start + i] - x_train[start]);
      if (i == 1) {
        memo[start][0] = (func(x_train[start + 1]) - func(x_train[start])) / koeff;
        memo[start][1] = (func(x_train[start]) * x_train[start + 1] - func(x_train[start + 1]) * x_train[start]) / koeff;
      }
      else {
        for (int k = i; k > 0; --k) {
          memo[start][k] = (memo[start + 1][k - 1] - memo[start][k - 1] + x_train[start + i] * memo[start][k] - x_train[start] * memo[start + 1][k]) / koeff;
        }
        memo[start][0] = (x_train[start + i] * memo[start][0] - x_train[start] * memo[start + 1][0]) / koeff;
      }
    }
  }
  w = memo[0];
  //std::reverse(std::begin(w), std::end(w));
} */
Polynom Table_Function::lag_j(size_t j) {
  // ОШИБКА
  // но т.к. мы правильно юзаем формулу, то это никогда не произойдет
  // при отшлифовке программы можно добавить исключение
  if (j > size)
    return Polynom(vector<double>(0));
  Polynom result({1});
  for (size_t i = 0; i < size; ++i) {
    if (i != j)
      result = result * (Polynom({ -x[i], 1 }) / (x[j] - x[i]));
  }
  return result;
}
Polynom Table_Function::lag_j_2(size_t j) {
  Polynom P = lag_j(j);
  return P * P;
}
Polynom Table_Function::phi(size_t j) {
  double koeff = 1;
  Polynom P({ 2 * x[j], -2 });
  for (size_t i = 0; i < size; ++i) {
    if (i != j)
      koeff *= (x[j] - x[i]);
  }
  P = P / koeff;
  P = P + (Polynom({ 1 }));
  return P * lag_j_2(j);
}
Polynom Table_Function::psi(size_t j) {
  return lag_j_2(j) * Polynom({ -x[j], 1 });
}
Polynom Table_Function::Hermit() {
  Polynom result({});
  for (size_t i = 0; i < size; ++i) {
    Polynom P1 = psi(i);
    Polynom P2 = phi(i);
    P2 = P2 * f_x[i];
    P1 = P1 * f1_x[i];
    result = result + P1 + P2;
  }
  return result;
}
double Table_Function::h_procces(double number, FILE* stream) {
  double result = 0;
  for (size_t j = 0; j < size; ++j) {
    double lagr_j = 1;
    double alpha_j = 0;
    for (size_t i = 0; i < size; ++i) {
      if (i != j) {
        lagr_j *= (number - x[i]) / (x[j] - x[i]);
        alpha_j -= 2.0 / (x[j] - x[i]);
      }
    }
    if (stream != NULL) {
      fprintf(stream, "+ ( %.9lf .* (%.9lf .* (x - %.9lf) + 1) + %.9lf .* (x - %.9lf)) ", f_x[j], alpha_j, x[j], f1_x[j], x[j]);
      for (size_t i = 0; i < size; ++i) {
        if (i != j)
          fprintf(stream, " .* (x - %.9lf)/(%.9lf - %.9lf) ", x[i], x[j], x[i]);
      }
    }
    result += (f_x[j] * (alpha_j * (number - x[j]) + 1)  + f1_x[j] * (number - x[j])) * lagr_j * lagr_j;
  }
  return result;
}
vector<double> Table_Function::Hermit(vector<double> valid_x) {
  vector<double> res;
  for (auto number : valid_x) {
    res.push_back(h_procces(number, NULL));
  }
  return res;
}
void Table_Function::PrintHermit(FILE* stream) {
  fprintf(stream, "Hermit interpolation with %i points:\n", size);
  h_procces(0, stream);
  fprintf(stream, "\n END OF POLYNOM\n\n");
}
