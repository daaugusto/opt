/*
 * Main.cpp
 *
 *  Created on: 03/02/2012
 *      Author: Eduardo Krempser
 *
 *  Description: Main function of the program, it includes the several configurations.
 */

#define TEST 0

#include "includes.h"
using namespace std;
using namespace opt::base;
using namespace opt::function;
using namespace opt::evaluate;
using namespace opt::operators;
using namespace opt::algorithm;
using namespace opt::hybridAos;
using namespace opt::surrogate;
using namespace opt::smde;
using namespace opt::slsde;
using namespace opt::esmde;
using namespace opt::blde;

Algorithm* selectAlgorithm(Evaluate *eval, Evaluate_Surrogate *evalSurrogate = NULL){
	if (Input::algorithm == "GA_AOS"){
		return new Algorithm_GA_AOS(eval);
	} else if (Input::algorithm == "DE_AOS"){
		return new Algorithm_DE_AOS(eval);
	} else if (Input::algorithm == "HYBRID_AOS"){
		return new Algorithm_Hybrid_AOS(eval);
	} else if (Input::algorithm == "HYBRIDOP_AOS"){
		return new Algorithm_HybridOp_AOS(eval);
	} else if (Input::algorithm == "GA"){
		return new Algorithm_GA(eval);
	} else if (Input::algorithm == "SMDE"){
		if (Input::sm == ""){
			throw new Exception("SMDE can't be initialized with out the sm definition  -- Main/selectAlgorithm");
		}
		return new Algorithm_SMDE(eval, evalSurrogate);
	} else if (Input::algorithm == "SMDE_AKNN"){
		if (Input::sm != "KNN"){
			throw new Exception("SMDE_aKnn can't be initialized with out the sm definition as KNN -- Main/selectAlgorithm");
		}
		return new Algorithm_SMDE_aKnn(eval, evalSurrogate);
	} else if (Input::algorithm == "SLSDE"){
		if (Input::sl == "NONE"){
			throw new Exception("SLSDE can't be initialized with out the sl definition -- Main/selectAlgorithm");
		}
		return new Algorithm_SLSDE(eval, evalSurrogate);
	} else if (Input::algorithm == "ESMDE"){
		return new Algorithm_ESMDE(eval, Input::sm);
	} else if (Input::algorithm == "BLDE"){
		if (Input::sm == ""){
			throw new Exception("BLDE can't be initialized with out the sm definition  -- Main/selectAlgorithm");
		}
		        //cout << "Main:Teste" << endl;
		return new Algorithm_BLDE(eval, evalSurrogate);
	} else {
		return new Algorithm_DE(eval);
	}
}

