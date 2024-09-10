/*
 * Function_Unconstrained.cpp
 *
 *  Created on: 24/05/2012
 *      Author: krempser
 */

#include "Function_Unconstrained.h"

namespace opt {
namespace function {

/** Initial value: 61 ===> U01 == 61, U02 == 62, ..., U16 == 76 **/
Function_Unconstrained::Function_Unconstrained(int id) {
	idFunction = id;

	nDimensions  = getN();
	nConstraints = getNConstH() + getNConstG();

	//Define the bounds
	setBounds();
}

Function_Unconstrained::~Function_Unconstrained() {
}

void Function_Unconstrained::calc(const vector<double> values, double &fitness, vector<double> &constVal){
	Function::calc(values, fitness, constVal);
	int n;
	n = this->getNDimensions();
	//Convert the variables in correct range
	int j;
	double *xTemp;
	char fName[4];
	makeName(idFunction, fName);
	xTemp = (double *)malloc(n*sizeof(double));
	for (j = 0; j < n; j++){
		xTemp[j] = convertToRealRange(j, values[j]);
	}

	switch(idFunction){
		case 61: u01(xTemp, &f, n);
			break;
		case 62: u02(xTemp, &f, n);
			break;
		case 63: u03(xTemp, &f, n);
			break;
		case 64: u04(xTemp, &f, n);
			break;
		case 65: u05(xTemp, &f, n);
			break;
		case 66: u06(xTemp, &f, n);
			break;
		case 67: u07(xTemp, &f, n);
			break;
		case 68: u08(xTemp, &f, n);
			break;
		case 69: u09(xTemp, &f, n);
			break;
		case 70: u10(xTemp, &f, n);
			break;
		case 71: u11(xTemp, &f, n);
			break;
		case 72: u12(xTemp, &f, n);
			break;
		case 73: u13(xTemp, &f, n);
			break;
		case 74: u14(xTemp, &f, n);
			break;
		case 75: u15(xTemp, &f, n);
			break;
		case 76: u16(xTemp, &f, n);
			break;
	}
	free(xTemp);

	//Set values
	fitness = f;
}

/*
double Function_Unconstrained::convertToRealRange(int index, double val){
	return ((val)*(boundMax[index] - boundMin[index])) + boundMin[index];
	//return val;
}
*/

double Function_Unconstrained::getBoundMax(int index){
	return boundMax[index];
}

double Function_Unconstrained::getBoundMin(int index){
	return boundMin[index];
}

//Define the bounds of the variables
void Function_Unconstrained::setBounds(){
	boundMin.clear();
	boundMax.clear();
	for(int variable = 0; variable < getNDimensions(); variable++){
//////////////
		switch(idFunction){
			case 61:{
				boundMin.push_back(-1.0);
				boundMax.push_back(1.0);
			} break;
			case 62:{
				boundMin.push_back(-10.0);
				boundMax.push_back(10.0);
			} break;
			case 63:{
				if(variable == 0){
					boundMin.push_back(-3.0);
					boundMax.push_back(3.0);
				} else {
					boundMin.push_back(-2.0);
					boundMax.push_back(2.0);
				}
			} break;
			case 64:{
				boundMin.push_back(-5.12);
				boundMax.push_back(5.12);
			} break;
			case 65:{
				boundMin.push_back(-5.12);
				boundMax.push_back(5.12);
			} break;
			case 66:{
				boundMin.push_back(-100.0);
				boundMax.push_back(100.0);
			} break;
			case 67:{
				boundMin.push_back(-600);
				boundMax.push_back(600);
			} break;
			case 68:{
				boundMin.push_back(0.0);
				boundMax.push_back(M_PI);
			}break;
			case 69:{
				boundMin.push_back(-100);
				boundMax.push_back(100);
			}break;
			case 70:{
				boundMin.push_back(-5.12);
				boundMax.push_back(5.12);
			}break;
			case 71:{
				boundMin.push_back(-2.048);
				boundMax.push_back(2.048);
			}break;
			case 72:{
				boundMin.push_back(-500.0);
				boundMax.push_back(500.0);
			}break;
			case 73:{
				boundMin.push_back(-1.0);
				boundMax.push_back(1.0);
			}break;
			case 74:{
				boundMin.push_back(-10);
				boundMax.push_back(5);
			}break;
			case 75:{
				boundMin.push_back(-100.0);
				boundMax.push_back(100.0);
			}break;
			case 76:{
				boundMin.push_back(-5.0);
				boundMax.push_back(10.0);
			}break;
		}
	/////////
	}
}

int Function_Unconstrained::getN(){
	if(idFunction == 63 || idFunction == 66){
		return 2;
	} else {
		return 30;
	}
}

int Function_Unconstrained::getNConstG(){
  return 0;
}

int Function_Unconstrained::getNConstH(){
  return 0;
}


double Function_Unconstrained::getBest(){
  return 0;
}


void Function_Unconstrained::makeName(int f, char *name){
  if (f < 10){
	sprintf(name, "U0%d", f-60);
  } else {
	sprintf(name, "U%d", f-60);
  }
}

//Ackley function
void Function_Unconstrained::u01(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 += cos(2*M_PI*x[i]);//*x[i];
	}
	//f[0] = - 20 + M_E - exp(-(0.2/dimension)*sqrt(result)) - exp(1.0/dimension*result2);
	f[0] = -20 * exp(-0.2 * sqrt( (1.0/dimension) * result ) ) - exp( (1.0/dimension) * result2 ) + 20 + M_E;
}

//Alpine
void Function_Unconstrained::u02(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += fabs(x[i]*sin(x[i]) + 0.1*x[i]);
	}

