/*
 * BLDE.cpp
 * Surrogate Model For Bilevel Problems- Differential Evolution
 *
 *  Created on: 13/03/2019
 *      Author: Eduardo Krempser
 */

#include "Algorithm_BLDE_Follower.h"

namespace opt {
namespace blde {


Algorithm_BLDE_Follower::Algorithm_BLDE_Follower(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed, int dimFollower, IndividualPtr indLeader): Algorithm_DE(pMaxGen, pPopSize, pEval, seed){
	this->setConfig(pMaxGen, pPopSize, pEval, pEvalSur, napp, smp, seed, dimFollower, indLeader);
}

Algorithm_BLDE_Follower::Algorithm_BLDE_Follower(Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int dimFollower, IndividualPtr indLeader): Algorithm_DE(pEval){
	setConfig(Input::maxGen, Input::popSize, pEval, pEvalSur, Input::nap, Input::smp, Input::seedValue, dimFollower, indLeader);
}

//napp -> number of approximations
//smp -> surrogate parameters
void Algorithm_BLDE_Follower::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed, int dimFollower, IndividualPtr pIndLeader){
	Algorithm::setConfig(pMaxGen, pPopSize, pEval, seed);

	iBest = 0;

	//Set the variants by input params
	manager_op_mt = new Manager_Operator();
	this->addOperatorsByInput(manager_op_mt, "DE");

	//Set the surrogate variables
	this->nApp = napp;
	this->evalSurrogate = pEvalSur;

	//Receive the leader data
	this->indLeader = pIndLeader;

	//Receive the follower dimension 
	this->dimensionsFollower = dimFollower;
}

void Algorithm_BLDE_Follower::createExtraHeaderInfo(ostringstream &extra){
	extra << " nEvals nEvalSurrog bestSurrogat DiffApp SqRootMeanError MaxError MinError countAccept goodChoice";
}

void Algorithm_BLDE_Follower::createExtraGenerationInfo(ostringstream &extra, int iBest_){
	extra << " " << eval->getNEvals();
	extra << " " << evalSurrogate->getNEvals();
	extra << " " << pop[iBest_]->getFitnessSurrogate();
	extra << " " << fabs(pop[iBest_]->getFitness() - pop[iBest_]->getFitnessSurrogate());

	//Cacl the squared root mean error
	double sum = 0.0;
	double err = pop[0]->getFitness() - pop[0]->getFitnessSurrogate();
	double max = fabs(err);
	double min = max;
	for(int i = 1; i < popSize; i++){
		double fit = pop[i]->getFitness();
		double fitS = pop[i]->getFitnessSurrogate();
		err = fabs( pop[i]->getFitness() - pop[i]->getFitnessSurrogate() );
		sum += err*err;
		if ( err > max ){
			max = err;
		}
		if ( err < min ){
			min = err;
		}
	}
	extra << " " << ( sum/popSize ) << " " << max << " " << min << " " << (popSize - this->countErrors) << " " << this->goodChoice;
}

void Algorithm_BLDE_Follower::createPop(){
	for (int i = 0; i < popSize; i++){
		this->pop.push_back(IndividualPtr(new Individual()));
		vector<double> chromosome;
		chromosome.clear();
		for (int j = 0; j < this->dimensionsFollower; j++){
			double value = Tools::newRand(((Function_SMD*)Input::function)->getBoundMinFollower(j), ((Function_SMD*)Input::function)->getBoundMaxFollower(j));
			chromosome.push_back(value);
		}
		pop[i]->setChromosome(chromosome);
		((Evaluate_BLDE*)this->eval)->calcFitness(indLeader, this->pop[i], 2);
	}
}

//Run all DE
void Algorithm_BLDE_Follower::runAll(){
	Input::level = 2;

	//Initialize the function
	eval->initialize();
	//Create pop
	if (pop.size() <= 0){
		createPop();
		for( int i=0; i<pop.size(); i++ ) {
			pop[ i ]->setFitnessSurrogate( 0 );
			this->evalSurrogate->insert( pop[ i ] );
		}
	}

	//Stagnation control
	int countFit = 0;
	double oldFit = -100000;
	vector<double> var_inicial(this->dimensionsFollower);
	vector<double> var_atual(this->dimensionsFollower);
	Tools::calcVariance(pop, this->dimensionsFollower, var_inicial);
	int G = 0;
	while (G < this->maxGen){ //TODO: while( ! Tools::isEndProcess(eval, pop[iBest]->getFitness()) ){
		eval->update(pop);

		//Run one generation
		iBest = Tools::getBest(pop, eval);
		run_generate(pop);
		G++;

		//Stop criterion by precision (0.01) or stagnation
		if (fabs(pop[iBest]->getFitness()) < 0.01) break;
	        Tools::calcVariance(pop, this->dimensionsFollower, var_atual);
	        double soma_total = 0;
		for (int d = 0; d < this->dimensionsFollower; d++){
                        soma_total += var_atual[d] / var_inicial[d];
		}
		if (soma_total < 0.00001){
			break;
		}
	}
	//Finalize function
	eval->finalize();
	Input::level = 1;
}

void Algorithm_BLDE_Follower::run_generate(vector<IndividualPtr> &pop){
	vector<IndividualPtr> newPop;
	vector<IndividualPtr> offspring;
	vector<IndividualPtr> completeOffspring;
	Operator *op;
	int ng = 0;
	double Cr = 0.9;


	//Run one generation
	iBest = Tools::getBest(pop, eval);
	newPop.clear();

	this->countErrors = 0;
	this->goodChoice = 0;

	while(ng < popSize){//TODO:} && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
		Input::currentIndividual = ng;
		completeOffspring.clear();

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
				int randJ = (int)Tools::newRand(0, this->dimensionsFollower);
				for (int j = 0; j < this->dimensionsFollower; j++){
					double r = Tools::newRand(0, 1);
					if (r >= Cr && j != randJ){
						double v = pop[ng]->getGene(j);
						offspring[i]->setGene(j, v);
					}
				}

				//Evaluate the offspring by surrogate model
				evalSurrogate->calcFitness(offspring[i]);
				double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[ng]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
				offspring[i]->setInfoParam("EI", -EI);

				completeOffspring.push_back(offspring[i]);
			}
		}
		if (Input::sel.compare("Y") == 0){
			Tools::order(completeOffspring, evalSurrogate);
		} else {
			Tools::order(completeOffspring, evalSurrogate, "EI");
		}
		//Evaluate the best offspring by original fitness function
		((Evaluate_BLDE*)eval)->calcFitness(indLeader, completeOffspring[0], 2);
	        ((Evaluate_BLDE*)eval)->setNEvalsFollower( ((Evaluate_BLDE*)eval)->getNEvalsFollower() + 1 );

		evalSurrogate->insert(completeOffspring[0]);
		//Select new pop
		if (eval->compare(completeOffspring[0], pop[ng]) >= 0){
			newPop.push_back(completeOffspring[0]);
		} else {
			newPop.push_back(pop[ng]);
		}
		ng++;
	}
	pop = newPop;
}

IndividualPtr Algorithm_BLDE_Follower::getBest(){
	return pop[Tools::getBest(pop, eval)];
}

Algorithm_BLDE_Follower::~Algorithm_BLDE_Follower() {
	// TODO Auto-generated destructor stub
}

} /* namespace blde */
} /* namespace opt */
