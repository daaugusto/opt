/*
 * Algorithm_SLSDE.cpp
 * Surrogate Local Search Differential Evolution
 *
 *
 *  Created on: 22/05/2012
 *      Author: krempser
 */

#include "Algorithm_SLSDE.h"

namespace opt {
namespace slsde {

Algorithm_SLSDE::Algorithm_SLSDE(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, string sl,  int seed):Algorithm_SMDE(pMaxGen, pPopSize, pEval, pEvalSur, napp, smp, seed) {
	this->setConfig(pMaxGen, pPopSize, pEval, pEvalSur, napp, smp, sl, seed);
}

Algorithm_SLSDE::Algorithm_SLSDE(Evaluate *pEval, Evaluate_Surrogate *pEvalSur):Algorithm_SMDE(pEval, pEvalSur) {
	setConfig(Input::maxGen, Input::popSize, pEval, pEvalSur, Input::nap, Input::smp, Input::sl, Input::seedValue);
}

void Algorithm_SLSDE::setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, string sl, int seed){
	this->sl   = sl;
    avgErr = 0.0;
    sumErr = 0.0;
}

Algorithm_SLSDE::~Algorithm_SLSDE() {
}

void Algorithm_SLSDE::createExtraHeaderInfo(ostringstream &extra){
	extra << " nEvals nEvalSurrog bestSurrogat DiffApp F";
	//Include the param F in the population
	for(int i = 0; i < (int)pop.size(); i++){
		pop[i]->setInfoParam("F", Tools::newRand(0, F_BOUND_MAX));

//		if (sl == LOCALSEARCH_SFLS){
			pop[i]->setInfoParam("CR", Tools::newRand(0, 1));
//		} else {
//			pop[i]->setInfoParam("CR", 0.9);
//		}
		evalSurrogate->insert(pop[i]);
	}
}

void Algorithm_SLSDE::createExtraGenerationInfo(ostringstream &extra){
	extra << " " << eval->getNEvals();
	extra << " " << evalSurrogate->getNEvals();
	extra << " " << pop[iBest]->getFitnessSurrogate();
	extra << " " << fabs(pop[iBest]->getFitness() - pop[iBest]->getFitnessSurrogate());
	extra << " " << pop[iBest]->getInfoParam("F") << " ";
}

void Algorithm_SLSDE::run_generate(vector<IndividualPtr> &pop){
	vector<IndividualPtr> newPop;
	vector<IndividualPtr> offspring;
	vector<IndividualPtr> completeOffspring;
	Operator *op;
	int ng = 0;
	//double Cr = 0.9;
	//Run one generation
	iBest = Tools::getBest(pop, eval);
	newPop.clear();
	this->evalSurrogate->update( this->eval );
	while(ng < popSize && (! Tools::isEndProcess(eval, pop[iBest]->getFitness())) ){
		Input::currentIndividual = ng;
		completeOffspring.clear();

		//op = manager_op_mt->getOperator(iOp%manager_op_mt->getSize());
		op = manager_op_mt->getOperator(0);
		vector<int> indexParent;
		indexParent.clear();
		if ( ( (op->getKey()).find("CURRENT") >= 0 && (op->getKey()).find("CURRENT") < (op->getKey()).length() ) &&
			 ( (op->getKey()).find("BEST")    >= 0 && (op->getKey()).find("BEST")    < (op->getKey()).length())) {
			indexParent.push_back(ng);
			indexParent.push_back(iBest);
		} else if ( (op->getKey()).find("CURRENT") >= 0 && (op->getKey()).find("CURRENT") < (op->getKey()).length() ){
			indexParent.push_back(ng);
		} else if ( (op->getKey()).find("BEST") >= 0 && (op->getKey()).find("BEST") < (op->getKey()).length() ){
			indexParent.push_back(iBest);
		}

		//Select parent
		vector<int> indexSelect = op->selectParents(pop);
		for(int iSel = 0; iSel < (int)indexSelect.size(); iSel++){
			indexParent.push_back(indexSelect[iSel]);
		}

		//Select genes to crossOver
		vector<int> indexCrossOver;
		int randJ = (int)Tools::newRand(0, dimensions);
		for (int j = 0; j < dimensions; j++){
			if (Tools::newRand(0, 1) > pop[ng]->getInfoParam("CR") && j != randJ){
				indexCrossOver.push_back(j);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////
		//Apply local search
		double F = localSearch(pop, ng, op, indexParent, indexCrossOver, nApp, sl);
		////////////////////////////////////////////////////////////////////////////////////////////

		//Apply operator with obtained F
		offspring.clear();
		op->apply(pop, offspring, F, indexParent);
		offspring[0]->setInfoParam("F", F);
		offspring[0]->setInfoParam("CR", pop[ng]->getInfoParam("CR"));

		//CrossOver with offspring[0]
		crossover(pop[ng], offspring[0], indexCrossOver);

		//Evaluate the offspring by surrogate model
		evalSurrogate->calcFitness(offspring[0]);

		completeOffspring.push_back(offspring[0]);


		//Evaluate the best offspring by original fitness function
		eval->calcFitness(completeOffspring[0]);
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

void Algorithm_SLSDE::crossover(IndividualPtr parent, IndividualPtr &off, vector<int> index){
	//CrossOver with offspring[0]
	for (int j = 0; j < (int)index.size(); j++){
		off->setGene(index[j], parent->getGene(index[j]));
	}
}

double Algorithm_SLSDE::localSearch(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> &indexCrossOver, int nApp, string sl){
	double F = pop[current]->getInfoParam("F");
//cout << "\nsl: " << sl;
	/////////////////////

	if (sl == LOCALSEARCH_SMHC || sl == LOCALSEARCH_SMGS){
		/*if (true){
			F = Tools::newRand(0, 1);
			if (Tools::newRand(0, 1) < 0.5){
				sl = LOCALSEARCH_SMHC;
			} else {
				sl = LOCALSEARCH_SMGS;
			}
		}else*/
		if (current == iBest /*|| Tools::newRand(0, 1) < 0.5*/)
		{
			//sl = LOCALSEARCH_SMGS;
			/*if (Tools::newRand(0, 1) < 0.5){
				sl = LOCALSEARCH_SMHC;
			} else {
				sl = LOCALSEARCH_SMGS;
			}*/
		} else {
			F = pop[current]->getInfoParam("F");
			//Define F
			double tal1 = 0.1;
			F = pop[current]->getInfoParam("F");
			if (Tools::newRand(0, 1) < tal1){
				F = Tools::newRand(0, 1);
			}
			return F;
		}

/*		F = pop[current]->getInfoParam("F");
		double tal1 = 0.1, tal2 = 0.1;
		double tal3 = 0.5;//0.03;
		double tal4 = 1.0;//0.04 + tal3;
		double rand5 = Tools::newRand(0, 1);
		double Fl = 0.1;
		double Fu = 0.9;
		if (current == iBest && rand5 < tal3){
			sl = LOCALSEARCH_SMGS;
			F = goldenSearch(pop, current, op, indexParent, indexCrossOver, nApp, sl);
		} else if (current == iBest && rand5 < tal4){
			sl = LOCALSEARCH_SMHC;
			F = hillClimb(pop, current, op, indexParent, indexCrossOver, nApp, sl);
		} else {
			F = pop[current]->getInfoParam("F");
			//Define F
			if (Tools::newRand(0, 1) < tal1){
				F = Fl + Fu*Tools::newRand(0, 1);
			}
			//Define Cr
			if (Tools::newRand(0, 1) < tal2){
				pop[current]->setInfoParam("CR", Tools::newRand(0, 1));
			}

			//Select genes to crossOver with the new CR
			indexCrossOver.clear();
			int randJ = (int)Tools::newRand(0, dimensions);
			for (int j = 0; j < dimensions; j++){
				if (Tools::newRand(0, 1) > pop[current]->getInfoParam("CR") && j != randJ){
					indexCrossOver.push_back(j);
				}
			}
		}
		return F;
*/


/*
		double r = Tools::newRand(0, 1);
		if (r < 0.0){
			sl = LOCALSEARCH_RAND;
		}else{
			if (r < 0.5){
				sl = LOCALSEARCH_SMHC;
			} else {
				sl = LOCALSEARCH_SMGS;
			}
		}
*/
	}
	/////////////////////
	if (sl == LOCALSEARCH_SMHC || sl == LOCALSEARCH_HC){
		// Define Cr ////////////////////////////////////
		if (Tools::newRand(0, 1) < 0.1){
			pop[current]->setInfoParam("CR", Tools::newRand(0, 1));
			//Select genes to crossOver with the new CR
			indexCrossOver.clear();
			int randJ = (int)Tools::newRand(0, dimensions);
			for (int j = 0; j < dimensions; j++){
				if (Tools::newRand(0, 1) > pop[current]->getInfoParam("CR") && j != randJ){
					indexCrossOver.push_back(j);
				}
			}
		}
		///////////////////////////////////////////////

		F = hillClimb(pop, current, op, indexParent, indexCrossOver, nApp, sl);
	}else if (sl == LOCALSEARCH_SMSP || sl == LOCALSEARCH_SP){

		// Define Cr ////////////////////////////////////
		if (Tools::newRand(0, 1) < 0.1){
			pop[current]->setInfoParam("CR", Tools::newRand(0, 1));
			//Select genes to crossOver with the new CR
			indexCrossOver.clear();
			int randJ = (int)Tools::newRand(0, dimensions);
			for (int j = 0; j < dimensions; j++){
				if (Tools::newRand(0, 1) > pop[current]->getInfoParam("CR") && j != randJ){
					indexCrossOver.push_back(j);
				}
			}
		}
		//////////////////////////////////////////////////

		F = split(pop, current, op, indexParent, indexCrossOver, nApp, sl);
	} else if (sl == LOCALSEARCH_GS || sl == LOCALSEARCH_SMGS){
		// Define Cr ////////////////////////////////////
		if (Tools::newRand(0, 1) < 0.1){
			pop[current]->setInfoParam("CR", Tools::newRand(0, 1));
			//Select genes to crossOver with the new CR
			indexCrossOver.clear();
			int randJ = (int)Tools::newRand(0, dimensions);
			for (int j = 0; j < dimensions; j++){
				if (Tools::newRand(0, 1) > pop[current]->getInfoParam("CR") && j != randJ){
					indexCrossOver.push_back(j);
				}
			}
		}
		//////////////////////////////////////////////////

		F = goldenSearch(pop, current, op, indexParent, indexCrossOver, nApp, sl);
	} else if (sl == LOCALSEARCH_RAND){
		F =  Tools::newRand(F_BOUND_MIN, F_BOUND_MAX);
	} else if (sl == LOCALSEARCH_SFLS){
		F = pop[current]->getInfoParam("F");
		double tal1 = 0.1, tal2 = 0.1;
		double tal3 = 0.03;
		double tal4 = 0.04 + tal3;
		double rand5 = Tools::newRand(0, 1);
		double Fl = 0.1;
		double Fu = 0.9;
		if (current == iBest && rand5 < tal3){
			F = goldenSearch(pop, current, op, indexParent, indexCrossOver, nApp, sl);
		} else if (current == iBest && rand5 < tal4){
			F = hillClimb(pop, current, op, indexParent, indexCrossOver, nApp, sl);
		} else {
			F = pop[current]->getInfoParam("F");
			//Define F
			if (Tools::newRand(0, 1) < tal1){
				F = Fl + Fu*Tools::newRand(0, 1);
			}
			//Define Cr
			if (Tools::newRand(0, 1) < tal2){
				pop[current]->setInfoParam("CR", Tools::newRand(0, 1));
			}

			//Select genes to crossOver with the new CR
			indexCrossOver.clear();
			int randJ = (int)Tools::newRand(0, dimensions);
			for (int j = 0; j < dimensions; j++){
				if (Tools::newRand(0, 1) > pop[current]->getInfoParam("CR") && j != randJ){
					indexCrossOver.push_back(j);
				}
			}
		}
	}

	return F;
}

double Algorithm_SLSDE::hillClimb(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> indexCrossOver, int nApp, string sl){
	vector<IndividualPtr> offspring;
	double F = pop[current]->getInfoParam("F");//Tools::newRand(F_BOUND_MIN, F_BOUND_MAX);
	double h = H_STEP;

	if (sl == LOCALSEARCH_SFLS){
		h = 0.1;
		nApp = 15;
	}

	double valF, valFinf, valFsup;
	offspring.clear();
	//Apply mutation and cross-over
	op->apply(pop, offspring, F, indexParent);
	crossover(pop[current], offspring[0], indexCrossOver);

	if (sl == LOCALSEARCH_SMHC){
		evalSurrogate->calcFitness(offspring[0]);
		valF = offspring[0]->getFitnessSurrogate();

		//Apply the Expected Improvement
		double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[current]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
		if (Input::sel.compare("Y") != 0){
			valF = -EI;
		}
		//End-EI application

		//if (evalSurrogate->getVariance() > ((Evaluate_Surrogate_RBF*)evalSurrogate)->getTal()) return Tools::newRand(0, 1);
		//if (valF == RAND_MAX){return F;} //09_07 //15/07
	} else {
		eval->calcFitness(offspring[0]);
		valF = offspring[0]->getFitness();
	}

	//nApp indicates the number of steps in local search by (exact or approximate) model
	for(int iApp = 0; iApp < nApp; iApp++){
		offspring.clear();
		//Apply mutation and cross-over
		op->apply(pop, offspring, F - h, indexParent);
		crossover(pop[current], offspring[0], indexCrossOver);
		if (sl == LOCALSEARCH_SMHC){
			evalSurrogate->calcFitness(offspring[0]);
			valFinf = offspring[0]->getFitnessSurrogate();

			//Apply the Expected Improvement
			double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[current]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
			if (Input::sel.compare("Y") != 0){
				valFinf = -EI;
			}
			//End-EI application

			//if (evalSurrogate->getVariance() > ((Evaluate_Surrogate_RBF*)evalSurrogate)->getTal()) return Tools::newRand(0, 1);
		} else {
			eval->calcFitness(offspring[0]);
			valFinf = offspring[0]->getFitness();
		}

		offspring.clear();
		//Apply mutation and cross-over
		op->apply(pop, offspring, F + h, indexParent);
		crossover(pop[current], offspring[0], indexCrossOver);
		if (sl == LOCALSEARCH_SMHC){
			evalSurrogate->calcFitness(offspring[0]);
			valFsup = offspring[0]->getFitnessSurrogate();

			//Apply the Expected Improvement
			double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[current]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
			if (Input::sel.compare("Y") != 0){
				valFsup = -EI;
			}
			//End-EI application

			//if (evalSurrogate->getVariance() > ((Evaluate_Surrogate_RBF*)evalSurrogate)->getTal()) return Tools::newRand(0, 1);
		} else {
			eval->calcFitness(offspring[0]);
			valFsup = offspring[0]->getFitness();
		}


		if (valF <= valFinf && valF <= valFsup){
			h = h/2;
		} else if (valFinf <= valFsup){
			F = F - h;
			valF = valFinf;
		} else {
			F = F + h;
			valF = valFsup;
		}
	}
	return F;
}

double Algorithm_SLSDE::split(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> indexCrossOver, int nApp, string sl){
	vector<IndividualPtr> offspring;

	double h = fabs(F_BOUND_MIN - F_BOUND_MAX)/nApp;
	double F = F_BOUND_MIN;
	double valF = 0, valFbest = RAND_MAX;
	double Fbest = F;

	//nApp indicates the number of steps in local search by (exact or approximate) model
	for(int iApp = 0; iApp < nApp; iApp++, F += h){
		offspring.clear();
		//Apply mutation and cross-over
		op->apply(pop, offspring, F, indexParent);
		crossover(pop[current], offspring[0], indexCrossOver);
		if (sl == LOCALSEARCH_SMSP){
			evalSurrogate->calcFitness(offspring[0]);
			valF = offspring[0]->getFitnessSurrogate();

			//Apply the Expected Improvement
			double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[current]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
			if (Input::sel.compare("Y") != 0){
				valF = -EI;
			}
			//End-EI application
		} else {
			eval->calcFitness(offspring[0]);
			valF = offspring[0]->getFitness();
		}

		if (valF < valFbest || iApp == 0){
			valFbest = valF;
			Fbest = F;
		}

	}
	return Fbest;
}

double Algorithm_SLSDE::goldenSearch(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> indexCrossOver, int nApp, string sl){
	vector<IndividualPtr> offspring;
		double /*F = Tools::newRand(0, 1);*/ F = pop[current]->getInfoParam("F");//Tools::newRand(F_BOUND_MIN, F_BOUND_MAX);
		double a = 0.1, b = 1.0; //defined in Neri2009
		double F1, F2, valF1, valF2, fi;

		if (sl == LOCALSEARCH_SFLS){
			nApp = 4;
		}

		//nApp indicates the number of steps in local search by (exact or approximate) model
		for(int iApp = 0; iApp < nApp; iApp++){
			offspring.clear();

			//calc new F values
			fi = (1 + sqrt(5))/2.0;
			F1 = b - (b - a)/fi;
			F2 = a + (b - a)/fi;

			//Apply mutation and cross-over
			op->apply(pop, offspring, F1, indexParent);
			crossover(pop[current], offspring[0], indexCrossOver);
			if (sl == LOCALSEARCH_SMGS){
				evalSurrogate->calcFitness(offspring[0]);
				valF1 = offspring[0]->getFitnessSurrogate();

				//Apply the Expected Improviment
				double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[current]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
				if (Input::sel.compare("Y") != 0){
					valF1 = -EI;
				}
				//End-EI application

				// Testa qualidade da aproximacao 26/09
				//if (evalSurrogate->getVariance() > ((Evaluate_Surrogate_RBF*)evalSurrogate)->getTal()) return Tools::newRand(0, 1); /*return F1;*/
			} else {
				eval->calcFitness(offspring[0]);
				valF1 = offspring[0]->getFitness();

				////////////////////////////////////////// Caso ideal -> origial == surrogate
				//eval->setNEvals(eval->getNEvals() - 1);
				//////////////////////////////////////////
			}

			offspring.clear();

			//Apply mutation and cross-over
			op->apply(pop, offspring, F2, indexParent);
			crossover(pop[current], offspring[0], indexCrossOver);
			if (sl == LOCALSEARCH_SMGS){
				evalSurrogate->calcFitness(offspring[0]);
				valF2 = offspring[0]->getFitnessSurrogate();

				//Apply the Expected Improviment
				double EI = evalSurrogate->calcEI(evalSurrogate->getMean(), pop[current]->getFitness(), evalSurrogate->getMean(), evalSurrogate->getVariance());
				if (Input::sel.compare("Y") != 0){
					valF2 = -EI;
				}
				//End-EI application

				// Testa qualidade da aproximacao 26/09
				//cout << "\n var: " << evalSurrogate->getVariance() << " valF " << valF2;
				//if (evalSurrogate->getVariance() > ((Evaluate_Surrogate_RBF*)evalSurrogate)->getTal()) return Tools::newRand(0, 1); /*return F2;*/
				//cout << "\n ValF2: " << valF2;
			} else {
				eval->calcFitness(offspring[0]);
				valF2 = offspring[0]->getFitness();

				////////////////////////////////////////// Caso ideal -> origial == surrogate
				//eval->setNEvals(eval->getNEvals() - 1);
				//////////////////////////////////////////
			}

			if (valF1 < valF2){
				b = F2;
				F = b;
			} else {
				a = F1;
				F = a;
			}
		}
		return F;
}

} /* namespace slsde */
} /* namespace opt */
