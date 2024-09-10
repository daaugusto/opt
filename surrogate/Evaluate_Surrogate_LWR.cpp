/*
 * Evaluate_Surrogate_LWR.cpp
 *
 *  Created on: 04/07/2012
 *      Author: Eduardo Krempser
 */

#include "Evaluate_Surrogate_LWR.h"

namespace opt {
namespace surrogate {

Evaluate_Surrogate_LWR::Evaluate_Surrogate_LWR(Function *func):Evaluate_Surrogate(func) {
	this->tal = 0.5;
	this->dimension = func->getNDimensions();
	tree = new KDTree(this->dimension, func);
	this->setKey(SURROGATE_LWR);
}

Evaluate_Surrogate_LWR::Evaluate_Surrogate_LWR(Function *func, double tal):Evaluate_Surrogate(func){
	this->tal = tal;
	this->dimension = func->getNDimensions();
	tree = new KDTree(this->dimension, func);
	this->setKey(SURROGATE_LWR);
}

double Evaluate_Surrogate_LWR::weight(MatrixXd X, int index, MatrixXd P){
	double dist = Algebra::distance(X, P, index);
	double val = pow(dist, 2) / pow(tal, 2);
	return exp(- val);
}

void Evaluate_Surrogate_LWR::fillW(MatrixXd X, MatrixXd &W, MatrixXd P){
	for (int i = 0; i < X.rows(); i++){
		for(int j = 0; j < X.rows(); j++){
			if (i == j){
				W(i, j) = 0.5* ( weight(X, i, P)  );
			} else {
				W(i, j) = 0;
			}
		}
	}
}

bool Evaluate_Surrogate_LWR::regress(double *pY, double **pX, int M, int N, double *pP){ //P is the query point
	MatrixXd X(M, N), Y(M, 1), P(N, 1);

	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			X(i, j) = pX[i][j];
		}
		Y(i, 0) = pY[i];
	}
	for(int j = 0; j < N; j++){
		P(j, 0) = pP[j];
	}

	MatrixXd W(M, M);
	fillW(X, W, P);

	//Calc (X^t W X)
	MatrixXd Xt   = X.transpose();
	MatrixXd XtWX = Xt * W * X;

	//Calc (X^t W X)^-1 [pseudo-inverse]
	/*JacobiSVD<MatrixXd> svd(XtWX, ComputeThinU | ComputeThinV);
	MatrixXd sigma(N, N);
	sigma.setZero(N,N);
	for( int i = 0; i < M; i++){
		if (i < svd.singularValues().rows()){
			sigma(i, i) = (svd.singularValues())(i);
			if (sigma(i, i) != 0) sigma(i, i) = 1/ sigma(i, i);
		}
	}

	MatrixXd Ut = svd.matrixU().transpose();
	MatrixXd V  = svd.matrixV();
	MatrixXd INVERSE = V * sigma * Ut; */
	MatrixXd INVERSE = XtWX.inverse();

	//Calc  X^t W Y
	MatrixXd XtWY = Xt * W * Y;
	//Calc (X^t W X)^-1(X^t W ) -- coefficients
	C = (INVERSE)*(XtWY);


	return true;
}


Evaluate_Surrogate_LWR::~Evaluate_Surrogate_LWR() {
	//
}

double* Evaluate_Surrogate_LWR::getCoefficients(){
	double *coef = new double[C.rows()];
	for (int i = 0; i < C.rows(); i++){
		coef[i] = C(i);
	}
	return coef;
}

double Evaluate_Surrogate_LWR::calcNewY(double *P){
	double result = 0.0;
	for (int i = 0; i < C.rows(); i++){
		result += C(i)*P[i];
	}
	return result;
}

double Evaluate_Surrogate_LWR::calcFitness(IndividualPtr &ind){
	double fitness = 0;
	int plus = 2;
	double **X;
	double *Y;
	double *P;

	//Search near individuals
	double r = 0.1;
	tree->search(ind, r, this->dimension + plus);

	//Convert the more similar individuals to a matrix and apply the regression
	M = tree->nFoundK;
	N = this->dimension + 1;
	X = new double*[M];
	for(int i = 0; i < M; i++)
		X[i] = new double[N];
	Y = new double[M];

	//store biggest distance (11/07)
	double max_dist = 0.0;


	for(int i = 0; i < M; i++){
		X[i][0] = 1; //bias
		for(int j = 1; j < N; j++){
			X[i][j] = tree->foundK[i]->ind->getGene(j - 1);
		}
		Y[i] = tree->foundK[i]->ind->getFitness();
		max_dist = tree->distFoundK[i] > max_dist ? tree->distFoundK[i] : max_dist;
	}
	this->tal = sqrt(max_dist);


	P = new double[N];
	P[0] = 1;
	for(int j = 1; j < N; j++){
		P[j] = ind->getGene(j - 1);
	}

	//apply regression
	if (!this->regress(Y, X, M, N, P)){
		return RAND_MAX;
	}

	fitness = calcNewY(P);//result;
	ind->setFitnessSurrogate(fitness);
	return fitness;
}

void Evaluate_Surrogate_LWR::insert(IndividualPtr ind){
	tree->insert(ind);
}

//Set a parameter to surrogate model
void Evaluate_Surrogate_LWR::setParam(string param, double value){
	tal = value;
}

void Evaluate_Surrogate_LWR::setParam(string param, int value){
	tal = (double)value;
}

} /* namespace surrogate */
} /* namespace opt */
