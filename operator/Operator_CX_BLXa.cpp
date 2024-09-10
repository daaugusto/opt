/*
 * Operator_CX_BLXa.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_CX_BLXa.h"

namespace opt {
namespace operators {

	Operator_CX_BLXa::Operator_CX_BLXa(){
		setKey("BLXa");
		setNOffspring(2);
		setNParent(2);
		setType("CX");
		//Specific parameter
		alpha = 0.5;
	}

	void Operator_CX_BLXa::setParameterAlpha(double val){
		alpha = val;
	}

	/**
		BLXa (Eshelman and Schaffer (1993)) - Blend Crossover
		Have introduced the notion of interval schemata for real-coded genetic algorithms
	*/
	int Operator_CX_BLXa::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();

		//Create offspring
		for (int i = 0; i < nOffspring; i++){
			offspring.push_back(IndividualPtr(new Individual()));
		}

		//Generate children
		double x1, x2, min, max;
		double d;
		for (int i = 0; i < dimensions; i++){
			x1 = parent[0]->getGene(i);
			x2 = parent[1]->getGene(i);

			if (x2 < x1){
				min = x2;
				max = x1;
			} else {
				min = x1;
				max = x2;
			}
			d = max - min;

			x1 = Tools::newRand(min - alpha*d, max + alpha*d);
			x2 = Tools::newRand(min - alpha*d, max + alpha*d);

			//Treat values out of bounds (0, 1)
			Tools::treatBasicBounds(x1, parent[0]->getGene(i));
			Tools::treatBasicBounds(x2, parent[0]->getGene(i));

			offspring[0]->setGene(i, x1);
			offspring[1]->setGene(i, x2);
		}
		return nOffspring;
	}

} /* namespace operators */
} /* namespace opt */
