/*
 * Tools.cpp
 *
 *  Created on: 03/02/2012
 *      Author: Eduardo Krempser
 */

#include <algorithm>
#include "Tools.h"
#include "Input.h"
#include "../function/bbob/bbobStructures.h"

using namespace std;

namespace opt{
	namespace base {

		void Tools::generateSeed(int s){
			int seed = s;
			if (seed == -1){
				seed = time(NULL);
			}
			srand(seed);
		}

		double Tools::newRand(double min, double max){
			double r = (((double)rand()/RAND_MAX)*(max - min)) + min;
			//cout << " Tools::rand " << r << " min: " << min << " max: " << max << endl;
			return r;
		}

		//Treat the values out of basic bounds (0.0, 1.0)
		//The real bounds are converted in the function class
		double Tools::treatBasicBounds(double &x, int index){
			double bottom;
			double top;
			if (Input::normalized){
				bottom = 0;
				top = 1;
			} else {
				//Verify the bilevel case
				if (Input::algorithm == "BLDE" && Input::level == 2){
					bottom = ((Function_SMD*)Input::function)->getBoundMinFollower(index);
					top = ((Function_SMD*)Input::function)->getBoundMaxFollower(index);
				} else {
					bottom = Input::function->getBoundMin(index);
					top = Input::function->getBoundMax(index);
				}
			}

			/* Método original */
 			if (x > top){
				x = top;
			} else if (x < bottom){
				x = bottom;
			}
			return x;
		}

		double Tools::initializeGene(int index){
			double value;
			if (Input::normalized){
				value = Tools::newRand(0.0, 1.0);
			} else {
				value = Tools::newRand(Input::function->getBoundMin(index), Input::function->getBoundMax(index));
			}
			return value;
		}

		double Tools::convertToRealRange(int index, double val){
			if (Input::normalized){
				return ((val)*(Input::function->getBoundMax(index) - Input::function->getBoundMin(index))) + Input::function->getBoundMin(index);
			} else {
				return val;
			}
		}

		int Tools::getBest(vector<IndividualPtr> &pop, Evaluate *eval){
			int iBest = 0;
			for(int i = 1; i < (int)pop.size(); i++){
				if (eval->compare(pop[i], pop[iBest]) > 0){
					iBest = i;
				}
			}
			return iBest;
		}

		int Tools::getBestFeasible(vector<IndividualPtr> &pop, Evaluate *eval){
			int iBest = 0;
			for(int i = 1; i < (int)pop.size(); i++){
//				cout << pop[i]->getSumConstraints( ) << endl;
//				cout << (pop[i]->isValid()==0?"sim":"nao") << endl;
				if ( pop[i]->getSumConstraints( ) < pop[ iBest ]->getSumConstraints( ) ) {
					iBest = i;
				} else if ( pop[ i ]->getSumConstraints( ) <= 0 && pop[ iBest ]->getSumConstraints( ) <= 0 ) {
					if ( pop[i]->getFitness( ) < pop[iBest]->getFitness( ) ) {
						iBest = i;
					}
				}
			}
			return iBest;
		}

		int Tools::getWorst(vector<IndividualPtr> &pop, Evaluate *eval){
			int iWorst = 0;
			for(int i = 1; i < (int)pop.size(); i++){
				if (eval->compare(pop[i], pop[iWorst]) < 0){
					iWorst = i;
				}
			}
			return iWorst;
		}

		void Tools::order(vector<IndividualPtr> &pop, Evaluate *eval){
			IndividualPtr ind(new Individual());
			for(int i = 0; i < (int)pop.size(); i++){
				for(int j = i + 1; j < (int)pop.size(); j++){
					if (eval->compare(pop[j], pop[i]) > 0){
						IndividualPtr p = pop[i];
						pop[i] = pop[j];
						pop[j] = p;
					}
				}
			}
		}

		void Tools::order(vector<IndividualPtr> &pop, Evaluate *eval, string Param){
			IndividualPtr ind(new Individual());
			for(int i = 0; i < (int)pop.size(); i++){
				for(int j = i; j < (int)pop.size(); j++){
					if (pop[j]->getInfoParam(Param) < pop[i]->getInfoParam(Param)){
						IndividualPtr p = pop[i];
						pop[i] = pop[j];
						pop[j] = p;

					}
				}
			}
		}

		//Print one individual
		string Tools::printIndividual(IndividualPtr ind, Evaluate *eval, bool showConst){
			ostringstream result;
			result << "";
			double x;
			for (int i = 0; i < ind->getDimensions(); i++){
				if (eval == NULL){
					x = ind->getGene(i);
				} else {
					x = eval->getFunction()->convertToRealRange(i, ind->getGene(i));
				}
				result << x << " ";
			}

			//Constraints
			if (ind->getNConstraints() > 0 )
				result << "Const: ";
			for (int i = 0; i < ind->getNConstraints(); i++){
				result << " " << ind->getConstraint(i);
			}

			if (ind->isValid()){
				result << " [ valid ] ";
			} else {
				result << " [invalid (" << ind->getSumConstraints() << ") ] ";
			}

			if (ind->isEvaluatedExact()) result << " (" << ind->getFitness() << ") ";
			if (ind->isEvaluatedSurrogate()){
				result << " [Approximate: " << ind->getFitnessSurrogate() << "] ";
			}
			double kbest = eval->getFunction()->getBest();
			result << " { " << kbest - ind->getFitness() << " (" << 100*(kbest - ind->getFitness())/kbest << "%)" << " } ";
			return result.str();
		}

