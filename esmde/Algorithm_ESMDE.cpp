/*
 * Algorithm_EESMDE.cpp
 * Ensemble Surrogate Model Differential Evolution
 *
 *  Created on: 23/07/2012
 *      Author: Eduardo Krempser
 */

#include "Algorithm_ESMDE.h"

namespace opt {
namespace esmde {


Algorithm_ESMDE::Algorithm_ESMDE(int pMaxGen, int pPopSize, Evaluate *pEval, string surrogate_names, int napp, string smp, int seed): Algorithm_SMDE(pMaxGen, pPopSize, pEval, NULL, napp, smp, seed){
	this->setConfig(pMaxGen, pPopSize, pEval, surrogate_names, napp, smp, seed);
}

Algorithm_ESMDE::Algorithm_ESMDE(Evaluate *pEval, string surrogate_names): Algorithm_SMDE(pEval, NULL){
	setConfig(Input::maxGen, Input::popSize, pEval, surrogate_names, Input::nap, Input::smp, Input::seedValue);
}

//napp -> number of approximations
//smp -> surrogate parameters
void Algorithm_ESMDE::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, string surrogate_names, int napp, string smp, int seed){
	Algorithm::setConfig(pMaxGen, pPopSize, pEval, seed);

	iBest = 0;
	//If necessary generate initial random value
	if (seed != 0)
		Tools::generateSeed(seed);

	//Set the variants by input params
	manager_op_mt = new Manager_Operator();
	this->addOperatorsByInput(manager_op_mt, "DE");

	//Set the surrogate variables
	this->nApp = napp;

	//Set the surrogates by input params
	this->manager_surrogate = new Manager_Surrogate();

	//Set the surrogate evaluates to manager
	setSurrogates(surrogate_names, pEval);

	//Define the AOS method to select surrogate
	aos = new AOS(manager_surrogate->getSize(), "ALL");
}


void Algorithm_ESMDE::addSurrogateByInput(Manager_Surrogate *manager, char name[10], char smp[7], Evaluate *pEval){
	Evaluate_Surrogate *eval = 0;
	if (strcmp(name, SURROGATE_KNN) == 0 ){
		int k = 0;
		//std::istringstream stream(Input::smp);
		std::istringstream stream(smp);
		stream >> k;
		eval = new Evaluate_Surrogate_NN(pEval->getFunction(), k);
	} else if (strcmp(name, SURROGATE_RNN) == 0){
		float r = 0.0;
		//std::istringstream stream(Input::smp);
		std::istringstream stream(smp);
		stream >> r;
		eval = new Evaluate_Surrogate_NN(pEval->getFunction(), r);
	} else if (strcmp(name, SURROGATE_LWR) == 0){
		float tal = 0.0;
		std::istringstream stream(smp);
		stream >> tal;
		eval = new Evaluate_Surrogate_LWR(pEval->getFunction(), tal);
	} else if (strcmp(name, SURROGATE_RBF) == 0){
		float tal = 0.0;
		std::istringstream stream(smp);
		stream >> tal;
		eval = new Evaluate_Surrogate_RBF(pEval->getFunction(), tal);
	}  else if (strcmp(name, SURROGATE_LLR) == 0){
		//TODO -- to implement the weighted version -- last parameter equals to true
		eval = new Evaluate_Surrogate_LLR(pEval->getFunction(), false);
	}
	if (eval != 0){
		manager->addSurrogate(eval->getKey(), eval);
	} else {
		throw new Exception("Surrogate name didn't find -- Algorithm_ESMDE.cpp/addSurrogateByInput");
	}
}

void Algorithm_ESMDE::setSurrogates(string surrogate_names, Evaluate *pEval){
	int len = surrogate_names.size();
	int lenSMP = Input::smp.size();

	int iSMP = 0;
	for (int l = 0, lSMP =  0; l < len; l++, lSMP++){
		char res[10];
		char smp[7];
		int j = 0;
		while(surrogate_names[l] != '-' && l < len){
			res[j++] = surrogate_names[l++];
		}
		res[j] = 0;

		iSMP = 0;
		while(Input::smp[lSMP] != '-' && lSMP < lenSMP){
			smp[iSMP++] = Input::smp[lSMP++];
		}
		smp[iSMP] = 0;

		this->addSurrogateByInput(manager_surrogate, res, smp, pEval);
	}
}

void Algorithm_ESMDE::createExtraHeaderInfo(ostringstream &extra){
	extra << " nEvals nEvalSurrog bestSurrogat DiffApp Surrogate";
}

void Algorithm_ESMDE::createExtraGenerationInfo(ostringstream &extra){
	extra << " " << eval->getNEvals();
	extra << " " << evalSurrogate->getNEvals();
	extra << " " << pop[iBest]->getFitnessSurrogate();
	extra << " " << fabs(pop[iBest]->getFitness() - pop[iBest]->getFitnessSurrogate());
	if (pop[iBest]->getInfoSurrogate() == ""){
		extra << " " << "EXACT" << " ";
	} else {
		extra << " " << pop[iBest]->getInfoSurrogate() << " ";
	}
}

//Run all DE
void Algorithm_ESMDE::runAll(){
	//Initialize the function
	eval->initialize();

	//Create pop
	if (pop.size() <= 0){
		createPop();
	}
	for (int i = 0; i < (int)pop.size(); i++){
		insertIndividualInSurrogate(pop[i]);
	}

	iBest = Tools::getBest(pop, eval);
	ostringstream extraHeader;
	createExtraHeaderInfo(extraHeader);
	Tools::printHeaderInfo(pop, extraHeader.str(), false);

	int G = 0;
	while( ! Tools::isEndProcess(eval, pop[iBest]->getFitness()) ){
		eval->update(pop);

		//One generation
		run_generate(pop);

		iBest = Tools::getBest(pop, eval);

		ostringstream extra;
		createExtraGenerationInfo(extra);

		Tools::printGenerationInfo(G, pop, iBest, eval, extra.str(), false);
		G++;
	}

	//Finalize function
	eval->finalize();
}

void Algorithm_ESMDE::run_generate(vector<IndividualPtr> &pop){
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
		Input::currentIndividual = ng;
		completeOffspring.clear();

		//Select the surrogate by AOS
		int indexSurrogate = this->aos->SelectOperator();
		evalSurrogate = manager_surrogate->getSurrogate(indexSurrogate);

		//Apply mutation
		for(int iOp = 0; iOp < nApp; iOp++){
			offspring.clear();
			op = manager_op_mt->getOperator(iOp%manager_op_mt->getSize());
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
				offspring[i]->setInfoSurrogate(evalSurrogate->getKey());
			}
		}

