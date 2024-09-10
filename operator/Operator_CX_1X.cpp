/*
 * Operator_CX_1X.cpp
 *
 *  Created on: 08/02/2012
 *      Author: krempser
 */

#include "Operator_CX_1X.h"

namespace opt {
namespace operators {

	Operator_CX_1X::Operator_CX_1X(){
		setKey("1X");
		setNOffspring(2);
		setNParent(2);
		setType("CX");
	}

	int Operator_CX_1X::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();
		int point = (int)Tools::newRand(0, dimensions);
		for (int i = 0; i < nOffspring; i++){
			offspring.push_back(IndividualPtr(new Individual()));
		}
		for (int i = 0; i < dimensions; i++){
			if (i <= point){
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
