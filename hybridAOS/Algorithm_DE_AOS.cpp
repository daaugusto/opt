/*
 * AlgorithmDEAOS.cpp
 *
 *  Created on: 15/02/2012
 *      Author: Eduardo Krempser
 */

#include "Algorithm_DE_AOS.h"

namespace opt {
namespace hybridAos {

	Algorithm_DE_AOS::Algorithm_DE_AOS(int pMaxGen, int pPopSize, Evaluate *pEval, int seed):Algorithm_DE(pMaxGen, pPopSize, pEval, seed){
		this->setConfig(pMaxGen, pPopSize, pEval, seed);
	}

	Algorithm_DE_AOS::Algorithm_DE_AOS(Evaluate *pEval):Algorithm_DE(pEval){
		setConfig(Input::maxGen, Input::popSize, pEval, Input::seedValue);
	}

	void Algorithm_DE_AOS::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		Algorithm_DE::setConfig(pMaxGen, pPopSize, pEval, seed);

		//Set AOS
		aos = new AOS(manager_op_mt->getSize(), "DE");
	}

	//Run all DE
	void Algorithm_DE_AOS::runAll(){
		//Initialize the function
		eval->initialize();

		//Create pop
		if (pop.size() <= 0){
			createPop();
		}
		iBest = Tools::getBest(pop, eval);
		ostringstream extraHeader;
		extraHeader << " nEvals ";
		for (int i = 0; i < (int)manager_op_mt->getSize(); i++){
			extraHeader << manager_op_mt->getOperator(i)->getKey() << " ";
		}

		Tools::printHeaderInfo(pop, extraHeader.str(), false);

		int G = 0;
		while( ! Tools::isEndProcess(eval, pop[iBest]->getFitness()) ){
			//One generation
			run_generate(pop);
			eval->update(pop);

			iBest = Tools::getBest(pop, eval);
			ostringstream extra;
			extra << " " << eval->getNEvals() << " ";

			for (int i = 0; i < (int)manager_op_mt->getSize(); i++){
				extra << manager_op_mt->getTimes(i) << " ";
			}
			Tools::printGenerationInfo(G, pop, iBest, eval, extra.str() , false);

			G++;
		}

		//Finalize function
		eval->finalize();
	}

	void Algorithm_DE_AOS::run_generate(vector<IndividualPtr> &pop){
			vector<IndividualPtr> newPop;
			vector<IndividualPtr> offspring;
			int ng = 0;

			//Run one generation
			iBest = Tools::getBest(pop, eval);
			newPop.clear();
			while(ng < popSize  && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
				Input::currentIndividual = ng;
				offspring.clear();

				generateIndividual(ng, iBest, pop, offspring);

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

	//Generate individuals by application of an operator
	double Algorithm_DE_AOS::generateIndividual(int iCurrent, int iBest, vector<IndividualPtr> &pop, vector<IndividualPtr> &offspring){
		offspring.clear();

		Operator *op;
		double Cr = 0.9;

		//Select operator by AOS
		int indexOp = this->aos->SelectOperator();

		//Apply mutation
		op = this->manager_op_mt->getOperator(indexOp);
		this->manager_op_mt->setTimes(op->getKey(), this->manager_op_mt->getTimes(op->getKey()) + 1);

		//Index to current and best individuals in the population
		vector<int> index;
		index.clear();
		//Modified on 2012-May-21
		if ( ( (op->getKey()).find("CURRENT") >= 0 && (op->getKey()).find("CURRENT") < (op->getKey()).length() ) &&  ((op->getKey()).find("BEST") >= 0 && (op->getKey()).find("BEST") < (op->getKey()).length()) ){
			index.push_back(iCurrent);
			index.push_back(iBest);
		} else if ( (op->getKey()).find("CURRENT") >= 0 && (op->getKey()).find("CURRENT") < (op->getKey()).length() ){
			index.push_back(iCurrent);
		} else {
			index.push_back(iBest);
		}
		//end modification

		op->apply(pop, offspring, Input::F, index);
		//Calc the fitness of the offspring
		for (int i = 0; i < (int)offspring.size(); i++){
			//CrossOver
			int randJ = (int)Tools::newRand(0, dimensions);
			for (int j = 0; j < dimensions; j++){
				if (Tools::newRand(0, 1) > Cr && j != randJ){
					offspring[i]->setGene(j, pop[iCurrent]->getGene(j));
				}
			}

			eval->calcFitness(offspring[i]);
		}

		double wSum = 0.0;
		//Calc reward
		for (int i = 0; i < (int)offspring.size(); i++){
			double w = DBL_MAX;
			if (this->aos->AOS_technique < 5) w = 0.0;
			if (eval->compare(offspring[i], pop[iCurrent]) > 0){
				//Calc reward
				if (this->aos->AOS_technique < 5){
					w = fabs(offspring[i]->getFitness() - pop[iCurrent]->getFitness());
				} else
				if ( this->aos->aos_delta_fitness ){
					w = offspring[i]->getFitness() - pop[iCurrent]->getFitness();
				} else{ //To FAUC or FSUM
					w = offspring[i]->getFitness();
				}
			}
			//Apply reward to AOS
			applyReward(indexOp, w);
			wSum += w;
		}
		return wSum;
		//End generateIndividual
	}

	void Algorithm_DE_AOS::applyReward(int index, double w){
		this->aos->addReward(index, w);
		this->aos->ApplyReward(index);
	}
} /* namespace hybridAos */
} /* namespace opt */
