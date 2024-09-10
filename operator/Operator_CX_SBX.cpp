/*
 * Operator_CX_SBX.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_CX_SBX.h"

namespace opt {
namespace operators {

	Operator_CX_SBX::Operator_CX_SBX(){
		setKey("SBX");
		setNOffspring(2);
		setNParent(2);
		setType("CX");
		//Specific parameter
		n = 2.0;
	}

	void Operator_CX_SBX::setParameterN(double val){
		n = val;
	}

	/**
		SBX (Deb) - Simulated Binary Crossover
		Creates children solutions in proportion to the difference in parent solutions
	*/
	int Operator_CX_SBX::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();

		//Create offspring
		for (int i = 0; i < nOffspring; i++){
			offspring.push_back(IndividualPtr(new Individual()));
		}

		double u = Tools::newRand(0.0, 1.0);
		//probability distribution
		double betaq;
		if (u <= 0.5){
			betaq = pow(2*u, 1/(n+1));
		} else {
			betaq = pow((1/(2*(1-u))), 1/(n+1));
		}

		//Generate children
		double x1, x2;
		for (int i = 0; i < dimensions; i++){
			x1 = 0.5*(((1 + betaq)*parent[0]->getGene(i)) + ((1-betaq)*parent[1]->getGene(i)));
			x2 = 0.5*(((1 - betaq)*parent[0]->getGene(i)) + ((1+betaq)*parent[1]->getGene(i)));
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
