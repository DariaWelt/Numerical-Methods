#include <stdio.h>
#include <math.h>
#include <locale.h>
#pragma warning (disable:4996)
#define N 15
#define ANSWER_ALG 0.471307533879952
#define ANSWER_TRAN -1.5553465556979733500
// Границы, в которых считаются корни
#define A_ALG 0.1
#define A_TRAN -1.6
#define B_ALG 0.5
#define B_TRAN -1.3

// определим функции
double f_alg(double x) {
  return 0.5 * pow(x, 4) + 4 * pow(x, 3) - 11 * pow(x, 2) + 2;
}
double f_tran(double x) {
  return 0.5 * pow(x, 2)  - sin(exp(x)) - 1;
}
double mod(double a) {
  if (a > 0)
    return a;
  else
    return -a;
}
double Dixotomy(int *iter, double e, double a, double b, double(*function)(double)) {
  double rez, c, f_a, f_b, f_c;
  int iterations = 0;
  while (b - a > 2 * e) {
    ++iterations;
    c = a + (b - a) / 2;
    f_a = function(a);
    f_b = function(b);
    f_c = function(c);
    if (f_a == 0) {
      *iter = iterations;
      return a;
    }
    if (f_b == 0) {
      *iter = iterations;
      return b;
    }
    if (f_c == 0) {
      *iter = iterations;
      return c;
    }
    if (f_c * f_a < 0) {
      b = c;
    }
    else {
      a = c;
    }
  }
  rez = a + (b - a) / 2;
  *iter = iterations;
  return rez;
}
double FalsePosition(int *iter, double e, double a, double b, double(*function)(double)) {
  double c = a, f_c;
  int iterations = 0;
  double f_a = function(a);
  double f_b = function(b);
  double rez = (a * f_b - b * f_a) / (f_b - f_a);
  while (mod(c - rez) > e) {
    c = rez;
    f_c = function(c);
    if (f_c * f_a < 0) {
      b = c;
      f_b = f_c;
    }
    else {
      a = c;
      f_a = f_c;
    }
    rez = (a * f_b - b * f_a) / (f_b - f_a);
    ++iterations;
  }
  *iter = iterations;
  return rez;
}
void Algorithm(FILE* stream, double e, double(*method)(int*, double, double, double, double(*function)(double)), double(*function)(double), double const cnstA, double const cnstB, double const cnstANSWER) {
  int iteration[N] = { 0 };
  double distance[N] = { 0 };
  double a = cnstA, b = cnstB, answer = 0;
  int count = 0;
  printf("НАЧАЛО 1\n");
  for (unsigned i = 0; i < N && b - 5 * e > cnstANSWER && a + 5 * e < cnstANSWER; i++) {
    if (mod(cnstANSWER - a) < 5 * e || mod(b - cnstANSWER) < 5 * e) {
      printf("%i. ОШИБКА - ВЫХОД ЗА ДОПУСТИМЫЕ ЗНАЧЕНИЯ\n", i + 1);
      break;
    }
    answer = method(&count, e, a, b, function);
    if (mod(answer - cnstANSWER) > e)
      printf("%i. ОШИБКА: e =  %f; a =  %f; b - a = %f; ответ %f; разница в ответах %f;\n", i + 1, e, a, b - a, answer, mod(answer - ANSWER_ALG));
    iteration[i] = count;
    distance[i] = b - a;
    a += mod((cnstANSWER - cnstA) / 15);
    b -= mod((cnstANSWER - cnstB) / 15);
  }
  printf("УСПЕШНО 1\n");
  for (int i = 0; i < N; i++) {
    printf("%i %.15lf\n", iteration[i], distance[i]);
  }
  for (int i = 0; i < N; i++) {
    fprintf(stream, "%i ", iteration[i]);
  }
  for (int i = 0; i < N; i++) {
    fprintf(stream, "%.15lf ", distance[i]);
  }


  a = cnstA;
  b = cnstB;
  e = 0.1;
  int iteration2[15] = { 0 };
  double epsilon[15] = { 0 };
  printf("НАЧАЛО 2\n");
  for (unsigned i = 0; i < 15; i++) {
    answer = method(&count, e, a, b, function);
    if (mod(answer - cnstANSWER) > e)
      printf("%i. ОШИБКА: e =  %f; a =  %f; b - a = %f; ответ %f; разница в ответах %f;\n", i + 1, e, a, b - a, answer, mod(answer - ANSWER_ALG));
    iteration2[i] = count;
    epsilon[i] = e;
    e *= 0.1;
  }
  printf("УСПЕШНО 2\n");
  for (int i = 0; i < 15; i++) {
    printf("%i %.15lf\n", iteration2[i], epsilon[i]);
  }
  for (int i = 0; i < 15; i++) {
    fprintf(stream, "%i ", iteration2[i]);
  }
  for (int i = 0; i < 15; i++) {
    fprintf(stream, "%.15lf ", epsilon[i]);
  }
}
int main(void) {
  FILE* file;
  double e = 1.e-15;
  setlocale(LC_CTYPE, "Russian");
  file = fopen("ALG_DIX.txt","w");
    Algorithm(file, e, Dixotomy, f_alg, A_ALG, B_ALG, ANSWER_ALG);
  fclose(file);
  file = fopen("ALG_FAL.txt","w");
    Algorithm(file, e, FalsePosition, f_alg, -1.5, 0.5, ANSWER_ALG);
  fclose(file);
  file = fopen("TRAN_DIX.txt","w");
    Algorithm(file, e, Dixotomy, f_tran, A_TRAN, B_TRAN, ANSWER_TRAN);
  fclose(file);
  file = fopen("TRAN_FAL.txt","w");
    Algorithm(file, e, FalsePosition, f_tran, A_TRAN, B_TRAN, ANSWER_TRAN);
  fclose(file);
  scanf("%lf", &e);
  return 0;
}
