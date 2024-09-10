/*
 * AlgorithmGAAOS.cpp
 *
 *  Created on: 16/02/2012
 *      Author: krempser
 */

#include "Algorithm_GA_AOS.h"

namespace opt {
namespace hybridAos {

	Algorithm_GA_AOS::Algorithm_GA_AOS(int pMaxGen, int pPopSize, Evaluate *pEval, int seed):Algorithm_GA(pMaxGen, pPopSize, pEval, seed){
		this->setConfig(pMaxGen, pPopSize, pEval, seed);
	}

	Algorithm_GA_AOS::Algorithm_GA_AOS(Evaluate *pEval):Algorithm_GA(pEval){
		setConfig(Input::maxGen, Input::popSize, pEval, Input::seedValue);
	}

	void Algorithm_GA_AOS::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		Algorithm_GA::setConfig(pMaxGen, pPopSize, pEval, seed);

		//Set AOS
		aos_mt = new AOS(manager_op_mt->getSize(), "GA");
		aos_cx = new AOS(manager_op_cx->getSize(), "GA");
	}

	//Run all DE
	void Algorithm_GA_AOS::runAll(){
		//Initialize the function
		eval->initialize();

		//Create pop
		if (pop.size() <= 0){
			createPop();
		}
		Tools::order(pop, eval);
		Tools::printHeaderInfo(pop,  " nEvals ", false);

		int G = 0;
		while( ! Tools::isEndProcess(eval, pop[0]->getFitness()) ){
			ostringstream extra;
			extra << " " << eval->getNEvals() << " ";
			Tools::printGenerationInfo(G, pop, 0, eval, extra.str(), false);

			//One generation
			run_generate(pop);
			eval->update(pop);

			G++;
		}

		Tools::order(pop, eval);

		//Finalize function
		eval->finalize();
	}


	void Algorithm_GA_AOS::run_generate(vector<IndividualPtr> &pop){
		vector<IndividualPtr> newPop;
		vector<IndividualPtr> offspring;

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
		//End-Elitismn
		while(ng < popSize && (! Tools::isEndProcess(eval, pop[0]->getFitness())) ){
			Input::currentIndividual = ng;
			offspring.clear();
			generateIndividual(ng, 0, pop, offspring);

			//Calc the fitness of the offspring
			for (int i = 0; i < (int)offspring.size(); i++){
				//elitism case
				newPop.push_back(offspring[i]);
				//end - elitism case
//Stand case
//int iWorst = Tools::getWorst(pop, eval);
//if (eval->compare(offspring[0], pop[iWorst]) >= 0){
//	pop[iWorst] = offspring[0];
//}
//end stand case
			}
			ng += (int)offspring.size();
		}
//elitism case
		pop = newPop;
//end - elitism case
	}

	int Algorithm_GA_AOS::selection(vector<IndividualPtr> &pop){
//	  double c = 2;
	  /*double max = 2, min = 0;
	  double r = Tools::newRand(0, 1.0);
	  int N = (int)pop.size()/2;
	  double sum = 0.0;*/
/*	  for (int i = 1; i <= N; i++){
		  //double  pi = ((c - 1)/(pow(c,N) - 1))*pow(c,(N-i));
		  double pi = 1/(double)N*(min + ((max - min)*(i - 1))/(N - 1));
		  sum += pi;
		  if (r < sum){
			  return N - i;
		  }
	  }
	  return 0;
*/
	  int pos = (int)(pow(Tools::newRand(0, 1), 2)*pop.size());
	  //cout << " xi: " << pos;
	  return pos;
	}

	double Algorithm_GA_AOS::generateIndividual(int iCurrent, int iBest, vector<IndividualPtr> &pop, vector<IndividualPtr> &offspring){
		vector<IndividualPtr> parents;
		vector<IndividualPtr> parents_Mt;
		Operator *op;

		vector<int> genValues;
		genValues.clear();
		genValues.push_back(this->eval->getNEvals()/Input::popSize);
		genValues.push_back(this->maxGen);
		parents.clear();
		parents_Mt.clear();

		//Select parents
		int ix1 = selection(pop);
		int ix2 = selection(pop);

		parents.push_back(pop[ix1]);
		parents.push_back(pop[ix2]);

		//Apply CrossOver
		int indexOpCx =  this->aos_cx->SelectOperator();
		op = this->manager_op_cx->getOperator(indexOpCx);
		op->apply(parents, offspring, 0.0, genValues);
		string cxKey = op->getKey();

		//Apply mutation in all children
		//parents_Mt = offspring;
		for(int i = 0; i < (int)offspring.size(); i++){
			parents_Mt.push_back(offspring[i]);
		}
//		offspring.clear();

		int indexOpMt =  this->aos_mt->SelectOperator();
		op = this->manager_op_mt->getOperator(indexOpMt);
//		op->apply(parents_Mt, offspring, 0.0, genValues);

		//To equilibrate the comparisons between DE and GA with AOS only the first child is used
		while ((int)offspring.size() > 1){
			offspring.pop_back();
		}

		//Calc the fitness of the offspring
		for (int i = 0; i < (int)offspring.size(); i++){
			eval->calcFitness(offspring[i]);
		}

		//Calc reward
		double w = DBL_MAX;
		if (this->aos_cx->AOS_technique < 5  ) w = 0.0;
		Tools::order(offspring, eval);
		Tools::order(parents, eval);

		if (eval->compare(offspring[0], parents[0]) > 0){
			if (this->aos_cx->AOS_technique < 5){
				w = fabs(offspring[0]->getFitness() - parents[0]->getFitness());
			} else
			if ( this->aos_cx->aos_delta_fitness ){
				w = offspring[0]->getFitness() - parents[0]->getFitness();
			} else {//if FAUC or FSUM
				w = offspring[0]->getFitness();
			}
		}
		applyRewardCx(indexOpCx, w);
		applyRewardMt(indexOpMt, w);
		return w;
	}

	void Algorithm_GA_AOS::applyRewardCx(int index, double w){
		this->aos_cx->addReward(index, w);
		this->aos_cx->ApplyReward(index);
	}

	void Algorithm_GA_AOS::applyRewardMt(int index, double w){
		this->aos_mt->addReward(index, w);
		this->aos_mt->ApplyReward(index);
	}

} /* namespace hybridAos */
} /* namespace opt */
