/*
 * Manager_Surrogate.cpp
 *
 *  Created on: 23/07/2012
 *      Author: Eduardo Krempser
 */

#include "Manager_Surrogate.h"

namespace opt {
namespace surrogate {

	Manager_Surrogate::Manager_Surrogate(){
		surrogates.clear();
		prob.clear();
		times.clear();
	}

	void Manager_Surrogate::addSurrogate(string key, Evaluate_Surrogate *op){
		surrogates[key] = op;
		prob[key] = 1.0/surrogates.size();
		times[key] = 0;
		//recalc probabilities
		for (map<string, double>::iterator it = prob.begin(); it != prob.end(); it++){
			it->second = 1.0/surrogates.size();
		}
	}

	Evaluate_Surrogate* Manager_Surrogate::getSurrogate(string key){
		return (Evaluate_Surrogate*)surrogates.find(key)->second;
	}

	Evaluate_Surrogate* Manager_Surrogate::getSurrogate(int index){
		string lastKey = "";
		int count = 0;
		for (map<string, double>::iterator it = prob.begin(); it != prob.end(); it++){
			lastKey = it->first;
			if (count == index){
				return (Evaluate_Surrogate*)surrogates.find(it->first)->second;
			}
			count++;
		}
		return (Evaluate_Surrogate*)surrogates.find(lastKey)->second;
	}

	Evaluate_Surrogate* Manager_Surrogate::selectSurrogate(){
		double rvalue = Tools::newRand(0.0, 1.0);
		double sum = 0.0;
		string lastKey = "";

		//Select operator by probabilities
		for (map<string, double>::iterator it = prob.begin(); it != prob.end(); it++){
			sum += it->second;
			lastKey = it->first;
			if (rvalue < sum){
				times[lastKey] = times[lastKey] + 1;
				return (Evaluate_Surrogate*)surrogates.find(it->first)->second;
			}
		}
		times[lastKey] = times[lastKey] + 1;
		return surrogates[lastKey];
	}

	void Manager_Surrogate::setProb(string key, double value){
		prob[key] = value;
	}

	void Manager_Surrogate::setProb(map<string, double> newProb){
		for (map<string, double>::iterator it = newProb.begin(); it != newProb.end(); it++){
			if (prob.find(it->first) != prob.end()){
				prob[it->first] = (double)it->second;
			}
		}
	}

	double Manager_Surrogate::getProb(string key){
		return (double)prob.find(key)->second;
	}

	void Manager_Surrogate::setTimes(string key, int value){
		times[key] = value;
	}

	void Manager_Surrogate::setTimes(map<string, int> newTimes){
		for (map<string, int>::iterator it = newTimes.begin(); it != newTimes.end(); it++){
			if (times.find(it->first) != times.end()){
				times[it->first] = (int)it->second;
			}
		}
	}

	int Manager_Surrogate::getTimes(string key){
		return (int)times.find(key)->second;
	}

	int Manager_Surrogate::getTimes(int index){
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

	int Manager_Surrogate::getSize(){
		return surrogates.size();
	}

	Manager_Surrogate::~Manager_Surrogate() {
	}

} /* namespace surrogate */
} /* namespace opt */
