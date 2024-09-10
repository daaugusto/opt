/*
 * AlgorithmHybridAOS.cpp
 *
 *  Created on: 16/02/2012
 *      Author: Eduardo Krempser
 */

#include "Algorithm_Hybrid_AOS.h"

namespace opt {
namespace hybridAos {

	Algorithm_Hybrid_AOS::Algorithm_Hybrid_AOS(int pMaxGen, int pPopSize, Evaluate *pEval, int seed):Algorithm(pMaxGen, pPopSize, pEval, seed){
		this->setConfig(pMaxGen, pPopSize, pEval, seed);
	}

	Algorithm_Hybrid_AOS::Algorithm_Hybrid_AOS(Evaluate *pEval):Algorithm(pEval){
		setConfig(Input::maxGen, Input::popSize, pEval, Input::seedValue);
	}

	void Algorithm_Hybrid_AOS::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		Algorithm::setConfig(pMaxGen, pPopSize, pEval, seed);

	    ga = new Algorithm_GA_AOS(pEval);
	    de = new Algorithm_DE_AOS(pEval);

		//Set AOS (DE and GA)
		aos = new AOS(2, "ALL");

		nDE = 0;
		nGA = 0;
	}

	//Run all DE
	void Algorithm_Hybrid_AOS::runAll(){
		//Initialize the function
		eval->initialize();

		//Create pop
		if (pop.size() <= 0){
			createPop();
		}
		iBest = Tools::getBest(pop, eval);
		//TODO adicionar a lista de operadores do Manager_Operator
		Tools::printHeaderInfo(pop, " nEvals nDE nGA", false);
		int G = 0;
		while( ! Tools::isEndProcess(eval, pop[iBest]->getFitness()) ){
			//One generation
			run_generate(pop);
			eval->update(pop);
			iBest = Tools::getBest(pop, eval);

			ostringstream extra;
			extra << " " << eval->getNEvals() << " " << nDE << " " << nGA << " ";
			Tools::printGenerationInfo(G, pop, iBest, eval, extra.str() , false);

			G++;
		}

		//Finalize function
		eval->finalize();
	}

	void Algorithm_Hybrid_AOS::run_generate(vector<IndividualPtr> &pop){
	    //Run one generation
	    //Average population
	    avgFitness = 0.0;
	    for(int i = 0; i < (int)pop.size(); i++){
	    	avgFitness += pop[i]->getFitness();
	    }
	    avgFitness = avgFitness/pop.size();
double oldBest = pop[iBest]->getFitness();
int iOldBest = iBest;

	    //Select algorithm
	    int algIndex = this->aos->SelectOperator();

	    if (algIndex == 0){
	    	//Run DE algorithm
	    	de->run_generate(pop);
	    	iBest = Tools::getBest(pop, eval);
	    	nDE++;
	    } else if (algIndex == 1){
	    	ga->run_generate(pop);
	    	nGA++;
	    	iBest = Tools::getBest(pop, eval);
	    } else {
	    	throw new Exception("The index of algorithm not found -- Algorithm_Hybrid_AOS/run_generate");
	    }

	    double newAvgFitness = 0.0;
		for(int i = 0; i < (int)pop.size(); i++){
			newAvgFitness += pop[i]->getFitness();
		}
		newAvgFitness = newAvgFitness/pop.size();

	    double w = DBL_MAX;
	    if (this->aos->AOS_technique < 5) w = 0.0;
		/*if (newAvgFitness < avgFitness){
			if (this->aos->AOS_technique < 5){
				w = fabs(newAvgFitness - avgFitness);
			} else
			if ( this->aos->aos_delta_fitness ){
				w = newAvgFitness - avgFitness;
			} else{ //if FAUC or FSUM
				w = newAvgFitness;
			}
		}*/
	    if (oldBest < pop[iBest]->getFitness()){
			if (this->aos->AOS_technique < 5){
				w = fabs(oldBest - pop[iBest]->getFitness());
			} else
			if ( this->aos->aos_delta_fitness ){
				w = pop[iBest]->getFitness() - oldBest;
			} else{ //To FAUC or FSUM
				w = pop[iBest]->getFitness();
			}
	    }

		//Update rewards
	    this->aos->addReward(algIndex, w);
	    this->aos->ApplyReward(algIndex);
	}

	void Algorithm_Hybrid_AOS::reset(){
		Algorithm::reset();
		nDE = 0;
		nGA = 0;
	}

} /* namespace hybridAos */
} /* namespace opt */