int main(int argc, char *argv[]){
	Input::setParams(argc, argv);
	Tools::generateSeed(Input::seedValue);

	if (!TEST){
		int fBBOB = 0;
		Function *funct;

		if (Input::idFunction <= -10000){ //-10001 is the SMD1
			//Bilevel Functions
			funct = new Function_SMD(Input::idFunction);
		} else if (Input::idFunction <= -10){
			//Truss Functions
			funct = new Function_Truss(Input::idFunction);
		} else if (Input::idFunction < 0){ //-1 - welded beam
			funct = new Function_Mechanic(Input::idFunction);
		} else if (Input::idFunction < 30){
			funct = new Function_G(Input::idFunction);
		} else if(Input::idFunction < 60) {
			funct = new Function_F(Input::idFunction);
		} else if(Input::idFunction < 80) {
			funct = new Function_Unconstrained(Input::idFunction);
		} else {
			funct = new Function_BBOB(Input::idFunction);
			fBBOB = 1;
		}

		Input::function = funct;

		Algorithm *alg;
		Evaluate *eval;

		if (Input::tEval == "BLDE"){
			eval = new Evaluate_BLDE(funct);
			//cout << "Main:tEval: " << Input::tEval  << endl;
		} else if (Input::tEval == "APM"){
			eval = new Evaluate_APM(funct);
		} else if (Input::tEval == "APMMON"){
			eval = new Evaluate_APM_Monotonic(funct);
		} else if (Input::tEval == "APMDAMP"){
			eval = new Evaluate_APM_Damping(funct);
		} else {
			eval = new Evaluate_Deb(funct);
		}

		//Select surrogate model
		Evaluate_Surrogate *evalSurrogate = NULL;
		if (Input::sm == "KNN"){
			int k = 0;
			std::istringstream stream(Input::smp);
			stream >> k;
			evalSurrogate = new Evaluate_Surrogate_NN(funct, k);
		} else if (Input::sm == "RNN"){
			float r = 0.0;
			std::istringstream stream(Input::smp);
			stream >> r;
			evalSurrogate = new Evaluate_Surrogate_NN(funct, r);
		} else if (Input::sm == "LWR"){
			float tal = 0.0;
			std::istringstream stream(Input::smp);
			stream >> tal;
			evalSurrogate = new Evaluate_Surrogate_LWR(funct, tal);
		} else if (Input::sm == "RBF"){
			float tal = 0.0;
			std::istringstream stream(Input::smp);
			stream >> tal;
			evalSurrogate = new Evaluate_Surrogate_RBF(funct, tal);
		} else if (Input::sm == SURROGATE_LLR){
			float tal = 0.0;
			std::istringstream stream(Input::smp);
			stream >> tal;
			evalSurrogate = new Evaluate_Surrogate_LLR(funct, tal);
		}

		alg = selectAlgorithm(eval, evalSurrogate);
//cout << "Main:Sel" << endl;
		if (fBBOB){
			delete alg;
			//Run 15 instances to BBOB
			for (int i = 1; i <= 15; i++){
				Input::idTest = i;
				alg = selectAlgorithm(eval, evalSurrogate);
				alg->reset();

				alg->runAll();

				delete alg;
			}
		} else {
//cout << "Main:run.1" << endl;
			alg->runAll();
//cout << "Main:run.2" << endl;
		}

		delete alg;
		delete funct;
		delete eval;
		delete evalSurrogate;

	} else {
		cout << " build !\n";

		Function_G *function = new Function_G(1);
		cout << "Individual test...\n";
		IndividualPtr ind1 = IndividualPtr(new Individual());
		ind1->initialize(function->getNDimensions());
		cout << " dim: " << ind1->getDimensions() << " ";
		cout << "i0: " << ind1->getGene(0) << "\n";
		cout << "ok!\n";
		cout << "Evaluate test...\n";
		Evaluate *eval = new Evaluate_Deb(function);
		cout << "eval. ind: " << eval->calcFitness(ind1);
		cout << " isValid: " << eval->isValid(ind1) << "\n";
		cout << "c0: " << ind1->getConstraint(0) << "\n";
		cout << "c1: " << ind1->getConstraint(1) << "\n";
		cout << "ok!\n";
		cout << "Pop test...\n";
		vector<IndividualPtr> pop;
		Input::popSize = 40;
		Input::maxGen = 100;
		for (int i = 0; i < Input::popSize; i++){
			pop.push_back(IndividualPtr(new Individual()));
			pop[i]->initialize(function->getNDimensions());
			eval->calcFitness(pop[i]);
			cout << " pop[" << i << "]: " << pop[i]->getFitness() << " isValid: " << pop[i]->isValid() << "\n";
		}
		cout << "Operator test...\n";
		Operator_MT_Rand *op = new Operator_MT_Rand();
		vector<IndividualPtr> off;
		op->apply(pop, off);
		cout << "\nNumber of off: " << off.size() << "\n";
		for(int i = 0; i < (int)off.size(); i++){
			eval->calcFitness(off[i]);
			cout << " off[" << i << "]: " << off[i]->getFitness() << " isValid: " << off[i]->isValid() << " ConstSum: " << off[i]->getSumConstraints() << "\n";
		}
		cout << "End off\n";
		cout << " Best: off[" << Tools::getBest(off, eval) << "]\n";
		cout << "ok!\n";
		cout << "Algorithm test...\n";
		Algorithm_GA *alg = new Algorithm_GA(eval);
		alg->runAll();
		cout << "ok!\n";

		cout << "\n\n--------------\n\nAOS test...\n";
		Input::aos = 5;
		eval->setNEvals(0);
		Algorithm_GA_AOS *algAOS = new Algorithm_GA_AOS(eval);
		algAOS->runAll();
		cout << "ok!\n";

		cout << "\n\n--------------\n\nBBOB test...\n";
		Input::idTest = 1;
		Input::dim    = 20;
		Function_BBOB *function_bbob = new Function_BBOB(1010);
		Evaluate *eval_bbob = new Evaluate_Deb(function_bbob);
		Algorithm_DE_AOS *alg_bbob = new Algorithm_DE_AOS(eval_bbob);
		alg_bbob->runAll();
		cout << "ok!\n";

		cout << "\n\n--------------\n\nHYBRID test...\n";
		Algorithm_Hybrid_AOS *alg_hybrid = new Algorithm_Hybrid_AOS(eval_bbob);
		alg_hybrid->runAll();
		cout << "ok!\n";

		cout << "\n\n--------------\n\nHYBRID_OP test...\n";
		Algorithm_HybridOp_AOS *alg_hybridOp = new Algorithm_HybridOp_AOS(eval_bbob);
		alg_hybridOp->runAll();
		cout << "ok!\n";
	}
}






