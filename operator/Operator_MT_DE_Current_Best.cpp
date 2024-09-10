/*
 * Operator_MT_DE_Current_Best.cpp
 *
 *  Created on: 21/05/2012
 *      Author: krempser
 */

#include "Operator_MT_DE_Current_Best.h"

namespace opt {
namespace operators {

Operator_MT_DE_Current_Best::Operator_MT_DE_Current_Best(){
	setKey("CURRENT-BEST");
	setNOffspring(1);
	setNParent(3);
	setType("MT");
}

int Operator_MT_DE_Current_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
	double F = 0.9;

	return apply(parent, offspring, F);
}

//Apply operator with setted parameter
int Operator_MT_DE_Current_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param){
	vector<int> v;
		v.clear(); //set the empty index
	return apply(parent, offspring, param, v);
}

//Apply operator with the index of the parents
int Operator_MT_DE_Current_Best::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index){
	int nOffspring = getNOffspring();
	int dimensions = parent[0]->getDimensions();

	double F = param;
	int r_i, iBest;
	//Select random individuals
	int ind1, ind2;
	if (index.size() < 4){
		if (index.size() < 2){
			throw new Exception("The index of current and best individual didn't send -- Operator_MT_Current_Best.cpp/apply");
		} else {
			r_i   = index[0];
			iBest = index[1];
		}

		do{
			ind1 = (int)Tools::newRand(0, parent.size());
		} while(ind1 == r_i);

		do{
			ind2 = (int)Tools::newRand(0, parent.size());
		} while(ind1 == ind2 || ind2 == r_i);
	} else {
		r_i   = index[0];
		iBest = index[1];
		ind1 = index[2];
		ind2 = index[3];
	}

	if (offspring.size() <= 0){
		offspring.push_back(IndividualPtr(new Individual()));
	}

//cout << "Ind1: " << ind1 << " Ind2: " << ind2 << " IbEST:" << iBest << " r_i: " << r_i << " F: " << F << endl;
	for (int j = 0; j < dimensions; j++){
		double value = parent[r_i]->getGene(j) + F*(parent[iBest]->getGene(j) - parent[r_i]->getGene(j)) + F*(parent[ind1]->getGene(j) - parent[ind2]->getGene(j));

//cout << " p_i: " << parent[r_i]->getGene(j) << " iBest:" << parent[iBest]->getGene(j) << " ind1: " << parent[ind1]->getGene(j) << " ind2: " << parent[ind2]->getGene(j) << "of: " << value << endl;
		//Treat values out of bounds (0, 1)
//		Tools::treatBasicBounds(value, parent[r_i]->getGene(j));
		//Store new value
		offspring[0]->setGene(j, value);
	}

	return nOffspring;
}

//Select parents with the same mechanism of the application
vector<int> Operator_MT_DE_Current_Best::selectParents(vector<IndividualPtr> pop){
//Select random individuals
	int ind1, ind2;
	do{
		ind1 = (int)Tools::newRand(0, pop.size());
	} while(ind1 == Input::currentIndividual);
	do{
		ind2 = (int)Tools::newRand(0, pop.size());
	} while(ind1 == ind2 || ind2 == Input::currentIndividual);

	vector<int>	v;
	v.push_back(ind1);
	v.push_back(ind2);

	return v;
}

} /* namespace operators */
} /* namespace opt */
