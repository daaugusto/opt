/*
 * Evaluate_APM_Monotonic.cpp
 *
 *  Created on: 08/02/2012
 *      Author: krempser
 */

#include "Evaluate_APM_Monotonic.h"

namespace opt {
namespace evaluate {

	//Update weigths of constraints
	void Evaluate_APM_Monotonic::update(vector<IndividualPtr> pop){
		int nConst = getFunction()->getNConstraints();
		int nPop = pop.size();
		/*General calc*/
		//Sum of fitness in the population
		double sumFitness = 0.0;

		for (int i = 0; i < nPop; i++){
			sumFitness += pop[i]->getFitnessOriginal();
		}

		//Set the mean of the fitness (2011/08/04)
		fAvg = sumFitness/nPop;

		//Sum of violations for each individual for each violation
		//sum_{l=1}^{m}(sum_{i=1}^{pop}(v_l(x^1))^2)
		double sumViolationForInd = 0.0;
		double sumForAllViolation = 0.0;
		for (int l = 0; l < nConst; l++){
			sumViolationForInd = 0.0;
			for (int i = 0; i < nPop; i++){
				if (pop[i]->getConstraint(l) > 0){
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
				if (pop[i]->getConstraint(j) > 0){
					sumViolationJ += pop[i]->getConstraint(j);
				}
			}

			if (sumForAllViolation < 0.0001) sumForAllViolation = 0.0001;

			//If use the monotonic apm
			double preKj = fabs(fAvg)*((sumViolationJ/nPop)/sumForAllViolation);
			k[j] = preKj > k[j] ? preKj : k[j];
			//cout << " K: " << k[j] << " "<< " sJ: " << sumViolationJ;
		}  // cout << " avg: " << fAvg  << " sA: " << sumForAllViolation; cout << "\n";
	}

} /* namespace evaluate */
}
