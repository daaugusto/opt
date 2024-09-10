/*
 * Manager_Operator.h
 *
 *  Created on: 10/02/2012
 *      Author: krempser
 */

#ifndef MANAGER_OPERATOR_H_
#define MANAGER_OPERATOR_H_

#include "Operator.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;

namespace opt {
namespace operators {

	class Manager_Operator {
		private:
			//Store the operators by name
			map<string, Operator*> operators;
			map<string, double> prob;
			//Store the number of times that operator was selected
			map<string, int> times;
		public:
			Manager_Operator();
			virtual ~Manager_Operator();

			virtual void addOperator(string key, Operator *op);
			virtual Operator* getOperator(string key);
			virtual Operator* getOperator(int index);
			virtual Operator* selectOperator();

			void setProb(string key, double value);
			void setProb(map<string, double> newProb);
			double getProb(string key);

			void setTimes(string key, int value);
			void setTimes(map<string, int> newTimes);
			int getTimes(string key);
			int getTimes(int index);

			int getSize();
	};

} /* namespace operators */
} /* namespace opt */
#endif /* MANAGER_OPERATOR_H_ */
