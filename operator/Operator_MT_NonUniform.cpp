/*
 * OperatorMTNonUniform.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_MT_NonUniform.h"

namespace opt {
namespace operators {

	Operator_MT_NonUniform::Operator_MT_NonUniform(){
		setKey("NONUNIFORM");
		setNOffspring(1);
		setNParent(1);
		setType("MT");
	}

	int Operator_MT_NonUniform::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		return apply(parent, offspring, 0);
	}

	//Apply operator with setted parameter
	int Operator_MT_NonUniform::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param){
		vector<int> v;
			v.clear(); //set the empty index
		return apply(parent, offspring, param, v);
	}

	//Apply operator with the index of the parents
	int Operator_MT_NonUniform::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();
		int currentGen = 1, maxGen = 2;

		//Select random individuals
		if (index.size() > 1){
			currentGen = index[0];
			maxGen     = index[1];
		}
		if (offspring.size() <= 0){
			for(int i = 0; i < (int)parent.size(); i++){
					offspring.push_back(IndividualPtr(new Individual()));
					for (int j = 0; j < dimensions; j++){
						offspring[i]->setGene(j, parent[i]->getGene(j));
					}
			}
		}
		int b = 3;
		double a1, a2;
		double upper = 1.0, lower = 0.0;
	   for (int i = 0; i < (int)parent.size(); i++){
			a1 = Tools::newRand(0.0, 1.0);
			a2 = Tools::newRand(0.0, 1.0);
			double tal = pow(a2*(1 - (currentGen/maxGen)), b);
			int j = (int)Tools::newRand(0, dimensions);
			double value;
			if (a1 < 0.5){
				value = parent[i]->getGene(j) + (upper - parent[i]->getGene(j))*tal;
			} else {
				value = parent[i]->getGene(j) + (parent[i]->getGene(j) + lower)*tal;
			}
//			Tools::treatBasicBounds(value, parent[i]->getGene(j));
			//Store new value
			offspring[i]->setGene(j, value);
		}
		return nOffspring;
	}

} /* namespace operators */
} /* namespace opt */
