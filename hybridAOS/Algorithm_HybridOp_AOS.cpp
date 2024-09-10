/*
 * AlgorithmHybridOpAOS.cpp
 *
 *  Created on: 24/02/2012
 *      Author: Eduardo Krempser
 */

#include "Algorithm_HybridOp_AOS.h"

namespace opt {
namespace hybridAos {

	void Algorithm_HybridOp_AOS::run_generate(vector<IndividualPtr> &pop){
		//Run one generation
		iBest = Tools::getBest(pop, eval);
		vector<IndividualPtr> offspring;
		vector<IndividualPtr> newPop;
		newPop.clear();
		int ng = 0;

		while(ng < popSize  && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
			Input::currentIndividual = ng;
			//Select algorithm
			int algIndex = this->aos->SelectOperator();
			offspring.clear();
			double w = DBL_MAX;
			if (this->aos->AOS_technique < 5) w = 0.0;
			if (algIndex == 0){
				//Run DE algorithm
				w = de->generateIndividual(ng, iBest, pop, offspring);
				nDE++;
			} else if (algIndex == 1){
				//Run GA algorithm
				w = ga->generateIndividual(ng, iBest, pop, offspring);
				nGA++;
			} else {
				throw new Exception("The index of algorithm not found -- Algorithm_Hybrid_AOS/run_generate");
			}

			//Select new pop
			for (int i = 0; i < (int)offspring.size(); i++){
				if (eval->compare(offspring[i], pop[ng]) > 0){
					newPop.push_back(offspring[i]);
					//Calc reward
					/*if ( this->aos->aos_delta_fitness ){
						w = offspring[i]->getFitness() - pop[ng]->getFitness();
					} else {//To FAUC or FSUM
						w = offspring[i]->getFitness();
					}*/
				} else {
					newPop.push_back(pop[ng]);
				}
				//Update rewards
				this->aos->addReward(algIndex, w);
				this->aos->ApplyReward(algIndex);
			}
			ng+=(int)offspring.size();
		}

		//Update population
		pop = newPop;
	}

} /* namespace hybridAos */
} /* namespace opt */
