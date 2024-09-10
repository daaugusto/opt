/*
 * BLDE.cpp
 * Surrogate Model For Bilevel Problems- Differential Evolution
 *
 *  Created on: 13/03/2019
 *      Author: Eduardo Krempser
 */

#include "Algorithm_BLDE.h"

namespace opt {
namespace blde {


Algorithm_BLDE::Algorithm_BLDE(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed): Algorithm_DE(pMaxGen, pPopSize, pEval, seed){
	this->setConfig(pMaxGen, pPopSize, pEval, pEvalSur, napp, smp, seed);
	this->smp = smp;
}

Algorithm_BLDE::Algorithm_BLDE(Evaluate *pEval, Evaluate_Surrogate *pEvalSur): Algorithm_DE(pEval){
	setConfig(Input::maxGen, Input::popSize, pEval, pEvalSur, Input::nap, Input::smp, Input::seedValue);
}

//napp -> number of approximations
//smp -> surrogate parameters
void Algorithm_BLDE::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed){
	Algorithm::setConfig(pMaxGen, pPopSize, pEval, seed);

	iBest = 0;

	//Set the variants by input params
	manager_op_mt = new Manager_Operator();
	this->addOperatorsByInput(manager_op_mt, "DE");

	//Set the surrogate variables
	this->nApp = napp;
	this->nAppF = Input::napF;
	this->evalSurrogate = pEvalSur;
	this->smp = smp;
	this->realEvals = 0;
	this->dimensionsFollower = ((Function_SMD*)pEval->getFunction())->getDIMF(); //3 - TODO: criar parâmetro para o o popsize do follower
}

void Algorithm_BLDE::createExtraHeaderInfo(ostringstream &extra){
	extra << " nEvals nEvalSurrog bestSurrogat DiffApp SqRootMeanError MaxError MinError countAccept goodChoice";
	for (int i = 0; i < this->dimensionsFollower; i++){
		extra << " xf" << i;
	}
	extra << " fFitness nEvalFollower";
}

void Algorithm_BLDE::createExtraGenerationInfo(ostringstream &extra, int iBest_){
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

	//Include follower information
	extra << " " << pop[iBest_]->getInfoExtra() << " " << ((Evaluate_BLDE*)eval)->getNEvalsFollower();
}

double Algorithm_BLDE::extractFitnessFollower(int iBest){
    string extra = pop[iBest]->getInfoExtra();
    string buff{""};
	vector<string> v;

	if (extra == "") return 100000.0;
	for(auto n:extra)
	{
		if(n != ' ') buff+=n; else
		if(n == ' ' && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	return std::stod(v[v.size()-1]);

}

//Create the follower population
void Algorithm_BLDE::createPopFollower(){
	for (int i = 0; i < popSize; i++){
		this->popFollower.push_back(IndividualPtr(new Individual()));
		this->popFollower[i]->initialize(this->dimensionsFollower);
		((Evaluate_BLDE*)eval)->calcFitness(pop[i], popFollower[i], 2);
	}
}

//Run all DE
void Algorithm_BLDE::runAll(){
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

	//Create follower pop
	if (popFollower.size() <= 0){
		createPopFollower();
		for( int i=0; i<pop.size(); i++ ) {
			popFollower[ i ]->setFitnessSurrogate( 0 );
		}
	}

	//Evaluate the individual (leader variables and follower variables)
	for( int i=0; i<pop.size(); i++ ) {
		Algorithm_BLDE_Follower *deFollower = new Algorithm_BLDE_Follower(Input::maxGenF, Input::popSizeF, eval, evalSurrogate, nAppF, smp, 1, this->dimensionsFollower, pop[i]);
//TODO:rever		deFollower->setConfig(Input::maxGenF, Input::popSizeF, eval, evalSurrogate, nAppF, smp, 1, this->dimensionsFollower, pop[i]); //passa o leader calculado
		deFollower->runAll();
		IndividualPtr tmpFollower = deFollower->getBest();
		((Evaluate_BLDE*)eval)->calcFitness(pop[i], tmpFollower, 1);
		evalSurrogate->insert(pop[i]);

		//Insert in the additional information of individual the follower variables
		ostringstream extra;
		for (int k = 0; k < this->dimensionsFollower; k++){
			extra << " " << tmpFollower->getGene(k);
		}
		extra << " "<< tmpFollower->getFitness();
		pop[i]->setInfoExtra(extra.str());
    	}

	int iBest_;
	ostringstream extraHeader;
	createExtraHeaderInfo(extraHeader);
	Tools::printHeaderInfo(pop, extraHeader.str(), false);
	double olddiff = 0;
	int G = 0;
	while(this->realEvals < this->popSize * this->maxGen){ //TODO: while (G < this->maxGen){ //while( ! Tools::isEndProcess(eval, pop[iBest]->getFitness()) ){
		eval->update(pop);

		//One generation
		iBest = Tools::getBest(pop, eval);
		run_generate(pop, popFollower);

		//Print information
		ostringstream extra;
		createExtraGenerationInfo(extra, iBest);
		Tools::printGenerationInfo(G, pop, iBest, eval, extra.str(), false);
		G++;

		//Stop criterion by precision (0.01)
		if (fabs(pop[iBest]->getFitness()) < 0.01 && fabs(extractFitnessFollower(iBest)) < 0.01) break;
	}
	//Finalize function
	eval->finalize();
}

void Algorithm_BLDE::run_generate(vector<IndividualPtr> &pop, vector<IndividualPtr> &popFollower){
	vector<IndividualPtr> newPop;
	vector<IndividualPtr> newPopFollower;
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

	while(ng < popSize){//TODO: while(ng < popSize && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
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

				double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[ng]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
				offspring[i]->setInfoParam("EI", -EI);
				completeOffspring.push_back(offspring[i]);
			}
		}
	        //Tools::order(completeOffspring, eval);
		if (Input::sel.compare("Y") == 0){
			Tools::order(completeOffspring, evalSurrogate);
		} else {
			Tools::order(completeOffspring, evalSurrogate, "EI");
		}
		//Evaluate the best offspring by original fitness function
		//Aqui o bilevel busca no DE do seguidor as variáveis que completam o indivíduo
		Algorithm_BLDE_Follower *deFollower = new Algorithm_BLDE_Follower(Input::maxGenF, Input::popSizeF, eval, evalSurrogate, nAppF, smp, 1, this->dimensionsFollower, completeOffspring[0]);

		deFollower->setConfig(Input::maxGenF, Input::popSizeF, eval, evalSurrogate, nAppF, smp, 1, this->dimensionsFollower, completeOffspring[0]); //passa o leader calculado
		deFollower->runAll();
		IndividualPtr tmpFollower = deFollower->getBest();
		//Fim do DE do seguidor

		((Evaluate_BLDE*)eval)->calcFitness(completeOffspring[0], tmpFollower, 1);
		this->realEvals++;
		eval->setNEvals(eval->getNEvals()+1);

		////TEST
		//Use recalculation strategy
		if (Input::recalc == 1){
			if ((completeOffspring[0]->getFitness() < pop[iBest]->getFitness()) && (tmpFollower->getFitness() > stod(pop[iBest]->getInfoExtra().substr(pop[iBest]->getInfoExtra().rfind(" "), pop[iBest]->getInfoExtra().size())) ) ){
			   deFollower->runAll();
			   tmpFollower = deFollower->getBest(); 
			   ((Evaluate_BLDE*)eval)->calcFitness(completeOffspring[0], tmpFollower, 1);
			   this->realEvals++;
			   eval->setNEvals(eval->getNEvals()+1); 
			//cout << "RECALC" << endl;
			}
		}
		///END-TEST

		//Insert the evaluation in the surrogate database
		evalSurrogate->insert(completeOffspring[0]);

		//Insert in the additional information of individual the follower variables
		ostringstream extra;
		for (int k = 0; k < this->dimensionsFollower; k++){
			extra << " " << tmpFollower->getGene(k);
		}
		extra << " "<< tmpFollower->getFitness();
		completeOffspring[0]->setInfoExtra(extra.str());

		//Evaluate the aproximation  quality
        	double d = completeOffspring[ 0 ]->getFitness();
		this->countErrors += d != completeOffspring[ 0 ]->getFitness()? 1: 0;
		this->goodChoice += ( eval->compare(completeOffspring[0], pop[ng]) >= 0 || d == completeOffspring[ 0 ]->getFitness()) ? 1: 0;

		//Select new pop
		if (eval->compare(completeOffspring[0], pop[ng]) >= 0){
			newPop.push_back(completeOffspring[0]);
			newPopFollower.push_back(tmpFollower);
		} else {
			newPop.push_back(pop[ng]);
			newPopFollower.push_back(popFollower[ng]);
		}
		ng++;
	}
	pop = newPop;
	popFollower = newPopFollower;
}


Algorithm_BLDE::~Algorithm_BLDE() {
	// TODO Auto-generated destructor stub
}

} /* namespace blde */
} /* namespace opt */
