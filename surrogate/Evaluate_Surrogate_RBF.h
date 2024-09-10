/*
 * Evaluate_Surrogate_RBF.h
 *
 *  Created on: 19/07/2012
 *      Author: krempser
 */

#ifndef EVALUATE_SURROGATE_RBF_H_
#define EVALUATE_SURROGATE_RBF_H_

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

class Evaluate_Surrogate_RBF : public Evaluate_Surrogate{
protected:
	double tal;
	MatrixXd C; // Coefficients
	KDTree *tree;
	double **centers;
	int dimension;
	double lastFitness;
	MatrixXd lastInversePhi;
	MatrixXd lastphi;
	double lastVariance;
public:
	int N;
	int M;
	int nCenters;

	Evaluate_Surrogate_RBF(Function *func);
	Evaluate_Surrogate_RBF(Function *func, double tal);

	double *getCoefficients();

	double weight(MatrixXd X, int index, int index2);
	double basis(double dist, double t);
	void fillW(MatrixXd X, MatrixXd &W, MatrixXd P);
	bool regress(double *Y, double **X, int M, int N, double *P); //P is the query point

	void fillW(MatrixXd X, MatrixXd &W);
	double weight(MatrixXd X, int index, double *Center);

	virtual ~Evaluate_Surrogate_RBF();

	virtual double calcFitness(IndividualPtr &ind);
	void insert(IndividualPtr ind);

	//Calc the error with the current approximation (current tal)
	double approximationError(double *Y, double **X, int M, int N, double **Centers);

	//Set a parameter to surrogate model
	virtual void setParam(string param, double value);
	virtual void setParam(string param, int value);

	double calcNewY(double *P, double **X);

	//Return the mean and variance of the model, if exists
	virtual double getMean();
	virtual double getVariance();

	//Calc and store the last phi value to last point
	virtual void calcLastphi(double *P, double **X);
	virtual void calcVariance(double *Y, double **X, int N, int M, double **Centers, double fit);

	//return the tal value
	double getTal();

	//Update evaluate info
	void update(Evaluate *eval);
};

} /* namespace surrogate */
} /* namespace opt */
#endif /* EVALUATE_SURROGATE_RBF_H_ */
