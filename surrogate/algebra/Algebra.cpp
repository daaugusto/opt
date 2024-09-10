/*
 * Algebra.cpp
 *
 *  Created on: 04/07/2012
 *      Author: krempser
 */

#include "Algebra.h"

//Normal distribution
#include "distribution/prob.hpp"

/*
   //Using boost... version >= 1.45
#include <boost/math/distributions/normal.hpp> //for normal distribution
using boost::math::normal; //typedef provides default type is double
#include <iomanip>
using std::setw; using std::setprecision;
#include <limits>
using std::numeric_limits;
*/

namespace opt {
namespace surrogate {
namespace algebra {

void Algebra::printMatrix(double **V, int M, int N){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			cout << " " << V[i][j];
		}
		cout << "\n";
	}
}

void Algebra::transposeMatrix(double **V, int M, int N, double **T){
	for(int c = 0 ; c < M ; c++ ){
		for(int d = 0 ; d < N ; d++ ){
			 T[d][c] = V[c][d];
		}
	}
}

void Algebra::multiplyMatrix(double **A, int MA, int NA, double **B, int MB, int NB, double **MULT){
	if (NA != MB){
		cout << "\n\n ERROR! NA != NB\n\n";
		return;
	}
	double sum = 0;
	for (int c = 0 ; c < MA ; c++ ){
		for (int d = 0 ; d < NB ; d++ ){
			for (int k = 0 ; k < MB ; k++ ){
				sum = sum + A[c][k]*B[k][d];
			}
			MULT[c][d] = sum;
			sum = 0;
		}
	}
}

void Algebra::multiplyMatrixVector(double **A, int MA, int NA, double *V, int MV, double *R){
	if (NA != MV){
		cout << "\n\n ERROR! NA != NV\n\n";
		return;
	}
	for (int i = 0; i < MA; i++){
		R[i] = 0.0;
		for(int j = 0; j < MV; j++){
			R[i] += A[i][j] * V[j];
		}
	}
}

double Algebra::distance(double *X1, double *X2, int N){
	double sum = 0.0;
	for (int i = 0; i < N; i++){
		sum += pow(X1[i] - X2[i], 2);
	}
	return sqrt(sum);
}

bool Algebra::SymmetricMatrixInvert(double** V, int N){
	double* t = new double[N];
	double* Q = new double[N];
	double* R = new double[N];
	double AB;
	int K, L, M;

	// Invert a symetric matrix in V
	for (M = 0; M < N; M++)
	  R[M] = 1;
	K = 0;
	for (M = 0; M < N; M++)
	{
	  double Big = 0;
	  for (L = 0; L < N; L++)
	  {
		  AB = fabs(V[L][L]);
		  if ((AB > Big) && (R[L] != 0))
		  {
			  Big = AB;
			  K = L;
		  }
	  }
	  if (Big == 0)
	  {
		  return false;
	  }
	  R[K] = 0;
	  Q[K] = 1 / V[K][K];
	  t[K] = 1;
	  V[K][K] = 0;
	  if (K != 0)
	  {
		  for (L = 0; L < K; L++)
		  {
			  t[L] = V[L][K];
			  if (R[L] == 0)
				  Q[L] = V[L][K] * Q[K];
			  else
				  Q[L] = -V[L][K] * Q[K];
			  V[L][K] = 0;
		  }
	  }
	  if ((K + 1) < N)
	  {
		  for (L = K + 1; L < N; L++)
		  {
			  if (R[L] != 0)
				  t[L] = V[K][L];
			  else
				  t[L] = -V[K][L];
			  Q[L] = -V[K][L] * Q[K];
			  V[K][L] = 0;
		  }
	  }
	  for (L = 0; L < N; L++)
		  for (K = L; K < N; K++)
			  V[L][K] = V[L][K] + t[L] * Q[K];
	}
	M = N;
	L = N - 1;
	for (K = 1; K < N; K++)
	{
	  M = M - 1;
	  L = L - 1;
	  for (int J = 0; J <= L; J++)
		  V[M][J] = V[J][M];
	}

	delete [] t;
	delete [] Q;
	delete [] R;
	return true;
}

double Algebra::distance(MatrixXd X1, MatrixXd X2, int index){
	double sum = 0.0;
	for (int i = 0; i < X2.rows(); i++){
		sum += pow((float)(X1(index, i) - X2(i)), 2);
	}
	return sqrt(sum);
}

double Algebra::distance(MatrixXd X1, int index, MatrixXd X2, int index2){
	double sum = 0.0;
	for (int i = 0; i < X2.rows(); i++){
		sum += pow((float)(X1(index, i) - X2(index2, i)), 2);
	}
	return sqrt(sum);
}

//Statistics
//cdf -- pnorm (prob. acumulada), pdf -- dnorm (densidade prob.)
double Algebra::normalDistribution(double v){
/*	normal s;

	setprecision(17);
	return cdf(s, v);
*/
}

double Algebra::normalDistribution(double v, double mu, double var){
/*	normal s(mu, var);

	setprecision(17);
	return cdf(s, v);
*/

	double x = (v)/var;
//	double p = 1/(sqrt(2*M_PI))*exp(-0.5*(x*x));
//	cout << "\nv:" << v << " mu: " << mu << "var:" << var << " x: " << x << " p: " << p;
//	cout << "\n pdf: " << normal_pdf(x, 0, 1) << " cdf: " << normal_cdf(x, 0, 1) << " ";

	return normal_cdf(x, 0, 1);

}

double Algebra::normalDensity(double v){
/*
	normal s;
	setprecision(17);
	return pdf(s, v);
*/
}

double Algebra::normalDensity(double v, double mu, double var){
/*
	normal s(mu, var);
	setprecision(17);

	cout << "\npdf: " << pdf(s, v) << " normal_pdf: " << normal_pdf(v, mu, var);

	return pdf(s, v);
*/
	double x = (v)/var;
	return normal_pdf(x, 0, 1);
}

} /* namespace algebra */
} /* namespace surrogate */
} /* namespace opt */
