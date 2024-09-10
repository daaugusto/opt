/*
 * OperatorMTDECurrentRand.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_MT_DE_Current_Rand.h"

namespace opt {
namespace operators {

	Operator_MT_DE_Current_Rand::Operator_MT_DE_Current_Rand(){
		setKey("CURRENT-RAND");
		setNOffspring(1);
		setNParent(3);
		setType("MT");
	}

	int Operator_MT_DE_Current_Rand::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		double F = 0.9;

		return apply(parent, offspring, F);
	}

	//Apply operator with setted parameter
	int Operator_MT_DE_Current_Rand::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param){
		vector<int> v;
			v.clear(); //set the empty index
		return apply(parent, offspring, param, v);
	}

	//Apply operator with the index of the parents
	int Operator_MT_DE_Current_Rand::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();

		double F = param;
		int r_i;
		//Select random individuals
		int ind1, ind2, ind3;
		if (index.size() < 3){
			if (index.size() < 1){
				throw new Exception("The index of current individual didn't send -- Operator_MT_Current_Rand.cpp/apply");
			} else {
				r_i = index[0];
			}

			do{
				ind1 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == r_i);
			do{
				ind2 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == ind2 || ind2 == r_i);
			do{
				ind3 = (int)Tools::newRand(0, parent.size());
			} while(ind3 == ind2 || ind3 == ind1 || ind3 == r_i);
		} else {
			r_i  = index[0];
			ind1 = index[1];
			ind2 = index[2];
			ind3 = index[3];
		}

		if (offspring.size() <= 0){
			offspring.push_back(IndividualPtr(new Individual()));
		}

		for (int j = 0; j < dimensions; j++){
			double value = parent[r_i]->getGene(j) + F*(parent[ind1]->getGene(j) - parent[r_i]->getGene(j)) + F*(parent[ind2]->getGene(j) - parent[ind3]->getGene(j));
			//Treat values out of bounds (0, 1)
//			Tools::treatBasicBounds(value, parent[r_i]->getGene(j));
			//Store new value
			offspring[0]->setGene(j, value);
		}

		return nOffspring;
	}

	//Select parents with the same mechanism of the application
	vector<int> Operator_MT_DE_Current_Rand::selectParents(vector<IndividualPtr> pop){
	//Select random individuals
		int ind1, ind2, ind3;
		do{
			ind1 = (int)Tools::newRand(0, pop.size());
		}while(ind1 == Input::currentIndividual);
		do{
			ind2 = (int)Tools::newRand(0, pop.size());
		} while(ind1 == ind2 || ind2 == Input::currentIndividual);
		do{
			ind3 = (int)Tools::newRand(0, pop.size());
		} while(ind3 == ind2 || ind3 == ind1 || ind3 == Input::currentIndividual);

		vector<int>	v;
		v.push_back(ind1);
		v.push_back(ind2);
		v.push_back(ind3);

		return v;
	}

} /* namespace operators */
} /* namespace opt */
