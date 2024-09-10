/*
 * OperatorMTDEBest.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_MT_DE_Best.h"

namespace opt {
namespace operators {

	Operator_MT_DE_Best::Operator_MT_DE_Best(){
		setKey("BEST");
		setNOffspring(1);
		setNParent(3);
		setType("MT");
	}

	int Operator_MT_DE_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		double F = 0.9;

		return apply(parent, offspring, F);
	}

	int Operator_MT_DE_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param){
		vector<int> v;
			v.clear(); //set the empty index
		return apply(parent, offspring, param, v);
	}

	int Operator_MT_DE_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();

		double F = param;

		if (offspring.size() <= 0){
			offspring.push_back(IndividualPtr(new Individual()));
		}

		//Select random individuals
		int ind1, ind2, iBest;
		if (index.size() < 3){
			do{
				ind1 = (int)Tools::newRand(0, parent.size());
			}while(ind1 == Input::currentIndividual);
			do{
				ind2 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == ind2 || ind2 == Input::currentIndividual);

			//In this case the first value in the index vector is the best individual in the population
			if (index.size() < 1){
				throw new Exception("The index of best individual didn't send -- Operator_MT_DE_Best.cpp/apply");
			} else {
				iBest = index[0];
			}
		} else {
			ind1 = index[1];
			ind2 = index[2];
			iBest = index[0];
		}

		for (int j = 0; j < dimensions; j++){
			double value = parent[iBest]->getGene(j) + F*(parent[ind2]->getGene(j) - parent[ind1]->getGene(j));
			//Treat values out of bounds (0, 1)
//			Tools::treatBasicBounds(value, parent[iBest]->getGene(j));
			//Store new value
			offspring[0]->setGene(j, value);
		}

		return nOffspring;
	}

	//Select parents with the same mechanism of the application (but without the best value)
	vector<int> Operator_MT_DE_Best::selectParents(vector<IndividualPtr> pop){
		int ind1, ind2;
		do{
			ind1 = (int)Tools::newRand(0, pop.size());
		}while(ind1 == Input::currentIndividual);
		do{
			ind2 = (int)Tools::newRand(0, pop.size());
		} while(ind1 == ind2 || ind2 == Input::currentIndividual);

		vector<int> v;
		v.push_back(ind1);
		v.push_back(ind2);
		return v;
	}

} /* namespace operators */
} /* namespace opt */
