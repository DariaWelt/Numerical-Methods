#ifndef INERP
#define INERP
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
  struct Tab_Fun {
    void* obj;
  };
   typedef struct Tab_Fun Table_Func_t;
  __declspec(dllexport) Table_Func_t* CreateTableFunc(double * a, double* y, double* y1, int _size);
  __declspec(dllexport) double* Hermit(double* valid, int size_v, Table_Func_t* trash);
  __declspec(dllexport) void PrintHermitPolynom(FILE* stream, Table_Func_t* trash);
#ifdef __cplusplus
}
#endif

#endif // !INERP