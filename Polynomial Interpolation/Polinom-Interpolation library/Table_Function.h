#ifndef TFunc
#include "Polynom.h"
#include <vector>
using namespace std;
class Table_Function {
  vector<double> x;   //узлы 
  vector<double> f_x;   
  vector<double> f1_x; //значения в производной функции
  const size_t size;

  Polynom lag_j(size_t j);
  Polynom lag_j_2(size_t j);
  Polynom phi(size_t j);
  Polynom psi(size_t j);
  double h_procces(double number, FILE* stream);
public:
  Table_Function(const vector<double>& x, const vector<double>& y, const vector<double>& y1);
  Table_Function(double * x, double* y,  double* y1, int size);
  //Polynom Eitken();
  Polynom Hermit();
  vector<double> Hermit(vector<double> valid_x);
  void PrintHermit(FILE* stream);
};
#endif // !TFunc