	f[0] = result;
}

//Camelback
void Function_Unconstrained::u03(double *x, double *f, int nx){
	/* objective function */
	double result  = 0.0;
	result = 4*x[0]*x[0] - 2.1*x[0]*x[0] + x[0]*x[1] - 4*x[1]*x[1] + 4*pow(x[1], 4);

	f[0] = result;
}

//DeJong
void Function_Unconstrained::u04(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
	}

	f[0] = result;
}

//DropWave
void Function_Unconstrained::u05(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
	}

	f[0] = -(1 + cos(12*sqrt(result)))/(0.5*result+2);
}

//Easom
void Function_Unconstrained::u06(double *x, double *f, int nx){
	/* objective function */
	double result  = 0.0;
	result = cos(x[0])*cos(x[1])*exp(-pow(x[0]-M_PI, 2)-pow(x[1] - M_PI, 2));

	f[0] = result;
}

//Griewangk
void Function_Unconstrained::u07(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 1.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 *= cos(x[i]/sqrt(i+1));
	}

	f[0] = result/4000 - result2 + 1;
}

//Michalewicz
void Function_Unconstrained::u08(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += sin(x[i])*sin( ((i + 1) * pow(x[i], 2)) / M_PI );
	}

	f[0] = result;
}

//Pathological
void Function_Unconstrained::u09(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	for (int i = 0; i < dimension - 1; i++) {
		result  += 0.5 + (pow(sin(sqrt(100*x[i]*x[i]+x[i+1]*x[i+1]) - 0.5), 2)) / (1 + 0.001*pow( x[i]*x[i]-2*x[i]*x[i+1]+x[i+1]*x[i+1], 2 ));
	}

	f[0] = result;
}

//Rastrigin
void Function_Unconstrained::u10(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	for (int i = 0; i < dimension; i++) {
		result += x[i]*x[i] - 10*cos(2*M_PI*x[i]);
	}

	f[0] = 10*dimension + result;
}

////////Terminar
//Rosembrock valley
void Function_Unconstrained::u11(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 += cos(2*M_PI*x[i])*x[i];
	}

	f[0] = -20 + M_E + exp(-(0.2/dimension)*sqrt(result)) - exp(1.0/dimension*result2);
}

//Schewefel
void Function_Unconstrained::u12(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 += cos(2*M_PI*x[i])*x[i];
	}

	f[0] = -20 + M_E + exp(-(0.2/dimension)*sqrt(result)) - exp(1.0/dimension*result2);
}


//Sum of powers
void Function_Unconstrained::u13(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 += cos(2*M_PI*x[i])*x[i];
	}

	f[0] = -20 + M_E + exp(-(0.2/dimension)*sqrt(result)) - exp(1.0/dimension*result2);
}

//Tirronen
void Function_Unconstrained::u14(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 += cos(2*M_PI*x[i])*x[i];
	}

	f[0] = -20 + M_E + exp(-(0.2/dimension)*sqrt(result)) - exp(1.0/dimension*result2);
}

//Whitley
void Function_Unconstrained::u15(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 += cos(2*M_PI*x[i])*x[i];
	}

	f[0] = -20 + M_E + exp(-(0.2/dimension)*sqrt(result)) - exp(1.0/dimension*result2);
}

//Zakharov
void Function_Unconstrained::u16(double *x, double *f, int nx){
	int dimension = nx;

	/* objective function */
	double result  = 0.0;
	double result2 = 0.0;
	for (int i = 0; i < dimension; i++) {
		result  += x[i]*x[i];
		result2 += cos(2*M_PI*x[i])*x[i];
	}

	f[0] = -20 + M_E + exp(-(0.2/dimension)*sqrt(result)) - exp(1.0/dimension*result2);
}

} /* namespace function */
} /* namespace opt */
