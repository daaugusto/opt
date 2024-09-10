/*
 * Function_Truss.h
 *
 *  Created on: 18/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_H_
#define FUNCTION_TRUSS_H_

#include "Function.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <vector>
using namespace std;

#include "truss/Truss_Bar_Structure_Static_Problem.h"
#include "truss/Function_Truss_10_Bar.h"
#include "truss/Function_Truss_10_Bar_Discrete.h"
#include "truss/Function_Truss_25_Bar.h"
#include "truss/Function_Truss_25_Bar_Discrete.h"
#include "truss/Function_Truss_60_Bar.h"
#include "truss/Function_Truss_60_Bar_Discrete.h"
#include "truss/Function_Truss_72_Bar.h"
#include "truss/Function_Truss_72_Bar_Discrete.h"
#include "truss/F111Truss200Bar.h"
#include "truss/F112Truss200BarDiscrete.h"
#include "truss/Function_Truss_942_Bar.h"
#include "truss/Function_Truss_942_Bar_Discrete.h"
//#include "truss/F113Truss960Bar.h"
//#include "truss/F114Truss960BarDiscrete.h"

using namespace opt::function::truss;

namespace opt {
namespace function {

class Function_Truss : public Function{
protected:
	Truss_Bar_Structure_Static_Problem *problem;
	int idFunction;
	// Which are the discrete variables
	vector<double> discreteVariables;
	vector<double> discretization;

	virtual void setBounds();

public:
	Function_Truss(int id);
	virtual ~Function_Truss();
	virtual void calc(const vector<double> values, double &fitness, vector<double> &constVal);
	virtual double getBest();
	virtual double convertToRealRange(int index, double val);

	void makeName(int f, char *name);

	double getBoundMax(int index);
	double getBoundMin(int index);
};

} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_H_ */
