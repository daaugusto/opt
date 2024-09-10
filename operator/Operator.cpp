/*
 * Operator.cpp
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#include "Operator.h"

namespace opt {
namespace operators {

	Operator::Operator(){
		key = "OP";
		nParent = 0;
		nOffspring = 0;
		type = "OP";
	}

	int Operator::getNParent(){
		return nParent;
	}

	int Operator::getNOffspring(){
		return nOffspring;
	}

	string Operator::getKey(){
		return key;
	}

	string Operator::getType(){
		return type;
	}

	void Operator::setType(string t){
		type = t;
	}

	void Operator::setKey(string k){
		key = k;
	}

	void Operator::setNParent(int n){
		nParent = n;
	}

	void Operator::setNOffspring(int n){
		nOffspring = n;
	}

	//Return the size of offspring
	int Operator::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring){
		return 0;
	}

	int Operator::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param){
		return apply(parent, offspring);
	}

	//Apply operator with the index of the parents
	int Operator::apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index){
		return apply(parent, offspring);
	}

	//Select parents with the same mechanism of the application (basically return the empty set)
	vector<int> Operator::selectParents(vector<IndividualPtr> pop){
		vector<int> v;
		v.clear();
		return v;
	}

	Operator::~Operator() {
	}

} /* namespace operators */
} /* namespace opt */
