#ifndef MatlabDllHeader
#pragma once
#define EXPORT_FUNC __declspec(dllexport)
typedef struct square_matrix_t square_matrix_t;
#ifdef __cplusplus
extern "C" {
#endif
  EXPORT_FUNC square_matrix_t* CreateMatrix(double* data, int n);
  EXPORT_FUNC double* Solve(square_matrix_t* matrix, double* B);
  EXPORT_FUNC void DeleteArray(void* ptr);
  EXPORT_FUNC void DestroyMatrix(square_matrix_t* matrix);
#ifdef __cplusplus
}
#endif
#endif //MatlabDllHeader