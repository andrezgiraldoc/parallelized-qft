#include <stdio.h>
#include <iostream>
#include <vector>
#include <complex>
#include "qregister.hpp"
#include <time.h>

using namespace std;

int main() {
  // QRegister qreg({{0,1}, {1,0}, {1/sqrt(2), 1/sqrt(2)}, {1/sqrt(2), -1/sqrt(2)}, {1/sqrt(2), {0,1/sqrt(2)}}});
  QRegister qreg({{1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}});
  vector <complex<double> > result;
  result = qreg.getStateVector();
  clock_t t; 
  t = clock();
  qreg.applyQFT();
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC;
  result = qreg.getStateVector();
  cout<<"Final states: "<<endl;
  for (int i = 0; i < result.size(); i++)
    cout<<"result["<<i<<"] = "<<result[i]<<endl;
  cout<<"Tiempo que se demoró ejecutándose: "<<time_taken<<endl; 
  return 0;
}