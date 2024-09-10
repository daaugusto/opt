/*
 * OperatorMTDelta.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_MT_Delta.h"

namespace opt {
namespace operators {

	Operator_MT_Delta::Operator_MT_Delta(){
		setKey("DELTA");
		setNOffspring(1);
		setNParent(1);
		setType("MT");
	}

	int Operator_MT_Delta::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();

		double probApp = 1.0/dimensions;
		for (int i = 0; i < (int)parent.size(); i++){
			if ((int)offspring.size() <= i){
				offspring.push_back(IndividualPtr(new Individual()));
			}
			for (int j = 0; j < dimensions; j++){
				double actual = parent[i]->getGene(j);
				if (Tools::newRand(0.0, 1.0) < probApp){
					double v = Tools::newRand(0.0, 0.25), sig = Tools::newRand(0.0, 1.0);
					if (sig < 0.5) v = -v;
					double x = actual + v;
					//Treat values out of bounds (0, 1)
//					Tools::treatBasicBounds(x, parent[i]->getGene(j));
					//Store new value
					offspring[i]->setGene(j, x);
				} else {
					offspring[i]->setGene(j, actual);
				}
			}
		}
		return nOffspring;
	}

} /* namespace operators */
} /* namespace opt */
