/*
 * OperatorMTDERand.cpp
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#include "Operator_MT_DE_Rand.h"

namespace opt {
namespace operators {

	Operator_MT_DE_Rand::Operator_MT_DE_Rand(){
		setKey("RAND");
		setNOffspring(1);
		setNParent(3);
		setType("MT");
	}

	int Operator_MT_DE_Rand::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		double F = 0.9;

		return apply(parent, offspring, F);
	}

	//Apply operator with setted parameter
	int Operator_MT_DE_Rand::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param){
		vector<int> v;
			v.clear(); //set the empty index
		return apply(parent, offspring, param, v);
	}

	//Apply operator with the index of the parents
	int Operator_MT_DE_Rand::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index){
/*
		cout << "DE-RAND:"<<endl;
		for(int i = 0; i < index.size(); i++){
			cout << "\tindex[" << i << "]: " << index[i] << endl;
		}
*/
		int nOffspring = getNOffspring();
		int dimensions = parent[0]->getDimensions();
		double F = param;

		//Select random individuals
		int ind1, ind2, ind3;
		if (index.size() < 3){
			do{
				ind1 = (int)Tools::newRand(0, parent.size());
			}while(ind1 == Input::currentIndividual);
			do{
				ind2 = (int)Tools::newRand(0, parent.size());
			} while(ind1 == ind2 || ind2 == Input::currentIndividual);
			do{
				ind3 = (int)Tools::newRand(0, parent.size());
			} while(ind3 == ind2 || ind3 == ind1 || ind3 == Input::currentIndividual);
		} else {
			ind1 = index[0];
			ind2 = index[1];
			ind3 = index[2];
		}

		if (offspring.size() <= 0){
			offspring.push_back(IndividualPtr(new Individual()));
		}
////
/*
		cout << "\nTamanho Prole: " << offspring.size() << endl;
		cout << "Dimensão: " << dimensions << endl;
		cout << "Parents: --------" << endl;
		cout << "Ind1: " << ind1 << endl;
		for(int j = 0; j < dimensions; j++){
			cout << " " << parent[ind1]->getGene(j);
		}
		cout << "\nInd2: " << ind2 << endl;
		for(int j = 0; j < dimensions; j++){
			cout << " " << parent[ind2]->getGene(j);
		}
		cout << "\nInd3: " << ind3 << endl;
		for(int j = 0; j < dimensions; j++){
			cout << " " << parent[ind3]->getGene(j);
		}
		cout << "F: " << F << endl;
*/
////

		for (int j = 0; j < dimensions; j++){
			double value = parent[ind3]->getGene(j) + F*(parent[ind2]->getGene(j) - parent[ind1]->getGene(j));
			//Treat values out of bounds (0, 1)
//			Tools::treatBasicBounds(value, parent[ind3]->getGene(j));
			//Store new value
			offspring[0]->setGene(j, value);
//cout << " j: " << j << " p1: " << parent[ind3]->getGene(j) << " p2: " << parent[ind2]->getGene(j) << " p3: " << parent[ind1]->getGene(j) << " f: " << F << " value: " << value << endl;
		}
/*cout << "\noff: " << endl;
for(int j = 0; j < dimensions; j++){
	cout << " " << offspring[0]->getGene(j);
}
cout << "\n---------" << endl;*/

		return nOffspring;
	}

	//Select parents with the same mechanism of the application
	vector<int> Operator_MT_DE_Rand::selectParents(vector<IndividualPtr> pop){
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
