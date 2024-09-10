/*
 * AlgorithmGA.cpp
 *
 *  Created on: 10/02/2012
 *      Author: Eduardo Krempser
 */

#include "Algorithm_GA.h"

namespace opt {
namespace algorithm {

	Algorithm_GA::Algorithm_GA(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		this->setConfig(pMaxGen, pPopSize, pEval, seed);
	}

	Algorithm_GA::Algorithm_GA(Evaluate *pEval){
		setConfig(Input::maxGen, Input::popSize, pEval, Input::seedValue);
	}

	void Algorithm_GA::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		Algorithm::setConfig(pMaxGen, pPopSize, pEval, seed);

		//Define operators
		manager_op_cx = new Manager_Operator();
		manager_op_mt = new Manager_Operator();

		//Add cross-over operators
//		this->addOperatorsByInput(manager_op_cx, "GA_CX");
this->addOperatorsByInput(manager_op_cx, "GA");
		this->addOperatorsByInput(manager_op_mt, "GA_MT");
	}

	void Algorithm_GA::runAll(){
		//Initialize the function
		eval->initialize();

		//Create pop
		if (pop.size() <= 0){
			createPop();
		}
		Tools::order(pop, eval);
	    Tools::printHeaderInfo(pop, "", false);

	    int G = 0;
	    while( ! Tools::isEndProcess(eval, pop[0]->getFitness()) ){
			Tools::printGenerationInfo(G, pop, 0, eval, "", false);

			//One generation
			run_generate(pop);
			eval->update(pop);

			G++;
		}

		Tools::order(pop, eval);

		//Finalize function
		eval->finalize();
	}

	void Algorithm_GA::run_generate(vector<IndividualPtr> &pop){
		vector<IndividualPtr> newPop;
		vector<IndividualPtr> parents;
		vector<IndividualPtr> parents_Mt;
		vector<IndividualPtr> offspring;
		Operator *op;
		int ng = 0;

		//Run one generation
		Tools::order(pop, eval);
		newPop.clear();

		//Elitism
		int nElit = 0.1*pop.size();
		if (nElit % 2 != 0) nElit++;
		for(ng = 0; ng < nElit; ng++){
			newPop.push_back(pop[ng]);
		}
		while(ng < popSize  && (! Tools::isEndProcess(eval, pop[0]->getFitness())) ){
			parents.clear();
			parents_Mt.clear();
			offspring.clear();

			//Select parents
			int tp = popSize, ps = 2;
			double value = ((double)(tp - 1))/(ps);
			double rValue1 = Tools::newRand(0.0, 1.0);
			int ix1 = (int)(value*(1.5 - sqrt(2.25 - 2*rValue1))) + 1;
			double rValue2 = Tools::newRand(0.0, 1.0);
			int ix2 = (int)(value*(1.5 - sqrt(2.25 - 2*rValue2))) + 1;
			parents.push_back(pop[ix1]);
			parents.push_back(pop[ix2]);

			//Apply CrossOver
			op = manager_op_cx->selectOperator();
			op->apply(parents, offspring);
			string cxKey = op->getKey();

			//Apply mutation in all offspring
			parents_Mt = offspring;
			op = manager_op_mt->selectOperator();
			op->apply(parents_Mt, offspring);

			//Calc the fitness of the offspring
			for (int i = 0; i < op->getNOffspring(); i++){
				eval->calcFitness(offspring[i]);
				newPop.push_back(offspring[i]);
			}
			ng+=op->getNOffspring();
		}
		pop = newPop;
	}

} /* namespace operators */
} /* namespace opt */
