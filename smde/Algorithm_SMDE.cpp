/*
 * SMDE.cpp
 * Surrogate Model - Differential Evolution
 *
 *  Created on: 17/04/2012
 *      Author: Eduardo Krempser
 */

#include "Algorithm_SMDE.h"

namespace opt {
namespace smde {


Algorithm_SMDE::Algorithm_SMDE(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed): Algorithm_DE(pMaxGen, pPopSize, pEval, seed){
	this->setConfig(pMaxGen, pPopSize, pEval, pEvalSur, napp, smp, seed);
}

Algorithm_SMDE::Algorithm_SMDE(Evaluate *pEval, Evaluate_Surrogate *pEvalSur): Algorithm_DE(pEval){
	setConfig(Input::maxGen, Input::popSize, pEval, pEvalSur, Input::nap, Input::smp, Input::seedValue);
}

//napp -> number of approximations
//smp -> surrogate parameters
void Algorithm_SMDE::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed){
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
	this->evalSurrogate = pEvalSur;
}

void Algorithm_SMDE::createExtraHeaderInfo(ostringstream &extra){
	extra << " nEvals nEvalSurrog bestSurrogat DiffApp SqRootMeanError MaxError MinError countAccept goodChoice";
}

void Algorithm_SMDE::createExtraGenerationInfo(ostringstream &extra, int iBest_){
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

//Run all DE
void Algorithm_SMDE::runAll(){
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
//	iBest = Tools::getBest(pop, eval);
	int iBest_;
	ostringstream extraHeader;
	createExtraHeaderInfo(extraHeader);
	Tools::printHeaderInfo(pop, extraHeader.str(), false);

	int G = 0;
	while( ! Tools::isEndProcess(eval, pop[iBest]->getFitness()) ){
		eval->update(pop);

		//One generation
		iBest = Tools::getBest(pop, eval);
		//iBest = Tools::getBestFeasible(pop, eval);
		run_generate(pop);

		iBest_ = Tools::getBestFeasible(pop, eval);
		ostringstream extra;
		createExtraGenerationInfo(extra, iBest_);
		Tools::printGenerationInfo(G, pop, iBest_, eval, extra.str(), false);
		G++;
	}

	//Finalize function
	eval->finalize();
}

void Algorithm_SMDE::run_generate(vector<IndividualPtr> &pop){
/*
	cout << "\n------\nPop: \n" << endl;
	for(int i = 0; i < (int)pop.size(); i++){
		cout << " Ind " << i << ": ";
		for(int j = 0; j < dimensions; j++){
			cout << pop[i]->getGene(j) <<  "  ";
		}
		cout << " Fit: " << pop[i]->getFitness() << endl;
	}
*/
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

	this->evalSurrogate->update( this->eval );

	while(ng < popSize && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
		Input::currentIndividual = ng;
		completeOffspring.clear();
		//Apply mutation

//		cout << "Inicio operadores ======>" << endl;
		for(int iOp = 0; iOp < nApp; iOp++){
			offspring.clear();
			op = manager_op_mt->getOperator(iOp%manager_op_mt->getSize());

//			cout << "Op: " << op->getKey() << "----->" << endl;
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
					double r = Tools::newRand(0, 1);
					if (r >= Cr && j != randJ){
						double v = pop[ng]->getGene(j);
						offspring[i]->setGene(j, v);
					}
				}

				//Evaluate the offspring by surrogate model
				evalSurrogate->calcFitness(offspring[i]);

				eval->calcFitness(offspring[i]);

//				cout << "\n Mean: " << evalSurrogate->getMean() << " Var: " << evalSurrogate->getVariance() << " ";
//				cout << "\n EI: " << evalSurrogate->calcEI(evalSurrogate->getMean(), pop[ng]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance()) << " y: " << evalSurrogate->getMean();
//				eval->calcFitness(offspring[i]);
//				cout << " Y: " << offspring[i]->getFitness() << " yMin: " << pop[ng]->getFitness() << endl;
//				offspring[i]->setFitnessSurrogate(- evalSurrogate->calcEI(evalSurrogate->getMean(), pop[ng]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance()));
				double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[ng]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
				offspring[i]->setInfoParam("EI", -EI);

				completeOffspring.push_back(offspring[i]);
			}
//			cout << "<-----" << endl;
		}
//		cout << "<====== Fim operadores" << endl;
		//Select the offspring by surrogate model
/*		cout << "\n -----------------";
		for (int i =0; i < completeOffspring.size(); i++){
			eval->calcFitness(completeOffspring[i]);
			cout <<  "\n Y: " << completeOffspring[i]->getFitness()
				 << " ŷ: "    << completeOffspring[i]->getFitnessSurrogate()
				 << " dif: "  << completeOffspring[i]->getFitness() - completeOffspring[i]->getFitnessSurrogate()
				 << " EI: "   << completeOffspring[i]->getInfoParam("EI");
		}
		cout << "\n ----------------- \n";
*/
        eval->setNEvals( eval->getNEvals() - completeOffspring.size() );

//        cout << "Antes antes" << endl;
//        for( int i=0; i< completeOffspring.size(); i++ ) {
//            cout << "i: " << i << " | Fitness: " << completeOffspring[i]->getFitness() << " | Predicted: " << completeOffspring[i]->getFitnessSurrogate() << endl;
//		}

        Tools::order(completeOffspring, eval);
        double d = completeOffspring[ 0 ]->getFitness();

//        cout << "Antes" << endl;
//        for( int i=0; i< completeOffspring.size(); i++ ) {
//            cout << "i: " << i << " | Fitness: " << completeOffspring[i]->getFitness() << " | Predicted: " << completeOffspring[i]->getFitnessSurrogate() << endl;
//		}

		if (Input::sel.compare("Y") == 0){
			Tools::order(completeOffspring, evalSurrogate);
			//random_shuffle( completeOffspring.begin(), completeOffspring.end() );
		} else {
			Tools::order(completeOffspring, evalSurrogate, "EI");
		}

		this->countErrors += d != completeOffspring[ 0 ]->getFitness()? 1: 0;
		this->goodChoice += ( eval->compare(completeOffspring[0], pop[ng]) >= 0 || d == completeOffspring[ 0 ]->getFitness()) ? 1: 0;

//        cout << "Depois" << endl;
//		for( int i=0; i< completeOffspring.size(); i++ ) {
//            cout << "i: " << i << " | Fitness: " << completeOffspring[i]->getFitness() << " | Predicted: " << completeOffspring[i]->getFitnessSurrogate() << endl;
//		}

		//Evaluate the best offspring by original fitness function
		eval->calcFitness(completeOffspring[0]);
		evalSurrogate->insert(completeOffspring[0]);

		//Select new pop
		if (eval->compare(completeOffspring[0], pop[ng]) >= 0){
			newPop.push_back(completeOffspring[0]);
		} else {
			newPop.push_back(pop[ng]);
		}
//		cout << "\nFit ng(" << ng << "): " << completeOffspring[0]->getFitness() << endl;
		ng++;
	}
	pop = newPop;
}


Algorithm_SMDE::~Algorithm_SMDE() {
	// TODO Auto-generated destructor stub
}

} /* namespace smde */
} /* namespace opt */
