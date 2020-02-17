#include "Interpolation.h"
#include "Polynom.h"
#include "Table_Function.h"
#include <iostream>
void PrintHermitPolynom(FILE* stream, Table_Func_t* trash) {
  ((Table_Function*)trash->obj)->PrintHermit(stream);
}
double* Hermit(double* valid, int size_v, Table_Func_t* trash) {
  vector<double> x(size_v, 0);
  for (int i = 0; i < size_v; ++i)
    x[i] = valid[i];
  vector<double> result = ((Table_Function*)(trash->obj))->Hermit(x);
  double* e = new double[result.size()];
  for (int i = 0; i < result.size(); ++i)
    e[i] = result[i];
  return e;
}
Table_Func_t* CreateTableFunc(double * a, double* y, double* y1, int _size) {
  Table_Func_t* trash = new Table_Func_t;
  Table_Function* tableFunPtr = new Table_Function(a, y, y1, _size);
  trash->obj = (void*)tableFunPtr;
  return trash;
}