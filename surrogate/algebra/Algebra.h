/*
 * Algebra.h
 *
 *  Created on: 04/07/2012
 *      Author: krempser
 */

#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#include "math.h"
#include <iostream>
using namespace std;

#include "Eigen/Dense"
using namespace Eigen;

namespace opt {
namespace surrogate {
namespace algebra {

	class Algebra {
	public:
		static void printMatrix(double **V, int M, int N);
		static void transposeMatrix(double **V, int M, int N, double **T);
		static void multiplyMatrix(double **A, int MA, int NA, double **B, int MB, int NB, double **MULT);
		static void multiplyMatrixVector(double **A, int MA, int NA, double *V, int MV, double *R);
		static double distance(double *X1, double *X2, int N);
		static bool SymmetricMatrixInvert(double** V, int N);

		//with Eigen
		static double distance(MatrixXd X1, MatrixXd X2, int index);
		static double distance(MatrixXd X1, int index, MatrixXd X2, int index2);

		//Statistics
		static double normalDistribution(double v);
		static double normalDistribution(double v, double mu, double var);
		static double normalDensity(double v);
		static double normalDensity(double v, double mu, double var);
	};

} /* namespace algebra */
} /* namespace surrogate */
} /* namespace opt */
#endif /* ALGEBRA_H_ */
