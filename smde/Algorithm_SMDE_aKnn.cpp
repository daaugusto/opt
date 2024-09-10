/*
 * Algorithm_SMDE_aKnn.cpporithmSMDEaKnn.cpp
 *
 *  Created on: 04/05/2012
 *      Author: krempser
 */

#include "Algorithm_SMDE_aKnn.h"

using namespace opt::base;
using namespace opt::algorithm;
using namespace opt::surrogate;


namespace opt {
namespace smde {

	Algorithm_SMDE_aKnn::Algorithm_SMDE_aKnn(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed):Algorithm_SMDE(pMaxGen, pPopSize, pEval, pEvalSur, napp, smp, seed){

	}
	Algorithm_SMDE_aKnn::Algorithm_SMDE_aKnn(Evaluate *pEval, Evaluate_Surrogate *pEvalSur):Algorithm_SMDE(pEval, pEvalSur){

	}

	void Algorithm_SMDE_aKnn::createExtraHeaderInfo(ostringstream &extra){
		Algorithm_SMDE::createExtraHeaderInfo(extra);
		extra << " kValue";
	}

	void Algorithm_SMDE_aKnn::createExtraGenerationInfo(ostringstream &extra){
		Algorithm_SMDE::createExtraGenerationInfo(extra, this->iBest);
		string info = pop[iBest]->getInfoSurrogate();
		if (info == "" || info == "0"){
			info = "1";
		}
		extra << " " << info  << " ";
	}

	void Algorithm_SMDE_aKnn::run_generate(vector<IndividualPtr> &pop){
		vector<IndividualPtr> newPop;
		vector<IndividualPtr> offspring;
		vector<IndividualPtr> completeOffspring;
		Operator *op;
		int ng = 0;
		double Cr = 0.9;
		//Run one generation
		iBest = Tools::getBest(pop, eval);
		newPop.clear();
		while(ng < popSize && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
			completeOffspring.clear();
			//Define the K - parameter to generate the new individuals
			int kValue = 0;
			if (pop[ng]->getInfoSurrogate() == "" || pop[ng]->getInfoSurrogate() == "0"){
				kValue = (int)Tools::newRand(1, 10);
			} else {
				kValue = atoi((pop[ng]->getInfoSurrogate()).c_str());;
			}
			evalSurrogate->setParam("",kValue);
			//Apply mutatio
			for(int iOp = 0; iOp < nApp; iOp++){
				offspring.clear();
				op = manager_op_mt->getOperator(iOp%manager_op_mt->getSize());
				vector<int> index;
				index.clear();
				if ( (op->getKey()).find("CURRENT") ){
					index.push_back(ng);
				} else {
					index.push_back(iBest);
				}
				op->apply(pop, offspring, Input::F, index);
				//Calc the fitness of the offspring
				for (int i = 0; i < (int)offspring.size(); i++){
					//CrossOver
					int randJ = (int)Tools::newRand(0, dimensions);
					for (int j = 0; j < dimensions; j++){
						if (Tools::newRand(0, 1) > Cr && j != randJ){
							offspring[i]->setGene(j, pop[ng]->getGene(j));
						}
					}
					//Evaluate the offspring by surrogate model
					evalSurrogate->calcFitness(offspring[i]);
					completeOffspring.push_back(offspring[i]);
				}
			}
			//Select the offspring by surrogate model
			Tools::order(completeOffspring, evalSurrogate);

			//Evaluate the best offspring by original fitness function
			eval->calcFitness(completeOffspring[0]);

			//Select new pop
			if (eval->compare(completeOffspring[0], pop[ng]) >= 0){
				//Search the best value to k
				double diff = fabs(completeOffspring[0]->getFitness() - completeOffspring[0]->getFitnessSurrogate());
				double surrogateFitnessFinal = completeOffspring[0]->getFitnessSurrogate();
				int oldKValue = kValue;
				for (int ik = 1; ik <= 10; ik++){
					if (ik != oldKValue){
						evalSurrogate->setParam("",ik);
						evalSurrogate->calcFitness(completeOffspring[0]);
						double newDiff = fabs(completeOffspring[0]->getFitness() - completeOffspring[0]->getFitnessSurrogate());
						if (diff > newDiff){
							kValue = ik;
							surrogateFitnessFinal = completeOffspring[0]->getFitnessSurrogate();
							diff = newDiff;
						}
					}
				}
				completeOffspring[0]->setFitnessSurrogate(surrogateFitnessFinal);
				//Convert int k value to string parameter
				std::string s;
				std::stringstream out;
				out << kValue;
				completeOffspring[0]->setInfoSurrogate(out.str());
				//end search
				newPop.push_back(completeOffspring[0]);
			} else {
				newPop.push_back(pop[ng]);
			}
			//Insert the new exact evaluation in surrogate model
			evalSurrogate->insert(completeOffspring[0]);
			ng++;
		}
		pop = newPop;
	}

} /* namespace function */
} /* namespace opt */
