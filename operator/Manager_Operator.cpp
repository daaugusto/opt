/*
 * ManagerOperator.cpp
 *
 *  Created on: 10/02/2012
 *      Author: krempser
 */

#include "Manager_Operator.h"

namespace opt {
namespace operators {

	Manager_Operator::Manager_Operator(){
		//ctr
	}

	void Manager_Operator::addOperator(string key, Operator *op){
		operators[key] = op;
		prob[key] = 1.0/operators.size();
		times[key] = 0;
		//recalc probabilities
		for (map<string, double>::iterator it = prob.begin(); it != prob.end(); it++){
			it->second = 1.0/operators.size();
		}
	}

	Operator* Manager_Operator::getOperator(string key) {
		return (Operator*)operators.find(key)->second;
	}

	Operator* Manager_Operator::getOperator(int index) {
		string lastKey = "";
		int count = 0;
		for (map<string, double>::iterator it = prob.begin(); it != prob.end(); it++){
			lastKey = it->first;
			if (count == index){
				return (Operator*)operators.find(it->first)->second;
			}
			count++;
		}
		return (Operator*)operators.find(lastKey)->second;
	}

	Operator* Manager_Operator::selectOperator(){
		double rvalue = Tools::newRand(0.0, 1.0);
		double sum = 0.0;
		string lastKey = "";

		//Select operator by probabilities
		for (map<string, double>::iterator it = prob.begin(); it != prob.end(); it++){
			sum += it->second;
			lastKey = it->first;
			if (rvalue < sum){
				times[lastKey] = times[lastKey] + 1;
				return (Operator*)operators.find(it->first)->second;
			}
		}
		times[lastKey] = times[lastKey] + 1;
		return operators[lastKey];
	}

	void Manager_Operator::setProb(string key, double value){
		prob[key] = value;
	}

	void Manager_Operator::setProb(map<string, double> newProb){
		for (map<string, double>::iterator it = newProb.begin(); it != newProb.end(); it++){
			if (prob.find(it->first) != prob.end()){
				prob[it->first] = (double)it->second;
			}
		}
	}

	double Manager_Operator::getProb(string key){
		return (double)prob.find(key)->second;
	}

	void Manager_Operator::setTimes(string key, int value){
		times[key] = value;
	}

	void Manager_Operator::setTimes(map<string, int> newTimes){
		for (map<string, int>::iterator it = newTimes.begin(); it != newTimes.end(); it++){
			if (times.find(it->first) != times.end()){
				times[it->first] = (int)it->second;
			}
		}
	}

	int Manager_Operator::getTimes(string key){
		return (int)times.find(key)->second;
	}

	int Manager_Operator::getTimes(int index){
		string lastKey = "";
		int count = 0;
		for (map<string, int>::iterator it = times.begin(); it != times.end(); it++){
			lastKey = it->first;
			if (count == index){
				return (int)times.find(it->first)->second;
			}
			count++;
		}
		return (int)times.find(lastKey)->second;
	}

	int Manager_Operator::getSize(){
		return operators.size();
	}

	Manager_Operator::~Manager_Operator() {
		for (map<string, Operator*>::iterator it = operators.begin(); it != operators.end(); it++){
			delete it->second;
		}
		this->operators.clear( );
		this->prob.clear( );
		this->times.clear( );
	}

} /* namespace operators */
} /* namespace opt */
