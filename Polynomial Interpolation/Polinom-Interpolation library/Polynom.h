#ifndef POL
#define POL
#include <vector>
class Polynom {
  std::vector<double> weight;
public:
  Polynom(std::vector<double> weight);
  ~Polynom();
  Polynom operator=(Polynom const& m);
  Polynom operator+(Polynom const& P);
  Polynom operator*(Polynom const& P);
  Polynom operator*(double k);
  Polynom operator/(double k);

  //печать полинома в виде a_n*x^n + a_n-1*x^n-1 + ... + a_1*x + a_0
  void print(FILE* stream);
  double get_val(double x);
  std::vector<double> get_weights();
};
#endif // !POL