/*
 * EvaluateAPM.cpp
 *
 *  Created on: 08/02/2012
 *      Author: krempser
 */

#include "Evaluate_APM.h"

namespace opt{
namespace evaluate {

	Evaluate_APM::Evaluate_APM(Function *func): Evaluate(func){
		setFunction(func);
		int n = func->getNConstraints();
		k = new double[n];
		for (int l = 0; l < n; l++) k[l] = 0.0;
		fAvg = 0.0;
	}

	Evaluate_APM::~Evaluate_APM(){
		delete [] k;
	}

	double Evaluate_APM::calcFitness(IndividualPtr &ind) const{
		return calcFitness(ind, false);
	}

	double Evaluate_APM::calcFitness(IndividualPtr &ind, bool calculed) const{
		double result, originalResult;
		vector<double> val = ind->getChromosome();
		vector<double> con = ind->getConstraints();

		if (calculed == false){
			getFunction()->calc(val, result, con);
			ind->setConstraints(con);
		} else {
			result = ind->getFitnessOriginal();
		}

		originalResult = result;

		double sumConstW = 0.0;
		bool   valid = true;
		for (int i = 0; i < (int)con.size(); i++){
			if (con[i] > 0.0){
				valid = false;
			    sumConstW += con[i]*k[i];
			}
		}
		if (!valid){
			if (result < fAvg){
				result = fAvg + sumConstW;
			} else {
				result += sumConstW;
			}
		}
		ind->setFitnessOriginal(originalResult);
		ind->setFitness(result);
		return result;
	}

	//Update weigths of constraints
	void Evaluate_APM::update(vector<IndividualPtr> pop){
		int nConst = getFunction()->getNConstraints();
		int nPop = pop.size();
		/*General calc*/
		//Sum of fitness in the population
		double sumFitness = 0.0;
		//int n = 0;
		for (int i = 0; i < nPop; i++){
			//if (pop[i]->isValid()){
				sumFitness += pop[i]->getFitnessOriginal();
			//	n++;
			//}
		}

		//Set the mean of the fitness (2011/08/04)
		fAvg = sumFitness/nPop;
		//if (n == 0) n = 1;
		//cout << n << "\n";
		//fAvg = sumFitness/n;

		//Sum of violations for each individual for each violation
		//sum_{l=1}^{m}(sum_{i=1}^{pop}(v_l(x^1))^2)
		double sumViolationForInd = 0.0;
		double sumForAllViolation = 0.0;
		for (int l = 0; l < nConst; l++){
			sumViolationForInd = 0.0;
			for (int i = 0; i < nPop; i++){
				if (pop[i]->getConstraint(l) > 0.0){
					sumViolationForInd += pop[i]->getConstraint(l);
				}
			}
			sumViolationForInd = sumViolationForInd/nPop;
			sumForAllViolation += sumViolationForInd*sumViolationForInd;
		}

		//2011/08/04
		double sumViolationJ = 0.0;
		//Sum of the violantion in the population for each k_j
		for (int j = 0; j < nConst; j++){
			sumViolationJ = 0.0;
			for (int i = 0; i < nPop; i++){
				if (pop[i]->getConstraint(j) > 0.0){
					sumViolationJ += pop[i]->getConstraint(j);
				}
			}

			if (sumForAllViolation < 0.0001) sumForAllViolation = 0.0001;

			//Update k_j
			//Original apm
			k[j] = fabs(fAvg)*((sumViolationJ/nPop)/sumForAllViolation);
			//cout << " K: " << k[j] << " "<< " sJ: " << sumViolationJ;
		}   //cout << " avg: " << fAvg  << " sA: " << sumForAllViolation; cout << "\n";
	}

	//1 -- first best, 0 -- equals, -1 -- second best
	int Evaluate_APM::compare(IndividualPtr &ind1, IndividualPtr &ind2) const{
		calcFitness(ind1, true);
		calcFitness(ind2, true);
		//cout << "compares\n" ;
		if (ind1->getFitness() < ind2->getFitness()){
			return 1;
		} else if (ind1->getFitness() > ind2->getFitness()){
			return -1;
		} else {
			return 0;
		}
	}
} /* namespace evaluate */
}
