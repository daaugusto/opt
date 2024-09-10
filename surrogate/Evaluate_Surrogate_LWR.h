/*
 * Evaluate_Surrogate_LWR.h
 *
 *  Created on: 04/07/2012
 *      Author: krempser
 */

#ifndef EVALUATE_SURROGATE_LWR_H_
#define EVALUATE_SURROGATE_LWR_H_

#include "math.h"
#include "Evaluate_Surrogate.h"
#include "kdtree/KDTree.h"
#include "algebra/Algebra.h"
#include "algebra/Eigen/Dense"
#include "../base/Tools.h"
using namespace opt::surrogate;
using namespace opt::surrogate::kdtree;
using namespace opt::surrogate::algebra;
using namespace opt::base;
using namespace Eigen;

namespace opt {
namespace surrogate {

class Evaluate_Surrogate_LWR : public Evaluate_Surrogate{
protected:
	double tal;
	MatrixXd C; // Coefficients
	KDTree *tree;
	int dimension;
public:
	int N;
	int M;

	Evaluate_Surrogate_LWR(Function *func);
	Evaluate_Surrogate_LWR(Function *func, double tal);

	double *getCoefficients();

	double weight(MatrixXd X, int index, MatrixXd P);
	void fillW(MatrixXd X, MatrixXd &W, MatrixXd P);
	bool regress(double *Y, double **X, int M, int N, double *P); //P is the query point

	virtual ~Evaluate_Surrogate_LWR();

	virtual double calcFitness(IndividualPtr &ind);
	void insert(IndividualPtr ind);

	//Set a parameter to surrogate model
	virtual void setParam(string param, double value);
	virtual void setParam(string param, int value);

	double calcNewY(double *P);
};

} /* namespace surrogate */
} /* namespace opt */
#endif /* EVALUATE_SURROGATE_LWR_H_ */
