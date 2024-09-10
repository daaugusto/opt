/*
 * AlgorithmDE_.cpp
 *
 *  Created on: 10/02/2012
 *      Author: krempser
 */

#include "Algorithm_DE.h"

namespace opt {
namespace algorithm {

	Algorithm_DE::Algorithm_DE(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		this->setConfig(pMaxGen, pPopSize, pEval, seed);
	}

	Algorithm_DE::Algorithm_DE(Evaluate *pEval){
		setConfig(Input::maxGen, Input::popSize, pEval, Input::seedValue);
	}

	Algorithm_DE::~Algorithm_DE( ) {
		delete this->manager_op_mt;
	}


	void Algorithm_DE::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		Algorithm::setConfig(pMaxGen, pPopSize, pEval, seed);

		iBest = 0;
		//If necessary generate initial random value
		//if (seed != 0)
		//	Tools::generateSeed(seed);

		//Set the variants by input params
		this->manager_op_mt = new Manager_Operator();
		this->addOperatorsByInput(manager_op_mt, "DE");
	}

	//Run all DE
	void Algorithm_DE::runAll(){
		//Initialize the function
		eval->initialize();

		//Create pop
		if (pop.size() <= 0){
			createPop();
		}

//////////////
//			cout << "\nPop Inicial:\n";
//			for(int i = 0; i < (int)pop.size(); i++){
//				cout << " i  " << i << ": " << Tools::printIndividual(pop[i], eval, true) << "\n";
//			}
//////////////

		iBest = Tools::getBest(pop, eval);
		Tools::printHeaderInfo(pop, "", false);

//		eval->update(pop);

		int G = 0;
		while( ! Tools::isEndProcess(eval, pop[iBest]->getFitness()) ){
			eval->update(pop);

			//One generation
			run_generate(pop);

			iBest = Tools::getBest(pop, eval);

			Tools::printGenerationInfo(G, pop, iBest, eval, "", false);
//////////////
//			cout << "\nPop:\n";
//			for(int i = 0; i < (int)pop.size(); i++){
//				cout << "i(" << i << ": " << Tools::printIndividual(pop[i], eval, true) << "\n";
//			}
//////////////

			G++;
		}

		//Finalize function
		eval->finalize();
	}

	void Algorithm_DE::run_generate(vector<IndividualPtr> &pop){
		vector<IndividualPtr> newPop;
		vector<IndividualPtr> offspring;
		Operator *op;
		int ng = 0;
		double Cr = 0.9;
		//Run one generation
		iBest = Tools::getBest(pop, eval);
		newPop.clear();
		while(ng < popSize && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
			Input::currentIndividual = ng;
			offspring.clear();
			//Apply mutation
//			op = manager_op_mt->selectOperator();
op = manager_op_mt->getOperator(0);
			vector<int> index;
			index.clear();
			if ( ( (op->getKey()).find("CURRENT") >= 0 && (op->getKey()).find("CURRENT") < (op->getKey()).length() ) &&  ((op->getKey()).find("BEST") >= 0 && (op->getKey()).find("BEST") < (op->getKey()).length()) ){
				index.push_back(ng);
				index.push_back(iBest);
			} else if ( (op->getKey()).find("CURRENT") >= 0 && (op->getKey()).find("CURRENT") < (op->getKey()).length() ){
				index.push_back(ng);
			} else {
				index.push_back(iBest);
			}

////////////////////
//			cout << "\n------------  Op apply:" << endl;
////////////////////

			op->apply(pop, offspring, Input::F, index);
			//Calc the fitness of the offspring
			for (int i = 0; i < (int)offspring.size(); i++){
				//CrossOver
				int randJ = (int)Tools::newRand(0, dimensions);
////////////////////
//			cout << "\njRand:" << randJ << " CR: " << Cr << endl;
////////////////////
				for (int j = 0; j < dimensions; j++){
double r = 	Tools::newRand(0, 1);
//cout << " Random: " << r << endl;
					if (r >= Cr && j != randJ){
////////////////////
//			cout << "j =  " << j << endl;
////////////////////
						offspring[i]->setGene(j, pop[ng]->getGene(j));
					}
				}

				eval->calcFitness(offspring[i]);
			}

			/////////
//			cout << "\n------------  Op result:" << endl;
//			cout << Tools::printIndividual(offspring[0], eval, true) << "\n";
			////////


			//Select new pop
			for (int i = 0; i < (int)offspring.size(); i++){
				if (eval->compare(offspring[i], pop[ng]) >= 0){
					newPop.push_back(offspring[i]);
				} else {
					newPop.push_back(pop[ng]);
				}
			}
			ng+=(int)offspring.size();
		}
		pop = newPop;
	}

} /* namespace algorithm */
} /* namespace opt */
