#define _USE_MATH_DEFINES
#include <stdio.h>
#include <iostream>
#include <vector>
#include <complex>
#include <map>
#include <bitset>

using namespace std;

#define THRESHOLD 0.000000001

class Qubit {
  public:
    vector< complex<double> > coefficients;
    Qubit();
    Qubit(complex<double>, complex<double>);
    vector< complex<double> > getCoefficients() { return coefficients; };
    vector<double> getProbabilities();
};

Qubit::Qubit() {
  coefficients.push_back(1);
  coefficients.push_back(0);
}

Qubit::Qubit(complex<double> a, complex<double> b) {
  coefficients.push_back(a);
  coefficients.push_back(b);
}

class QRegister {
  private:
    int qubitsNumber;
    vector<Qubit> qubits;
    vector <complex<double> > stateVector;
  public:
    QRegister();
    QRegister(int);
    QRegister(vector< vector <complex<double> > >);
    int getNumberQubits() { return qubitsNumber; };
    vector<Qubit> getQubits() { return qubits; };
    vector <complex<double> > getStateVector() { return stateVector; };
    void applyQFT();
    vector <complex<double> > tensorProduct(vector<Qubit>);
    void matrixProduct(vector< vector <complex<double> > >, vector <complex<double> >);
    // void matrixProduct(vector <complex<double> >, vector <complex<double> >);
};

QRegister::QRegister() {
  qubitsNumber = 1;
  Qubit qubit;
  qubits.push_back(qubit);
  stateVector.push_back(qubit.coefficients[0]);
  stateVector.push_back(qubit.coefficients[1]);
}

QRegister::QRegister(int n) {
  qubitsNumber = n;
  Qubit qubit;
  for (int i = 0; i < n; i++)
    qubits.push_back(qubit);
  stateVector = tensorProduct(qubits);
}

QRegister::QRegister(vector< vector <complex<double> > > qubitState) {
  qubitsNumber = qubitState.size();
  for (int i = 0; i < qubitsNumber; i++)
  {
    Qubit qubit(qubitState[i][0],qubitState[i][1]);
    qubits.push_back(qubit);
  }
  stateVector = tensorProduct(qubits);
}

void QRegister::applyQFT() {
  int n = qubitsNumber;
  int N = pow(2, n);
  vector<vector <complex<double> > > QFTGate(N, vector <complex<double> >(N));
  complex<double> wm;
  complex<double> imaginaryValue = {0,1};
  double angle = (2*M_PI)/pow(2,n);
  double realPart, imaginaryPart;
  #pragma omp parallel private(realPart, imaginaryPart, wm)
  {
    for (int i = 0; i < N; i++)
    {
      #pragma omp for
      for (int j = 0; j < N; j++)
      {
        realPart = cos(angle*i*j);
        imaginaryPart = sin(angle*i*j);
        if (abs(realPart) < THRESHOLD) realPart = 0;
        if (abs(imaginaryPart) < THRESHOLD) imaginaryPart = 0;
        wm = realPart + imaginaryValue*imaginaryPart;
        QFTGate[i][j] = (wm/sqrt(N));
      }
    }
  }
  matrixProduct(QFTGate, stateVector);
}

vector <complex<double> > QRegister::tensorProduct(vector<Qubit> initialStatesMatrix) {
  const int MAX_QUBITS = 50;
  int n=initialStatesMatrix.size();
  complex<double> val;
  vector <complex<double> > finalStatesVector;
  string binary;
  for (int i=0; i<pow(2,n); i++)
  {
    binary = bitset<MAX_QUBITS>(i).to_string();
    val={1,0};
    for (int j=0; j<n; j++)
      val=val*initialStatesMatrix[j].getCoefficients()[binary.at((MAX_QUBITS-n)+j)-'0'];
    finalStatesVector.push_back(val);
  }
  return finalStatesVector;
}

void QRegister::matrixProduct(vector< vector <complex<double> > > operatorsVector, vector <complex<double> > statesVector) {
  vector <complex<double> > resultVector(operatorsVector.size());
  complex<double> val;
  int i,j;
  #pragma omp parallel shared(val,operatorsVector,statesVector) private(i,j) 
  {
    #pragma omp for schedule(static)
    for (i=0; i<operatorsVector.size(); i++) {
      resultVector.at(i)={0,0};
      for (j=0; j<statesVector.size(); j++) {
        resultVector.at(i)=resultVector.at(i)+operatorsVector[i][j]*statesVector[j];
        if (abs(resultVector.at(i).real()) < THRESHOLD) resultVector.at(i).real(0);
        if (abs(resultVector.at(i).imag()) < THRESHOLD) resultVector.at(i).imag(0);
      }
    }
  }
  stateVector = resultVector;
}