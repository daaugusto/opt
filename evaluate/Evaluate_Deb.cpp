/*
 * Evaluate_Deb.cpp
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#include "Evaluate_Deb.h"

namespace opt {
namespace evaluate {

	double Evaluate_Deb::calcFitness(IndividualPtr &ind) const{
		double result;
		vector<double> val = ind->getChromosome();
		vector<double> con = ind->getConstraints();
		this->getFunction()->calc(val, result, con);
		ind->setFitness(result);
		ind->setFitnessOriginal(result);
		ind->setConstraints(con);
		return result;
	}

	//1 -- first best, 0 -- equals, -1 -- second best
	int Evaluate_Deb::compare(IndividualPtr &ind1, IndividualPtr &ind2) const{
		//Constraint sum
		double cSum1 = 0.0, cSum2 = 0.0;
		for (int i = 0; i < getFunction()->getNConstraints(); i++){
			if (ind1->getConstraint(i) > 0)
				cSum1 += ind1->getConstraint(i);
			if (ind2->getConstraint(i) > 0)
				cSum2 += ind2->getConstraint(i);
		}

		if (cSum1 == 0.0 && cSum2 > 0.0){
			return 1;
		} else if (cSum1 > 0.0 && cSum2 == 0.0){
			return -1;
		} else if (cSum1 == 0.0 && cSum2 == 0.0){
			if (ind1->getFitness() < ind2->getFitness()){
				return 1;
			} else if (ind1->getFitness() > ind2->getFitness()){
				return -1;
			} else {
				return 0;
			}
		} else {
			if (cSum1 < cSum2){
				return 1;
			} else if (cSum1 > cSum2){
				return -1;
			} else {
				return 0;
			}
		}
	}

	double Evaluate_Deb::difference(IndividualPtr ind1, IndividualPtr ind2) const{
	    if (isValid(ind1) && isValid(ind2)){
	        return ind1->getFitness() - ind2->getFitness();
	    } else if (!isValid(ind1) && !isValid(ind2)){
	        return ind1->getSumConstraints() - ind2->getSumConstraints();
	    } else if (isValid(ind1) && !isValid(ind2)){
	        return ind2->getSumConstraints();
	    } else {
	        return ind1->getSumConstraints();
	    }
	}


} /* namespace evaluate */
} /* namespace opt */
