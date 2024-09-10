/*
 * Function_Mechanic.h
 *
 *  Created on: 02/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_MECHANIC_H_
#define FUNCTION_MECHANIC_H_

#include "Function.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

namespace opt {
namespace function {

	class Function_Mechanic : public Function {
		private:
				int idFunction;

				//Internal methods
				int getN();
				int getNConstG();
				int getNConstH();
				double getBest();
				void makeName(int f, char *name);

				double f, *g, *h;
				// Which are the discrete variables
				vector<double> discreteVariables;
				vector<double> discretization;
		public:
				Function_Mechanic(int id);
				virtual void calc(const vector<double> values, double &fitness, vector<double> &constVal);
				virtual double convertToRealRange(int index, double val);

				double getBoundMax(int index);
				double getBoundMin(int index);

				//Functions
				void weldedBeam(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void pressureVessel(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);

			protected:
				virtual void setBounds();

	};

} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_MECHANIC_H_ */