		//Select the offspring by surrogate model
		Tools::order(completeOffspring, evalSurrogate);
		//Evaluate the best offspring by original fitness function
		eval->calcFitness(completeOffspring[0]);

		insertIndividualInSurrogate(completeOffspring[0]);
		//evalSurrogate = manager_surrogate->getSurrogate(offspring[0]->getInfoSurrogate());
		//evalSurrogate->insert(completeOffspring[0]);


		//Select new pop
		if (eval->compare(completeOffspring[0], pop[ng]) >= 0){
			newPop.push_back(completeOffspring[0]);
		} else {
			newPop.push_back(pop[ng]);
		}

		///////AOS reward
		double w = DBL_MAX;
		if (this->aos->AOS_technique < 5){
			w = fabs(offspring[0]->getFitness() - offspring[0]->getFitnessSurrogate());
		} else
		if ( this->aos->aos_delta_fitness ){
			w = fabs(offspring[0]->getFitness() - offspring[0]->getFitnessSurrogate());
		} else{ //To FAUC or FSUM
			w = fabs(offspring[0]->getFitness() - offspring[0]->getFitnessSurrogate()); //offspring[0]->getFitness();
		}
		this->applyReward(indexSurrogate, w);
		/////////////////////////

		ng++;
	}
	pop = newPop;
}

void Algorithm_ESMDE::applyReward(int index, double w){
	this->aos->addReward(index, w);
	this->aos->ApplyReward(index);
}

void Algorithm_ESMDE::insertIndividualInSurrogate(IndividualPtr ind){
	for(int i = 0; i < manager_surrogate->getSize(); i++){
		manager_surrogate->getSurrogate(i)->insert(ind);
	}
}


Algorithm_ESMDE::~Algorithm_ESMDE() {
	// TODO Auto-generated destructor stub
}


} /* namespace eESMDE */
} /* namespace opt */
