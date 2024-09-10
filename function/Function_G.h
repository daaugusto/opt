/*
 * Function_G.h
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef FUNCTION_G_H_
#define FUNCTION_G_H_

#include "Function.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

namespace opt {
namespace function {

	class Function_G : public Function {
		private:
				int idFunction;

				//Internal methods
				int getN();
				int getNConstG();
				int getNConstH();
				double getBest();
				void makeName(int f, char *name);

				double f, *g, *h;
		public:
				Function_G(int id);
				virtual void calc(const vector<double> values, double &fitness, vector<double> &constVal);
				//virtual double convertToRealRange(int index, double val);

				double getBoundMax(int index);
				double getBoundMin(int index);

				//Functions
				void g01(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g02(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g03(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g04(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g05(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g06(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g07(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g08(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g09(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g10(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g11(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g12(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g13(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g14(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g15(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g16(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g17(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g18(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g19(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g20(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g21(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g22(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g23(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);
				void g24(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh);

			protected:
				virtual void setBounds();

	};

} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_G_H_ */