		//Print one individual
		string Tools::printIndividualSimple(IndividualPtr ind, Evaluate *eval, bool showConst){
			ostringstream result;
			result << "";
			double x;
			for (int i = 0; i < ind->getDimensions(); i++){
				if (eval == NULL){
					x = ind->getGene(i);
				} else {
					x = eval->getFunction()->convertToRealRange(i, ind->getGene(i));
				}
				result << x << " ";
			}
			//Constraints
			if (showConst){
				for (int i = 0; i < ind->getNConstraints(); i++){
					result << " " << ind->getConstraint(i);
				}
			}
			if (ind->isValid()){
				result << " valid " << 0.0 << " ";
			} else {
				result << " invalid " << ind->getSumConstraints() << " ";
			}
			if (ind->isEvaluatedExact()) result << " " << ind->getFitness() << " " ;
			if (ind->isEvaluatedSurrogate()){
				result << " " << ind->getFitnessSurrogate() << " ";
			} else {
			    result << " " << 0.0 << " ";
			}
			double kbest = eval->getFunction()->getBest();
			result << " " << kbest - ind->getFitness() << " " << (kbest != 0? 100*(kbest - ind->getFitness())/kbest : kbest - ind->getFitness()) << "%" << " ";
			return result.str();
		}

		//Print population
		void Tools::printPopulation(vector<IndividualPtr> pop, Evaluate *eval, bool showConst){
			for (int i = 0; i < (int)pop.size(); i++){
				cout << printIndividual(pop[i], eval, showConst) << "\n";
			}
		}


		void Tools::printHeaderInfo(vector<IndividualPtr> pop, string extra, bool showConst){
			//Genertion and number of valids
			cout << "G " << "nValids ";
			//Genes
			for (int i = 0; i <  pop[0]->getDimensions(); i++){
				cout << "x" << i << " ";
			}
			//Constraints
			if (showConst){
			   for (int i = 0; i <  pop[0]->getNConstraints(); i++){
				   cout << "cst" << i << " ";
			   }
			}

			//Valid/Invalid
			cout << "isValid ";
			//Sum of constraints
			cout << "SumOfConstraints ";
			//Fitness
			cout << "Fitness ";
			//Approximate
			cout << "ApproximateFitness ";
			//Difference to know best
			cout << "diffToKnowBest ";
			//% of difference
			cout << "diffPercent ";

			cout << extra << " " << endl;
		}

		void Tools::printGenerationInfo(int G, vector<IndividualPtr> pop, int iBest, Evaluate *eval, string extra, bool showConst){
			//Count valid individuals
			int nValids = 0;
			for(int i = 0; i < (int)pop.size(); i++){
				if (eval->isValid(pop[i]))
					nValids++;
			}
			cout << G << " " << nValids << " " << printIndividualSimple(pop[iBest], eval, showConst) << " ";
			//Extra information
			cout << extra << " " << endl;
		}

		bool Tools::isEndProcess(Evaluate *eval, double bestFit){
			int maxEval = eval->getMaxEvals();
			if (maxEval == -1){
				maxEval = Input::popSize * Input::maxGen;
				if (eval->getNEvals() >= maxEval){
					return true;
				}
			} else{
				if (eval->getNEvals() >= maxEval){
					return true;
				//} else if (bestFit <= eval->getFunction()->getBest() ){
				} else if (fgeneric_best() < fgeneric_ftarget()){
					return true;
				} else {
					return false;
				}
			}
			return false;
		}

		double Tools::getTime(){
			struct timeval tv;
			gettimeofday(&tv, NULL);
			return (double)(tv.tv_sec) + (double)(tv.tv_usec)/ 1000000.00;
		}

		void Tools::calcVariance(vector<IndividualPtr> pop, int dim, vector<double> &var){
            // variancias e medias de cada variavel
            vector<double> med(dim);

            for (int d = 0; d < dim; d++){
                double soma = 0;
                for (int n = 0 ; n < (int)pop.size() ; n++){
                    soma += pop[n]->getGene(d);
                }
                med[d] = soma / pop.size();
            }

            for (int d = 0; d < dim; d++){
                double soma_Pvar = 0;
                for (int n = 0 ; n < (int)pop.size() ; n++){
                    soma_Pvar += (pop[n]->getGene(d) - med[d]) * (pop[n]->getGene(d) - med[d]);
                }
                var[d] = soma_Pvar / pop.size();
            }
        }

	} /* namespace base */
}
