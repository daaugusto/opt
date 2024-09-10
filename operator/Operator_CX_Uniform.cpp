/*
 * Operator_CX_Uniform.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_CX_Uniform.h"

namespace opt {
namespace operators {

	Operator_CX_Uniform::Operator_CX_Uniform(){
		setKey("UNIFORM");
		setNOffspring(2);
		setNParent(2);
		setType("CX");
	}

	int Operator_CX_Uniform::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();
		for (int i = 0; i < nOffspring; i++){
			offspring.push_back(IndividualPtr(new Individual()));
		}
		for (int i = 0; i < dimensions; i++){
			double point = Tools::newRand(0, 1);
			if (point <= 0.5){
				offspring[0]->setGene(i, parent[0]->getGene(i));
				offspring[1]->setGene(i, parent[1]->getGene(i));
			} else {
				offspring[1]->setGene(i, parent[0]->getGene(i));
				offspring[0]->setGene(i, parent[1]->getGene(i));
			}
		}
		return nOffspring;
	}

} /* namespace operators */
} /* namespace opt */
