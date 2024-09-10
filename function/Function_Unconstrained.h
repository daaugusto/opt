/*
 * Function_Unconstrained.h
 *
 *  Created on: 24/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_UNCONSTRAINED_H_
#define FUNCTION_UNCONSTRAINED_H_

#include "Function.h"

#include "../base/Tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

namespace opt {
namespace function {

class Function_Unconstrained : public Function{
private:
	int idFunction;

	//Internal methods
	int getN();
	int getNConstG();
	int getNConstH();
	double getBest();
	void makeName(int f, char *name);

	double f;
protected:
	virtual void setBounds();
public:
	Function_Unconstrained(int id);
	virtual ~Function_Unconstrained();

	virtual void calc(const vector<double> values, double &fitness, vector<double> &constVal);
	//virtual double convertToRealRange(int index, double val);

	double getBoundMax(int index);
	double getBoundMin(int index);

	//Functions
	void u01(double *x, double *f, int nx);
	void u02(double *x, double *f, int nx);
	void u03(double *x, double *f, int nx);
	void u04(double *x, double *f, int nx);
	void u05(double *x, double *f, int nx);
	void u06(double *x, double *f, int nx);
	void u07(double *x, double *f, int nx);
	void u08(double *x, double *f, int nx);
	void u09(double *x, double *f, int nx);
	void u10(double *x, double *f, int nx);
	void u11(double *x, double *f, int nx);
	void u12(double *x, double *f, int nx);
	void u13(double *x, double *f, int nx);
	void u14(double *x, double *f, int nx);
	void u15(double *x, double *f, int nx);
	void u16(double *x, double *f, int nx);
};

} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_UNCONSTRAINED_H_ */
