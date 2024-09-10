/*
 * Algorithm.cpp
 *
 *  Created on: 09/02/2012
 *      Author: Eduardo Krempser
 */
#include "Algorithm.h"

namespace opt {
namespace algorithm {

	Algorithm::Algorithm(int pMaxGen, int pPopSize, Evaluate *pEval, int seed) {
	    this->setConfig(pMaxGen, pPopSize, pEval, seed);
	}

	Algorithm::Algorithm(Evaluate *pEval) {
		this->setConfig(Input::maxGen, Input::popSize, pEval, Input::seedValue);
	}

	void Algorithm::createPop(){
		for (int i = 0; i < popSize; i++){
			this->pop.push_back(IndividualPtr(new Individual()));
			this->pop[i]->initialize(this->dimensions);
			this->eval->calcFitness(this->pop[i]);
		}
	}

	void Algorithm::runAll(){

	}

	void Algorithm::run_generate(vector<IndividualPtr> &pop){

	}

	void Algorithm::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed){
		this->maxGen  = pMaxGen;
		this->popSize = pPopSize;
		this->dimensions = pEval->getFunction()->getNDimensions();
		this->eval = pEval;

		//If necessary generate initial random value
		//if (seed != 0)
		//	Tools::generateSeed(seed);
	}

	void Algorithm::addOperatorsByInput(Manager_Operator *manager, string type){
		Operator *op;
		//Case the variants weren't set include all variants
		if (type.compare("DE") == 0 || type.compare("ALL") == 0){
			if ((int)Input::opDE.size() <= 0){
				for(int i = 0; i < OP_DE_SIZE; i++){
					Input::opDE.push_back(i);
				}
			}
		}
		if (type.compare("GA") == 0 || type.compare("ALL") == 0 || type.compare("GA_CX") == 0 || type.compare("GA_MT") == 0){
			if ((int)Input::opGA.size() <= 0){
				for(int i = 0; i < OP_GA_SIZE; i++){
					Input::opGA.push_back(i);
				}
			}
		}

		//DE variants
		if (type == "DE" || type == "ALL"){
			for (int i = 0; i < (int)Input::opDE.size(); i++){
				op = 0;
				switch(Input::opDE[i]){
					case OP_DE_MT_BEST:{
						op = new Operator_MT_DE_Best();
					} break;
					case OP_DE_MT_CURRENT_RAND:{
						op = new Operator_MT_DE_Current_Rand();
					}break;
					case OP_DE_MT_RAND:{
						op = new Operator_MT_DE_Rand();
					}break;
					case OP_DE_MT_RAND_BEST:{
						op = new Operator_MT_DE_Rand_Best();
					}break;
					case OP_DE_MT_RAND2:{
						op = new Operator_MT_DE_Rand2();
					}break;
					case OP_DE_MT_CURRENT_BEST:{
						op = new Operator_MT_DE_Current_Best();
					}break;
				}
				if (op != 0)
					manager->addOperator(op->getKey(), op);
			}
		}
		//GA cross-over operators
		if (type == "GA" || type == "ALL" || type == "GA_CX"){
			for (int i = 0; i < (int)Input::opGA.size(); i++){
				op = 0;
				switch(Input::opGA[i]){
					case OP_GA_CX_1X:{
						op = new Operator_CX_1X();
					} break;
					case OP_GA_CX_BLXa:{
						op = new Operator_CX_BLXa();
					}break;
					case OP_GA_CX_SBX:{
						op = new Operator_CX_SBX();
					}break;
					case OP_GA_CX_UNIFORM:{
						op = new Operator_CX_Uniform();
					}break;
				}
				if (op != 0)
					manager->addOperator(op->getKey(), op);
			}
		}
		//GA mutation operators
		if (type == "GA" || type == "ALL" || type == "GA_MT"){
			for (int i = 0; i < (int)Input::opGA.size(); i++){
				op = 0;
				switch(Input::opGA[i]){
					case OP_GA_MT_DELTA:{
						op = new Operator_MT_Delta();
					}break;
					case OP_GA_MT_NONUNIFORM:{
						op = new Operator_MT_NonUniform();
					}break;
					case OP_GA_MT_RAND:{
						op = new Operator_MT_Rand();
					}break;
				}
				if (op != 0)
					manager->addOperator(op->getKey(), op);
			}
		}
	}

	//Reinitialize all components
	void Algorithm::reset(){
		pop.clear();
		eval->setNEvals(0);
	}

	Algorithm::~Algorithm() {
	}

} /* namespace operators */
} /* namespace opt */
