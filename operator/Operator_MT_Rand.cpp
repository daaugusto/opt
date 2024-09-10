/*
 * OperatorMTRand.cpp
 *
 *  Created on: 09/02/2012
 *      Author: Eduardo Krempser
 */

#include "Operator_MT_Rand.h"

namespace opt {
namespace operators {

	Operator_MT_Rand::Operator_MT_Rand(){
		setKey("RAND");
		setNOffspring(1);
		setNParent(1);
		setType("MT");
	}

	int Operator_MT_Rand::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		int dimensions = parent[0]->getDimensions();

		double probApp = 1.0/dimensions;
		int t = (int)Tools::newRand(0, dimensions);
		for (int i = 0; i < (int)parent.size(); i++){
			if ((int)offspring.size() <= i)
				offspring.push_back(IndividualPtr(new Individual()));
			for (int j = 0; j < dimensions; j++){
				double actual = parent[i]->getGene(j);
				if (Tools::newRand(0.0, 1.0) <= probApp || j == t){
					double v = Tools::newRand(0.0, 1.0);
					offspring[i]->setGene(j, v);
				} else {
					offspring[i]->setGene(j, actual);
				}
			}
		}

		/*for (int i = 0; i < (int)parent.size(); i++){
			if ((int)offspring.size() <= i)
							offspring.push_back(IndividualPtr(new Individual()));
			int ind = (int)Tools::newRand(0, dimensions);
			for (int j = 0; j < dimensions; j++){
				if (j == ind){
					double v = Tools::newRand(0.0, 1.0);
					offspring[i]->setGene(j, v);
				} else {
					offspring[i]->setGene(j, parent[i]->getGene(j));
				}
			}
		}*/

		return (int)offspring.size();
	}

} /* namespace operators */
} /* namespace opt */
