/*
 * Evaluate.cpp
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#include "Evaluate.h"

namespace opt{
namespace evaluate {

	Evaluate::Evaluate(Function *funct){
		function = funct;
	}

	double Evaluate::calcFitness(IndividualPtr &ind) const{
		double result;
		vector<double> val = ind->getChromosome();
		vector<double> con = ind->getConstraints();
		function->calc(val, result, con);
		ind->setFitness(result);
		ind->setFitnessOriginal(result);
		ind->setConstraints(con);
		return result;
	}

	//1 -- first best, 0 -- equals, -1 -- second best
	int Evaluate::compare(IndividualPtr &ind1, IndividualPtr &ind2) const{
		if (ind1->getFitness() < ind2->getFitness()){
			return 1;
		} else if (ind1->getFitness() > ind2->getFitness()){
			return -1;
		} else {
			return 0;
		}
	}

	void Evaluate::setFunction(Function *funct){
		function = funct;
	}

	Function* Evaluate::getFunction() const{
		return function;
	}

	bool Evaluate::isValid(const IndividualPtr ind) const{
		return isValid(ind->getConstraints());
	}

	bool Evaluate::isValid(const vector<double> constraints) const{
		int n = constraints.size();
		for (int i = 0; i < n; i++){
			if (constraints[i] > 0){
				return false;
			}
		}
		return true;
	}

	bool Evaluate::operator() (IndividualPtr i,IndividualPtr j){
		if (this->compare(i, j) >= 0){
			return true;
		} else {
			return false;
		}
	}

	void Evaluate::update(const vector<IndividualPtr> pop){
		//Update informations of evaluate process
	}

	double Evaluate::difference(const IndividualPtr ind1, const IndividualPtr ind2) const{
		   return ind1->getFitness() - ind2->getFitness();
	}

	//For apm to update the penalty fitness
	double Evaluate::calcFitness(IndividualPtr &ind, bool calculated) const{
		return this->calcFitness(ind);
	}

	Evaluate::~Evaluate() {
		// TODO Auto-generated destructor stub
	}

	void Evaluate::initialize(){
		function->initialize();
	}

	void Evaluate::finalize(){
		function->finalize();
	}

	void Evaluate::setNEvals(double n){
		function->setNCalls(n);
	}

	double Evaluate::getNEvals(){
		return function->getNCalls();
	}

	void Evaluate::setMaxEvals(double n){
		function->setMaxCalls(n);
	}

	double Evaluate::getMaxEvals(){
		return function->getMaxCalls();
	}

} /* namespace evaluate */
}
