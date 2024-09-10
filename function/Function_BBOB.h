/*
 * Function_BBOB.h
 *
 *  Created on: 16/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef FUNCTION_BBOB_H_
#define FUNCTION_BBOB_H_

#include "bbob/bbobStructures.h"
#include "Function.h"

#include "../base/Input.h"
using namespace opt::base;

namespace opt {
namespace function {

	class Function_BBOB : public Function{
		private:
			int idFunction;

			//Internal methods
			int getN();
			int getNConstG();
			int getNConstH();
			double getBest();
			void makeName(int f, char *name);
		public:
			double maxEvals;

			Function_BBOB(int id);
			virtual void calc(const vector<double> values, double &fitness, vector<double> &constVal);
			//virtual double convertToRealRange(int index, double val);
			double getBoundMax(int index);
			double getBoundMin(int index);

			virtual void initialize();
			virtual void finalize();
		protected:
			virtual void setBounds();
	};

} /* namespace hybridAos */
} /* namespace opt */
#endif /* FUNCTION_BBOB_H_ */
