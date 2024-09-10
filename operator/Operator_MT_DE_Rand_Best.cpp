/*
 * OperatorMTDERandBest.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_MT_DE_Rand_Best.h"

namespace opt {
namespace operators {

	Operator_MT_DE_Rand_Best::Operator_MT_DE_Rand_Best(){
		setKey("RAND-BEST");
		setNOffspring(1);
		setNParent(6);
		setType("MT");
	}

	int Operator_MT_DE_Rand_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		double F = 0.9;

		return apply(parent, offspring, F);
	}

	int Operator_MT_DE_Rand_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param){
		vector<int> v;
			v.clear(); //set the empty index
		return apply(parent, offspring, param, v);
	}

	int Operator_MT_DE_Rand_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();

		if (offspring.size() <= 0){
			offspring.push_back(IndividualPtr(new Individual()));
		}

		double F = param;
		//Select random individuals
		int ind1, ind2, ind3, ind4, ind5, iBest;
		if (index.size() < 5){
			do{
				ind1 = (int)Tools::newRand(0, parent.size());
			}while(ind1 == Input::currentIndividual);
			do{
				ind2 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == ind2 || ind2 == Input::currentIndividual);
			do{
				ind3 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == ind3 || ind2 == ind3 || ind3 == Input::currentIndividual);
			do{
				ind4 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == ind4 || ind2 == ind4 || ind3 == ind4 || ind4 == Input::currentIndividual);
			do{
				ind5 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == ind5 || ind2 == ind5 || ind3 == ind5 || ind4 == ind5 || ind5 == Input::currentIndividual);

			//In this case the first value in the index vector is the best individual in the population
			if (index.size() < 1){
				throw new Exception("The index of best individual didn't send -- Operator_MT_DE_Rand_Best.cpp/apply");
			} else {
				iBest = index[0];
			}
		} else {
			ind1 = index[1];
			ind2 = index[2];
			ind3 = index[3];
			ind4 = index[4];
			ind5 = index[5];
			iBest = index[0];
		}

		for (int j = 0; j < dimensions; j++){
			double value = parent[ind1]->getGene(j) + F*(parent[iBest]->getGene(j) - parent[ind1]->getGene(j)) + F*(parent[ind2]->getGene(j) - parent[ind3]->getGene(j)) + F*(parent[ind4]->getGene(j) - parent[ind5]->getGene(j));
			//Treat values out of bounds (0, 1)
//			Tools::treatBasicBounds(value, parent[ind1]->getGene(j));
			//Store new value
			offspring[0]->setGene(j, value);
		}

		return nOffspring;
	}

	//Select parents with the same mechanism of the application
	vector<int> Operator_MT_DE_Rand_Best::selectParents(vector<IndividualPtr> pop){
		int ind1, ind2, ind3, ind4, ind5;
		do{
			ind1 = (int)Tools::newRand(0, pop.size());
		}while(ind1 == Input::currentIndividual);
		do{
		ind2 = (int)Tools::newRand(0, pop.size());
		} while(ind1 == ind2 || ind2 == Input::currentIndividual);
		do{
		ind3 = (int)Tools::newRand(0, pop.size());
		} while(ind1 == ind3 || ind2 == ind3 || ind3 == Input::currentIndividual);
		do{
		ind4 = (int)Tools::newRand(0, pop.size());
		} while(ind1 == ind4 || ind2 == ind4 || ind3 == ind4 || ind4 == Input::currentIndividual);
		do{
		ind5 = (int)Tools::newRand(0, pop.size());
		} while(ind1 == ind5 || ind2 == ind5 || ind3 == ind5 || ind4 == ind5 || ind5 == Input::currentIndividual);

		vector<int> v;
		v.push_back(ind1);
		v.push_back(ind2);
		v.push_back(ind3);
		v.push_back(ind4);
		v.push_back(ind5);
		return v;
	}

} /* namespace operators */
} /* namespace opt */
