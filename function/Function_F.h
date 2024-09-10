/*
 * FunctionF.h
 *
 *  Created on: 07/02/2012
 *      Author: krempser
 */

#ifndef FUNCTIONF_H_
#define FUNCTIONF_H_

#include "Function.h"

#include "../base/Tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "function_f/functions_code.h"

//#define PI 3.141592653589793
//#define E  2.718281828459045

using namespace std;
using namespace opt::base;

namespace opt{
namespace function {

	class Function_F : public Function{
	private:
			int idFunction;

			//Internal methods
			int getN();
			int getNConstG();
			int getNConstH();
			double getBest();
			void makeName(int f, char *name);

			double f;
		public:
			Function_F(int id);
			virtual void calc(const vector<double> values, double &fitness, vector<double> &constVal);
			//virtual double convertToRealRange(int index, double val);

			double getBoundMax(int index);
			double getBoundMin(int index);

			//Functions
			void f01(double *x, double *f,int nx);
			void f02(double *x, double *f,int nx);
			void f03(double *x, double *f,int nx);
			void f04(double *x, double *f,int nx);
			void f05(double *x, double *f,int nx);
			void f06(double *x, double *f,int nx);
			void f07(double *x, double *f,int nx);
			void f08(double *x, double *f,int nx);
			void f09(double *x, double *f,int nx);
			void f10(double *x, double *f,int nx);
			void f11(double *x, double *f,int nx);
			void f12(double *x, double *f,int nx);
			void f13(double *x, double *f,int nx);
			void f14(double *x, double *f,int nx);
			void f15(double *x, double *f,int nx);
			void f16(double *x, double *f,int nx);
			void f17(double *x, double *f,int nx);
			void f18(double *x, double *f,int nx);
			void f19(double *x, double *f,int nx);
			void f20(double *x, double *f,int nx);
			void f21(double *x, double *f,int nx);
			void f22(double *x, double *f,int nx);
			void f23(double *x, double *f,int nx);
			void f24(double *x, double *f,int nx);
			void f25(double *x, double *f,int nx);
			void f26(double *x, double *f,int nx);
			void f27(double *x, double *f,int nx);
			void f28(double *x, double *f,int nx);
			void f29(double *x, double *f,int nx);

			double u(double x, double a, double k, double m);
			double product(double *v1, double *v2, int n);

			virtual ~Function_F();
		protected:
			virtual void setBounds();


	};

} /* namespace function */
}
#endif /* FUNCTIONF_H_ */
