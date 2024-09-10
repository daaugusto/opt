/*
 * Evaluate_BLDE.cpp
 *
 *  Created on: 13/03/2019
 *      Author: Eduardo Krempser
 */

#include "Evaluate_BLDE.h"

namespace opt {
namespace evaluate {

	Evaluate_BLDE::Evaluate_BLDE(Function *func): Evaluate(func){
//		functionSMD = func;
		this->nCallsFollower = 0;
	}

	void Evaluate_BLDE::setNEvalsFollower(double n){
		this->nCallsFollower = n;
	}

	double Evaluate_BLDE::getNEvalsFollower(){
		return this->nCallsFollower;
	}

/*	Function_SMD* Evaluate_BLDE::getFunctionSMD(){
		return this->functionSMD;
	}
*/
	double Evaluate_BLDE::calcFitness(IndividualPtr &ind) const{
//        cout << "EvalBLDE:calcInd.1" << endl;
		double result;
		vector<double> val = ind->getChromosome();
		vector<double> con = ind->getConstraints();
		this->getFunction()->calc(val, result, con);
		ind->setFitness(result);
		ind->setFitnessOriginal(result);
		ind->setConstraints(con);
		return result;
	}

	double Evaluate_BLDE::calcFitness(IndividualPtr &indLeader, IndividualPtr &indFollower, int level) const{
		double result;
//		cout << "EvalBLDE:calc.1" << endl;
		vector<double> valLeader = indLeader->getChromosome();
//		cout << "EvalBLDE:calc.2" << endl;
		vector<double> valFollower = indFollower->getChromosome();
		vector<double> con;
//		cout << "EvalBLDE:calcInd.3" << endl;
		if (level == 1){
			con = indLeader->getConstraints();
		} else {
			con = indFollower->getConstraints();
		}
//		cout << "antes " << endl;
//valLeader[0] = 0;valLeader[1] = 0;
//valFollower[0] = 0;valFollower[1] = 0; valFollower[2] = 0;
		((Function_SMD*)this->getFunction())->calc(valLeader, valFollower, result, con, level);
//		cout << result << endl;
 		if (level == 1){
			indLeader->setFitness(result);
			indLeader->setFitnessOriginal(result);
			indLeader->setConstraints(con);
		} else {
			indFollower->setFitness(result);
			indFollower->setFitnessOriginal(result);
			indFollower->setConstraints(con);
		}
		return result;
	}

	//1 -- first best, 0 -- equals, -1 -- second best
	int Evaluate_BLDE::compare(IndividualPtr &ind1, IndividualPtr &ind2) const{
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

	double Evaluate_BLDE::difference(IndividualPtr ind1, IndividualPtr ind2) const{
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
