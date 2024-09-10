/*
 * Function.h
 *
 *  Created on: 07/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <vector>
using namespace std;

namespace opt {
namespace function {

	class Function {
		protected:
			int nDimensions;
			int nConstraints;
			double knowBest;
			vector<double> boundMin;
			vector<double> boundMax;
			virtual void setBounds();

			//Number of calcs
			double nCalls;
			//Max number of evaluations (if there is)
			double maxCalls;
		public:
			Function();
			virtual ~Function();
			virtual void calc(const vector<double> values, double &fitness, vector<double> &constVal);
			virtual int getNDimensions();
			virtual void setNDimensions(int dim);
			virtual int getNConstraints();
			virtual double getBest();
			virtual double convertToRealRange(int index, double val);
			void convertToRealRange(vector<double> &values);
			//Initialize and finalize the function (BBOB)
			virtual void initialize();
			virtual void finalize();

			virtual void setNCalls(double n);
			virtual double getNCalls();
			virtual void setMaxCalls(double n);
			virtual double getMaxCalls();

			virtual double getBoundMax(int index);
			virtual double getBoundMin(int index);
	};
} /* namespace base */
}
#endif /* FUNCTION_H_ */
