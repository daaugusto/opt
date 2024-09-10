/*
 * Evaluate_Surrogate_NN.cpp
 *
 *  Created on: 18/04/2012
 *      Author: Eduardo Krempser
 */

#include "Evaluate_Surrogate_NN.h"

namespace opt {
namespace surrogate {

//Define the k-NN
Evaluate_Surrogate_NN::Evaluate_Surrogate_NN(Function *func, int k):Evaluate_Surrogate(func) {
	tree = new KDTree(func->getNDimensions(), func);
	type = KNN;
	this->k = k;
	this->r = 1.0;
	this->setKey(SURROGATE_KNN);
}

//Define the r-NN
Evaluate_Surrogate_NN::Evaluate_Surrogate_NN(Function *func, double r):Evaluate_Surrogate(func) {
	tree = new KDTree(func->getNDimensions(), func);
	type = RNN;
	this->k = 1;
	this->r = r;
	this->setKey(SURROGATE_RNN);
}

//Define k-NN or r-NN by values
Evaluate_Surrogate_NN::Evaluate_Surrogate_NN(Function *func, int k, double r):Evaluate_Surrogate(func) {
	tree = new KDTree(func->getNDimensions(), func);

	if (k == 0){
		type = RNN;
		this->k = 1;
		this->r = r;
		this->setKey(SURROGATE_RNN);
	} else {
		type = KNN;
		this->k = k;
		this->r = 0.0;
		this->setKey(SURROGATE_KNN);
	}
}

Evaluate_Surrogate_NN::~Evaluate_Surrogate_NN() {
	delete tree;
}

double Evaluate_Surrogate_NN::similarity(IndividualPtr &ind1, IndividualPtr &ind2){
	double boundDist = sqrt(ind1->getDimensions());
	double s = (1 - tree->distance(ind1, ind2))/(boundDist);
	return s;
}


double Evaluate_Surrogate_NN::calcFitness(IndividualPtr &ind){
	this->nEval = this->nEval + 1;
	double fitness;
	double sum = 0.0, sum2 = 0.0;
	//Search near individuals
	tree->search(ind, (float)r, k);
	//If nothing has been found
	if (tree->nFoundK == 0){
		return 0.0;
	}
	if (type == KNN){
		for(int i = 0; i < tree->nFoundK; i++){
			double s = this->similarity(ind, tree->foundK[i]->ind);
			sum +=  pow(s, 2) * tree->foundK[i]->ind->getFitness();
			sum2 += pow(s, 2);
		}
		fitness = sum/sum2;
		ind->setFitnessSurrogate(fitness);
		return fitness;
	} else {
		if (tree->nFound > 0){
			for(int i = 0; i < tree->nFound; i++){
				sum += pow(tree->distance(ind, tree->found[i]->ind), 2) * tree->found[i]->ind->getFitness();
				sum2 += pow(tree->distance(ind, tree->found[i]->ind), 2);
			}
			fitness = sum/sum2;
		} else {
			fitness = tree->foundK[0]->ind->getFitness();
		}
		ind->setFitnessSurrogate(fitness);
		return fitness;
	}
}

void Evaluate_Surrogate_NN::insert(IndividualPtr ind){
	tree->insert(ind);
}

//Set a parameter to surrogate model
void Evaluate_Surrogate_NN::setParam(string param, double value){
	this->r = value;
}

void Evaluate_Surrogate_NN::setParam(string param, int value){
	this->k = value;
}

void Evaluate_Surrogate_NN::update( Evaluate* eval ) {
    //Update
	tree->update(eval);
}

} /* namespace surrogate */
} /* namespace opt */
