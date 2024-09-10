/*
 * Evaluate_Surrogate_RBF.cpp
 *
 *  Created on: 19/07/2012
 *      Author: Eduardo Krempser
 */

#include "Evaluate_Surrogate_RBF.h"

namespace opt {
namespace surrogate {

Evaluate_Surrogate_RBF::Evaluate_Surrogate_RBF(Function *func):Evaluate_Surrogate(func) {
	this->tal = 0.5;
	this->dimension = func->getNDimensions();
	tree = new KDTree(this->dimension, func);
	this->setKey(SURROGATE_RBF);
}

Evaluate_Surrogate_RBF::Evaluate_Surrogate_RBF(Function *func, double tal):Evaluate_Surrogate(func){
	this->tal = tal;
	this->dimension = func->getNDimensions();
	tree = new KDTree(this->dimension, func);
	this->setKey(SURROGATE_RBF);
}

double Evaluate_Surrogate_RBF::basis(double dist, double t){
	double val = (-(dist*dist)) / (t*t);
	return exp(val);
}

double Evaluate_Surrogate_RBF::weight(MatrixXd X, int index, int index2){
	double dist = Algebra::distance(X, index, X, index2);
	return basis(dist, tal);
}

void Evaluate_Surrogate_RBF::fillW(MatrixXd X, MatrixXd &W, MatrixXd P){
	for (int i = 0; i < X.rows(); i++){
		for(int j = 0; j < X.rows(); j++){
			W(i, j) = weight(X, i, j);
		}
	}
}


void Evaluate_Surrogate_RBF::fillW(MatrixXd X, MatrixXd &W){
	for (int i = 0; i < X.rows(); i++){
		for(int j = 0; j < nCenters; j++){
			W(i, j) = weight(X, i, centers[j]);
		}
	}
}

double Evaluate_Surrogate_RBF::weight(MatrixXd X, int index, double *Center){
	double *v = new double[N];
	for (int i = 0; i < N; i++){
		v[i] = X(index, i);
	}
	double dist = Algebra::distance(v, Center, N);
	delete []v;
	return basis(dist, tal);
}

bool Evaluate_Surrogate_RBF::regress(double *pY, double **pX, int M, int N, double *pP){ //P is the query point
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
	MatrixXd W(M, nCenters);
	fillW(X, W);
	/********************* CALCULO DE SOBESTER 2004 -- COERENTE COM A VARIANCIA ******
	MatrixXd INVERSE = W.inverse();

	//Store de last inverse
	this->lastInversePhi = INVERSE;

	//Calc  coefficients
	C = INVERSE * Y;
	//***********************************/

	/******************** MINIMOS QUADRADOS **********/
	//Calc (X^t W X)
	MatrixXd Wt   = W.transpose();
	MatrixXd WtW = Wt * W;

	//Calculo da inversa direto
	//MatrixXd INVERSE = WtW.inverse();

	FullPivHouseholderQR<MatrixXd> qr = (WtW).fullPivHouseholderQr( );
	if (qr.rank() < WtW.cols()){
//		cout << "rank: " << qr.rank() << " cols: " << WtW.cols() << endl;
//		cout << "INST" << endl;
		return false;
	}

	/********************* CALCULO DA INVERSA POR SVD ******/
	//Calc (X^t W X)^-1 [pseudo-inverse]
	JacobiSVD<MatrixXd> svd(WtW, ComputeThinU | ComputeThinV);
	//int n = N < M ? N : M;
	int n = nCenters < M ? nCenters : M;
	MatrixXd sigma(n, n);
	sigma.setZero(n,n);
	for( int i = 0; i < M; i++){
		if (i < svd.singularValues().rows()){
			sigma(i, i) = (svd.singularValues())(i);
			if (sigma(i, i) != 0) sigma(i, i) = 1/ sigma(i, i);
		}
	}

	MatrixXd Ut = svd.matrixU().transpose();
	MatrixXd V  = svd.matrixV();
	MatrixXd INVERSE = V * sigma * Ut;
	//***********************************/

	//Store de last inverse
	this->lastInversePhi = INVERSE;

	//Calc  coefficients
	C = INVERSE * Wt * Y;
	/*************************************************************************************/


	return true;
}


Evaluate_Surrogate_RBF::~Evaluate_Surrogate_RBF() {
	//
}

double* Evaluate_Surrogate_RBF::getCoefficients(){
	double *coef = new double[C.rows()];
	for (int i = 0; i < C.rows(); i++){
		coef[i] = C(i);
	}
	return coef;
}

double Evaluate_Surrogate_RBF::calcNewY(double *P, double **Centers){
	double result = 0.0;
	for (int i = 0; i < C.rows(); i++){
		result += C(i)*basis(Algebra::distance(Centers[i], P, this->N), this->tal);
	}
	return result;
}

double Evaluate_Surrogate_RBF::approximationError(double *Y, double **X, int M, int N, double **Centers){
	double sum = 0.0;
	for(int i = 0; i < M; i++){
		double val = calcNewY(X[i], Centers);
		sum = fabs(Y[i] - val) * fabs(Y[i] - val);
	}
	return sum / M;
}

/*
double Evaluate_Surrogate_RBF::calcFitness(IndividualPtr &ind){
	this->nEval = this->nEval + 1;
	double fitness = 0;
	int plus = 1; //1
	double **X;
	double *Y;
	double *P;
	N = this->dimension + plus;
	double max_dist = 0.0;

	//Search near individuals
	double r = 0.01;
	int k = this->dimension/2;
	nCenters = this->dimension/2;

	int *centerIndex = new int[nCenters];
	double *centerDist = new double[nCenters];
	for(int l = 0; l < nCenters; l++){
		centerDist[l]  = RAND_MAX;
		centerIndex[l] = -1;
	}

	//Search M values to train
	tree->search(ind, r, k);

	if (tree->nFoundK < k){
		return RAND_MAX;
	}

	//Convert the more similar individuals to a matrix and apply the regression
	M = tree->nFoundK;
	X = new double*[M];
	for(int i = 0; i < M; i++)
		X[i] = new double[N];
	Y = new double[M];

	//Individual
	P = new double[N];
	if (plus > 0)
		P[0] = 1;
	for(int j = 0 + plus; j < N; j++){
		******** Normalized gene *****************************
		P[j] = ind->getGene(j - plus);
		******** Normalized gene *****************************
		*******************************************************
		P[j] = this->function->convertToRealRange(j - plus, ind->getGene(j - plus));
		/*******************************************************
	}

	//store biggest distance (11/07)
	max_dist = 0.0;
	for(int i = 0; i < M; i++){
		if (plus > 0){
			X[i][0] = 1; //bias
		}
		for(int j = 0 + plus; j < N; j++){
			******** Normalized gene *****************************
			X[i][j]       = tree->foundK[i]->ind->getGene(j - plus);
			******** Normalized gene *****************************
			*******************************************************
			X[i][j]       = this->function->convertToRealRange(j - plus, tree->foundK[i]->ind->getGene(j - plus));
 	 	 	/*******************************************************
		}
		******** Normalized gene *****************************
		Y[i] = tree->foundK[i]->ind->getFitness();
		******** Normalized gene *****************************
		*******************************************************
		Y[i] = tree->foundK[i]->ind->getFitness();
		/*******************************************************

		//double dist = Algebra::distance(P, X[i], N);
		//max_dist = dist > max_dist ? dist : max_dist;
		max_dist = tree->distFoundK[i] > max_dist ? tree->distFoundK[i] : max_dist;


		//Pick the nCenters with best distances
		int tempcenterIndexMax = 0;
		for(int l = 0; l < nCenters; l++){
			if (centerDist[l] > centerDist[tempcenterIndexMax]){
				tempcenterIndexMax = l;
			}
		}
		if (tree->distFoundK[i] < centerDist[tempcenterIndexMax]){
			centerDist[tempcenterIndexMax]  = tree->distFoundK[i];
			centerIndex[tempcenterIndexMax] = i;
		}
	}

	for(int i = 0; i < nCenters; i++){
		int r1, r2, aux;
		double auxVal;
		r1 = Tools::newRand(0, nCenters);
		r2 = Tools::newRand(0, nCenters);
		aux    = centerIndex[r1];
		auxVal = centerDist[r1];
		centerIndex[r1] = centerIndex[r2];
		centerDist[r1]  = centerDist[r2];
		centerIndex[r2] = aux;
		centerDist[r2]  = auxVal;
	}

	//Select centers
	centers = new double*[nCenters];
	for(int i = 0; i < nCenters; i++){
		centers[i] = new double[N];
		if (plus > 0){
			centers[i][0] = 1; //bias
		}
		for(int j = 0 + plus; j < N; j++){
			******** Normalized gene *****************************
			centers[i][j] = tree->foundK[centerIndex[i]]->ind->getGene(j - plus);
			******** Normalized gene *****************************
			*******************************************************
			centers[i][j] = this->function->convertToRealRange(j - plus, tree->foundK[centerIndex[i]]->ind->getGene(j - plus));
			/*******************************************************
		}
	}
	******** Normalized gene *****************************
	//this->tal = sqrt(max_dist);
	this->tal = sqrt(this->dimension);//max_dist;
	******** Normalized gene *****************************
	******************************************************
	//this->tal = sqrt(this->function->convertToRealRange(0, max_dist));
	int iMaxRange = 0;
	double maxRange = (this->function->convertToRealRange(0, 1.0) - this->function->convertToRealRange(0, 0.0));
	for (int i = 0; i < this->dimension; i++){
		double range = (this->function->convertToRealRange(0, 1.0) - this->function->convertToRealRange(0, 0.0));
		if (range > maxRange){
			iMaxRange = i;
		}
	}
	this->tal = sqrt(this->function->convertToRealRange(iMaxRange, max_dist));
	/********************************************************

	this->tal = 0.01;
	double bestTal = this->tal;
	double bestTalAp = -1;
	double h = 0.1;
	for(int ir = 0; ir < 10; ir++){
		//apply regression
		if (!this->regress(Y, centers, nCenters, N, P)){
			//return RAND_MAX;
			continue;
		}

		double apError = approximationError(Y, X, M, N, centers);
		cout << "\nErro: " << apError << " tal:" << tal;
		if (bestTalAp == -1 || bestTalAp > apError){
			bestTal = this->tal;
			bestTalAp = apError;
		}
		this->tal = this->tal + h;
	}
	this->tal = bestTal;
	cout << " besttal: " << tal;

	//if (!this->regress(Y, centers, nCenters, N, P)){
	if (!this->regress(Y, X, M, N, P)){
		return RAND_MAX;
	}

	fitness = calcNewY(P, centers);
	ind->setFitnessSurrogate(fitness);

	//Store the last phi vector
	this->calcLastphi(P, centers);

	//Calc and store the variance
	this->calcVariance(Y, X, N, M, centers, fitness);

	//free memory
	delete []Y;
	delete []P;
	for(int i = 0; i < M; i++)
		delete []X[i];
	delete []X;
	for(int i = 0; i < nCenters; i++)
		delete []centers[i];
	delete []centers;

	//Store the last calculated fitness
	this->lastFitness = fitness;

	return fitness;
}
*/

double Evaluate_Surrogate_RBF::calcFitness(IndividualPtr &ind){
	this->nEval = this->nEval + 1;
	double fitness = 0;
	int plus = 0; //1
	double **X;
	double *Y;
	double *P;
	N = this->dimension + plus;
	double max_dist = 0.0;

	//Search near individuals
	double r = 0.01;
	int k = 2*this->dimension;

	//Search M values to train
	tree->search(ind, r, k);

	if (tree->nFoundK < k){
		return RAND_MAX;
	}

	double maxBound = 0;
	for(int i = 0; i < this->dimension; i++){
		maxBound += pow(this->function->getBoundMax(i) - this->function->getBoundMin(i), 2);
	}
	this->tal = sqrt(maxBound);

	int extra = 0;
	do{
		nCenters = this->dimension/2;// + extra;
		//Convert the more similar individuals to a matrix and apply the regression
		M = nCenters + extra;//tree->nFoundK;
		X = new double*[M];
		for(int i = 0; i < M; i++)
			X[i] = new double[N];
		Y = new double[M];

		//Individual
		P = new double[N];
		if (plus > 0)
			P[0] = 1;
		for(int j = 0 + plus; j < N; j++){
			P[j] = ind->getGene(j - plus);
		}

		//Centers
		int *centerIndex = new int[nCenters];
		double *centerDist = new double[nCenters];
		for(int l = 0; l < nCenters; l++){
			centerDist[l]  = RAND_MAX;
			centerIndex[l] = -1;
		}


		//store biggest distance (11/07)
		max_dist = 0.0;
		for(int i = 0; i < M; i++){
			if (plus > 0){
				X[i][0] = 1; //bias
			}
			for(int j = 0 + plus; j < N; j++){
				X[i][j]       = tree->foundK[i]->ind->getGene(j - plus);
			}
			Y[i] = tree->foundK[i]->ind->getFitness();
			max_dist = tree->distFoundK[i] > max_dist ? tree->distFoundK[i] : max_dist;

			//Pick the nCenters with best distances
			int tempcenterIndexMax = 0;
			for(int l = 0; l < nCenters; l++){
				if (centerDist[l] > centerDist[tempcenterIndexMax]){
					tempcenterIndexMax = l;
				}
			}
			if (tree->distFoundK[i] < centerDist[tempcenterIndexMax]){
				centerDist[tempcenterIndexMax]  = tree->distFoundK[i];
				centerIndex[tempcenterIndexMax] = i;
			}
		}

		for(int i = 0; i < nCenters; i++){
			int r1, r2, aux;
			double auxVal;
			r1 = Tools::newRand(0, nCenters);
			r2 = Tools::newRand(0, nCenters);
			aux    = centerIndex[r1];
			auxVal = centerDist[r1];
			centerIndex[r1] = centerIndex[r2];
			centerDist[r1]  = centerDist[r2];
			centerIndex[r2] = aux;
			centerDist[r2]  = auxVal;
		}

		//Select centers
		centers = new double*[nCenters];
		for(int i = 0; i < nCenters; i++){
			centers[i] = new double[N];
			if (plus > 0){
				centers[i][0] = 1; //bias
			}
			for(int j = 0 + plus; j < N; j++){
				centers[i][j] = tree->foundK[centerIndex[i]]->ind->getGene(j - plus);
			}
		}
		extra++;
	}while(!this->regress(Y, X, M, N, P) && (nCenters + extra) < k);

	fitness = calcNewY(P, centers);
	ind->setFitnessSurrogate(fitness);

	//Store the last phi vector
	this->calcLastphi(P, centers);

	//Calc and store the variance
	this->calcVariance(Y, X, N, M, centers, fitness);

	//free memory
	delete []Y;
	delete []P;
	for(int i = 0; i < M; i++)
		delete []X[i];
	delete []X;
	for(int i = 0; i < nCenters; i++)
		delete []centers[i];
	delete []centers;

	//Store the last calculated fitness
	this->lastFitness = fitness;

	return fitness;
}


void Evaluate_Surrogate_RBF::insert(IndividualPtr ind){
	tree->insert(ind);
}

//Set a parameter to surrogate model
void Evaluate_Surrogate_RBF::setParam(string param, double value){
	tal = value;
}

void Evaluate_Surrogate_RBF::setParam(string param, int value){
	tal = (double)value;
}


//Return the mean and variance of the model, if exists
double Evaluate_Surrogate_RBF::getMean(){
	return this->lastFitness;
}

void Evaluate_Surrogate_RBF::calcVariance(double *Y, double **X, int N, int M, double **Centers, double fit){
	MatrixXd result1 = this->lastphi * this->lastInversePhi;
	result1 = result1 * this->lastphi.transpose();
	double val1 = result1.determinant();

	MatrixXd uns(nCenters, 1);
	uns.setOnes(nCenters, 1);
	MatrixXd result2 = uns.transpose() * this->lastInversePhi * this->lastphi.transpose();
	double val2 = 1 - result2.determinant();
	val2 = val2 * val2;

	MatrixXd result3 = uns.transpose() * this->lastInversePhi * uns;
	double val3 = result3.determinant();

	double valRes = pow(this->tal, 2)*(1 - val1 + val2 / val3);

	this->lastVariance = valRes;



	//this->lastVariance = this->tal/(sqrt(2*nCenters));

}

double Evaluate_Surrogate_RBF::getVariance(){
	return this->lastVariance;
}

void Evaluate_Surrogate_RBF::calcLastphi(double *P, double **X){
	MatrixXd phi(1, C.rows());
	for (int i = 0; i < C.rows(); i++){
		phi(0, i) = basis(Algebra::distance(X[i], P, this->N), this->tal);
	}
	this->lastphi = phi;
}

double Evaluate_Surrogate_RBF::getTal(){
	return this->tal;
}

void Evaluate_Surrogate_RBF::update( Evaluate* eval ) {
    //Update
	tree->update(eval);
}

} /* namespace surrogate */
} /* namespace opt */
