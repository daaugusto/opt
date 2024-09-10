/*
 * Manager_Surrogate.h
 *
 *  Created on: 23/07/2012
 *      Author: Eduardo Krempser
 */

#ifndef MANAGER_SURROGATE_H_
#define MANAGER_SURROGATE_H_

#include "Evaluate_Surrogate.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "../base/Tools.h"
using namespace std;
using namespace opt::base;

namespace opt {
namespace surrogate {

class Manager_Surrogate {
	private:
		//Store the operators by name
		map<string, Evaluate_Surrogate*> surrogates;
		map<string, double> prob;
		//Store the number of times that operator was selected
		map<string, int> times;
	public:
		Manager_Surrogate();

		virtual void addSurrogate(string key, Evaluate_Surrogate *op);
		virtual Evaluate_Surrogate* getSurrogate(string key);
		virtual Evaluate_Surrogate* getSurrogate(int index);
		virtual Evaluate_Surrogate* selectSurrogate();

		void setProb(string key, double value);
		void setProb(map<string, double> newProb);
		double getProb(string key);

		void setTimes(string key, int value);
		void setTimes(map<string, int> newTimes);
		int getTimes(string key);
		int getTimes(int index);

		int getSize();

		virtual ~Manager_Surrogate();
};

} /* namespace surrogate */
} /* namespace opt */
#endif /* MANAGER_SURROGATE_H_ */
