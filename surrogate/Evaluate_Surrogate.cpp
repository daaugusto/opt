/*
 * Evaluate_Surrogate.cpp
 *
 *  Created on: 18/04/2012
 *      Author: Eduardo Krempser
 */

#include "Evaluate_Surrogate.h"


namespace opt {
namespace surrogate {

Evaluate_Surrogate::Evaluate_Surrogate(Function *func) : Evaluate(func){
	this->nEval = 0;
	// TODO Auto-generated constructor stub

}

Evaluate_Surrogate::~Evaluate_Surrogate() {
	// TODO Auto-generated destructor stub
}


void Evaluate_Surrogate::setKey(string k){
	this->key = k;
}

string Evaluate_Surrogate::getKey(){
	return this->key;
}

double Evaluate_Surrogate::calcFitness(IndividualPtr &ind) {
	nEval = nEval + 1;
	double result;
	vector<double> val = ind->getChromosome();
	vector<double> con = ind->getConstraints();

	result = 0.0;
	//Surrogate Calc

	ind->setFitnessSurrogate(result);
	ind->setConstraintsSurrogate(con);
	return result;
}

//1 -- first best, 0 -- equals, -1 -- second best
int Evaluate_Surrogate::compare(IndividualPtr &ind1, IndividualPtr &ind2) const{
	if (ind1->getFitnessSurrogate() < ind2->getFitnessSurrogate()){
		return 1;
	} else if (ind1->getFitnessSurrogate() > ind2->getFitnessSurrogate()){
		return -1;
	} else {
		return 0;
	}
}

bool Evaluate_Surrogate::isValid(const IndividualPtr ind) const{
	return Evaluate::isValid(ind->getConstraintsSurrogate());
}


bool Evaluate_Surrogate::operator() (IndividualPtr i,IndividualPtr j){
	if (this->compare(i, j) >= 0){
		return true;
	} else {
		return false;
	}
}

void Evaluate_Surrogate::update(const vector<IndividualPtr> pop){
	//Update informations of Evaluate_Surrogate process
}

void Evaluate_Surrogate::update( Evaluate* eval ) {
    //Update
}

double Evaluate_Surrogate::difference(const IndividualPtr ind1, const IndividualPtr ind2) const{
	   return ind1->getFitnessSurrogate() - ind2->getFitnessSurrogate();
}

//For apm to update the penalty fitness
double Evaluate_Surrogate::calcFitness(IndividualPtr &ind, bool calculated) {
	return this->calcFitness(ind);
}

void Evaluate_Surrogate::initialize(){
	//Initialize variables
	this->nEval = 0;
}

void Evaluate_Surrogate::finalize(){
	//Finalize variables
}

void Evaluate_Surrogate::setNEvals(double n){
	this->nEval = n;
}

double Evaluate_Surrogate::getNEvals(){
	return this->nEval;
}

void Evaluate_Surrogate::insert(IndividualPtr ind){

}

void Evaluate_Surrogate::setParam(string param, double value){

}

void Evaluate_Surrogate::setParam(string param, int value){

}

void Evaluate_Surrogate::setParam(string param, string value){

}

//Return the mean and variance of the model, if exists
double Evaluate_Surrogate::getMean(){
	return 0; //not defined
}

double Evaluate_Surrogate::getVariance(){
	return 0; //not defined
}

double Evaluate_Surrogate::calcEI(double y, double yMin, double mean, double variance){
	double s = sqrt(variance);
	double diff = yMin - y;// > 0 ? yMin - y : 0;

//	if (diff > 0) cout << "\n yMin: " << yMin << " y:" << y << " s: " << s << " variance: " << variance;
//cout << "\n" << Algebra::normalDensity(diff/s);
	if (s > 0){
		//return (diff)*Algebra::normalDistribution(diff/s) + s*Algebra::normalDensity(diff/s);
		//return (diff)*Algebra::normalDistribution(diff/s);
		//return (diff)*Algebra::normalDistribution(diff, mean, s) + s*Algebra::normalDensity(diff, mean, s);
		//return (diff)*Algebra::normalDensity(diff, mean, s) + s*Algebra::normalDistribution(diff, mean, s);
		//return (diff)*Algebra::normalDistribution(diff, mean, s);
		//return (diff)*Algebra::normalDensity(diff, mean, s);

		if (Input::sel.compare("PoI") == 0){
			//return (diff)*Algebra::normalDistribution(diff, mean, s);
			return (diff)*Algebra::normalDensity(diff, mean, s);
		} else {
			return (diff)*Algebra::normalDistribution(diff, mean, s) + s*Algebra::normalDensity(diff, mean, s);
		}
	} else {
		return 0;
	}
}

} /* namespace surrogate */
} /* namespace opt */
