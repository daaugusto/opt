/*
 * FunctionF.cpp
 *
 *  Created on: 07/02/2012
 *      Author: Eduardo Krempser
 */

#include "Function_F.h"
using namespace opt::function::function_f_code;

namespace opt{
namespace function {

	/** Initial value: 31 ===> F01 == 31, F02 == 32, ..., F25 == 55 **/

	Function_F::Function_F(int id){
		idFunction = id;

		nDimensions  = getN();
		nConstraints = getNConstH() + getNConstG();

		//Define the bounds
		setBounds();
	}

	void Function_F::calc(const vector<double> values, double &fitness, vector<double> &constVal){
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
			case 31: f01(xTemp, &f, n);
				break;
			case 32: f02(xTemp, &f, n);
				break;
			case 33: f03(xTemp, &f, n);
				break;
			case 34: f04(xTemp, &f, n);
				break;
			case 35: f05(xTemp, &f, n);
				break;
			case 36: f06(xTemp, &f, n);
				break;
			case 37: f07(xTemp, &f, n);
				break;
			case 38: f08(xTemp, &f, n);
				break;
			case 39: f09(xTemp, &f, n);
				break;
			case 40: f10(xTemp, &f, n);
				break;
			case 41: f11(xTemp, &f, n);
				break;
			case 42: f12(xTemp, &f, n);
				break;
			case 43: f13(xTemp, &f, n);
				break;
			case 44: f14(xTemp, &f, n);
				break;
			case 45: f15(xTemp, &f, n);
				break;
			case 46: f16(xTemp, &f, n);
				break;
			case 47: f17(xTemp, &f, n);
				break;
			case 48: f18(xTemp, &f, n);
				break;
			case 49: f19(xTemp, &f, n);
				break;
			case 50: f20(xTemp, &f, n);
				break;
			case 51: f21(xTemp, &f, n);
				break;
			case 52: f22(xTemp, &f, n);
				break;
			case 53: f23(xTemp, &f, n);
				break;
			case 54: f24(xTemp, &f, n);
				break;
			case 55: f25(xTemp, &f, n);
				break;
			case 56: f26(xTemp, &f, n);
				break;
			case 57: f27(xTemp, &f, n);
				break;
			case 58: f28(xTemp, &f, n);
				break;
			case 59: f29(xTemp, &f, n);
				break;
		}
		free(xTemp);

		//Set values
		fitness = f;
	}

	/*
	double Function_F::convertToRealRange(int index, double val){
		return ((val)*(boundMax[index] - boundMin[index])) + boundMin[index];
	}
	*/

	double Function_F::getBoundMax(int index){
			return boundMax[index];
		}

	double Function_F::getBoundMin(int index){
		return boundMin[index];
	}


	//Define the bounds of the variables
	void Function_F::setBounds(){
		boundMin.clear();
		boundMax.clear();
		for(int variable = 0; variable < getNDimensions(); variable++){
	//////////////
			switch(idFunction){
				case 31:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				} break;
				case 32:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				} break;
				case 33:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				} break;
				case 34:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				} break;
				case 35:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				} break;
				case 36:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				} break;
				case 37:{
					boundMin.push_back(0.0);
					boundMax.push_back(600.0);
				} break;
				case 38:{
					boundMin.push_back(-32.0);
					boundMax.push_back(32.0);
				}break;
				case 39:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 40:{
							boundMin.push_back(-5.0);
							boundMax.push_back(5.0);
				}break;
				case 41:{
					boundMin.push_back(-0.5);
					boundMax.push_back(0.5);
				}break;
				case 42:{
					boundMin.push_back(-PI);
					boundMax.push_back(PI);
				}break;
				case 43:{
					boundMin.push_back(-3.0);
					boundMax.push_back(1.0);
				}break;
				case 44:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				}break;
				case 45:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 46:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 47:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 48:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 49:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 50:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 51:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 52:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 53:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 54:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				} break;
				case 55:{
					boundMin.push_back(2.0);
					boundMax.push_back(5.0);
				}break;
				case 56:{
					boundMin.push_back(-100.0);
					boundMax.push_back(100.0);
				}break;
				case 57:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 58:{
					boundMin.push_back(-5.0);
					boundMax.push_back(5.0);
				}break;
				case 59:{
					boundMin.push_back(-512.0);
					boundMax.push_back(512.0);
				}break;
			}
		/////////
		}
	}


	//Internal methods
	int Function_F::getN(){
		return 30;
	/*    switch(idFunction){
		case 1:
		return 10;
		case 2:
		return 20;
		case 3:
		return 10;
		case 4:
		return 5;
		case 5:
		return 4;
		case 6:
		return 2;
		case 7:
		return 10;
		case 8:
		return 2;
		case 9:
		return 7;
		case 10:
		return 8;
		case 11:
		return 2;
		case 12:
		return 3;
		case 13:
		return 5;
		case 14:
		return 10;
		case 15:
		return 3;
		case 16:
		return 5;
		case 17:
		return 6;
		case 18:
		return 7;
		case 19:
		return 15;
		case 20:
		return 24;
		case 21:
		return 7;
		case 22:
		return 22;
		case 23:
		return 9;
		case 24:
		return 2;
	  }
	  return 0;*/
	}

	int Function_F::getNConstG(){
	  return 0;
	}

	int Function_F::getNConstH(){
	  return 0;
	}

	//Best known values
	double Function_F::getBest(){
		switch(idFunction){
		case 31:
		return -450.0;
		case 32:
		return -450.0;
		case 33:
		return -450.0;
		case 34:
		return -450.0;
		case 35:
		return -310.0;
		case 36:
		return 390.0;
		case 37:
		return -180.0;
		case 38:
		return -140.0;
		case 39:
		return -330.0;
		case 40:
		return -330.0;
		case 41:
		return 90.0;
		case 42:
		return -460.0;
		case 43:
		return -130.0;
		case 44:
		return -300.0;
		case 45:
		return 120.0;
		case 46:
		return 120.0;
		case 47:
		return 120.0;
		case 48:
		return 10.0;
		case 49:
		return 10.0;
		case 50:
		return 10.0;
		case 51:
		return 360.0;
		case 52:
		return 360.0;
		case 53:
		return 360.0;
		case 54:
		return 260.0;
		case 55:
		return 260.0;
		case 56:
		return 0;
		case 57:
		return 0;
		case 58:
		return 0;
		case 59:
		return 0;
	  }
	  return 0;
	}

	void Function_F::makeName(int f, char *name){
	  if (f < 10){
		sprintf(name, "F0%d", f-30);
	  } else {
		sprintf(name, "F%d", f-30);
	  }
	}

	void Function_F::f01(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 1;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 1;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;

		// objective function
		double result = 0.0;
		for (int i = 0; i < dimension; i++) {
			result += x[i]*x[i];
		}

		f[0] = result;
*/
	}

	void Function_F::f02(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 2;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 2;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;
		double products = 1;
		double var;
		for (int i = 0; i < dimension; i++) {
			var = fabs( x[i] );
			result += var;
			products *= var;
		}
		result += products;
		f[0] = result;
*/
	}

	void Function_F::f03(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 3;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 3;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;
		double summation;
		for (int i = 0; i < dimension; i++) {
			summation = 0;
			for (int j = 0; j < i; j++) {
				summation += x[j];//*x[j];
			}
			result += summation*summation;
		}
		f[0] = result;
*/
	}

	void Function_F::f04(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 4;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 4;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		result = -1;
		double var;
		for (int i = 0; i < dimension; i++) {
			var = fabs(x[i]);
			result = var > result? var: result;
		}

		f[0] = result;
*/
	}

	void Function_F::f05(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 5;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 5;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double aux1;
		double aux2;
		for (int i = 0; i < dimension-1; i++) {
			aux1 = x[i+1]-x[i]*x[i];
			aux2 = x[i]-1;
			result += 100*aux1*aux1 + aux2*aux2;
		}

		f[0] = result;
*/
	}

	void Function_F::f06(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 6;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 6;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double aux;
		for (int i = 0; i < dimension; i++) {
			aux = floor(x[i] + 0.5);
			result += aux*aux;
		}

		f[0] = result;
*/
	}

	void Function_F::f07(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 7;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 7;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		for (int i = 0; i < dimension; i++) {
			result += (i+1)*x[i]*x[i]*x[i]*x[i];
		}
		result += Tools::newRand(0, 1);


		f[0] = result;
*/
	}

	void Function_F::f08(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 8;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 8;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		for (int i = 0; i < dimension; i++) {
			result += x[i]*sin(sqrt(fabs( x[i] ) ) );
		}

		f[0] = -result;
*/
	}

	void Function_F::f09(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 9;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 9;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		for (int i = 0; i < dimension; i++) {
			result += x[i]*x[i] - 10*cos(2*PI*x[i]) + 10;
		}

		f[0] = result;
*/
	}

	void Function_F::f10(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 10;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 10;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double sum1 = 0;
		double sum2 = 0;
		for (int i = 0; i < dimension; i++) {
			sum1 += x[i]*x[i];
			sum2 += cos(2*PI*x[i]); //Mudança para ackley do artigo de Neri
		//sum2 += cos(2*PI*x[i])*x[i];
		}
		//result = -20*exp((-0.2/(double)dimension)*sqrt(sum1)) - exp(sum2/(double)dimension) + E; + 20;
		result = -20*exp((-0.2)*sqrt((1/(double)dimension)*sum1)) - exp(sum2/(double)dimension) + E + 20;
		//result = 0 + E + exp((-0.2/(double)dimension)*sqrt(sum1)) - exp(sum2/(double)dimension);

		f[0] = result;
*/
	}

	void Function_F::f11(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 11;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 11;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double product = 1;
		for (int i = 0; i < dimension; i++) {
			product *= cos( x[i] / sqrt(i+1) );
			result += x[i]*x[i];
		}
		result = result/4000 - product + 1;

		f[0] = result;
*/
	}

	 double Function_F::u(double x, double a, double k, double m) {
		return x > a? k*pow(x-a, m): x < -a? k*pow(-x-a, m): 0;
	}

	void Function_F::f12(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 12;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 12;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();


/*		int dimension = nx;
		double result = 0.0;

		double sum1 = 0;
		double sum2 = 0;
		double aux;
		//double *y = getY(x, dimension);
		double *y = new double[dimension];

		for (int i = 0; i < dimension; i++) {
			y[i] = 1 + 0.25*(x[i] + 1);
		}
		//
		for (int i = 0; i < dimension-1; i++) {
			aux = (y[i]-1);
			sum1 += aux*aux*(1 + 10*pow(sin(PI*y[i+1]), 2));
		}
		for (int i = 0; i < dimension; i++) {
			sum2 += u(x[i], 10, 100, 4);
		}
		aux = y[dimension-1] - 1;
		result = (PI/30)*(10*pow(sin(PI*y[0]), 2) + sum1 + aux*aux) + sum2;

		delete y;
		f[0] = result;
*/
	}

	void Function_F::f13(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 13;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 13;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double sum1 = 0;
		double sum2 = 0;
		double aux;
		//double[] y = getY(x, dimension);
		double *y = new double[dimension];
		for (int i = 0; i < dimension; i++) {
			y[i] = 1 + 0.25*(x[i] + 1);
		}
		//
		for (int i = 0; i < dimension-1; i++) {
			aux = (x[i]-1);
			sum1 += aux*aux*(1 + pow(sin(3*PI*x[i+1]), 2));
		}
		for (int i = 0; i < dimension; i++) {
			sum2 += u(x[i], 5, 100, 4);
		}
		aux = x[dimension-1] - 1;
		result = 0.1*(pow(sin(3*PI*x[0]), 2) + sum1 + aux*aux*(1+pow(2*PI*x[dimension-1], 2))) + sum2;

		delete y;
		f[0] = result;
*/
	}

	void Function_F::f14(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 14;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 14;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double a[2][25] = {{-32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32},
				{-32, -32, -32, -32, -32, -16, -16, -16, -16, -16, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32}};
		double sum;
		for (int j = 0; j < 2; j++) {
			sum = 0;
			for (int i = 0; i < dimension; i++) {
				sum += pow(x[i]-a[i][j], 6);
			}
			result += 1.0/((double)j+1+sum);
		}
		result = 1.0 / (1.0/500.0 + result);

		f[0] = result;
*/
	}

	void Function_F::f15(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 15;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 15;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		double result = 0.0;

		double a[11] = {0.1957, 0.1947, 0.1735, 0.1600, 0.0844, 0.0627, 0.0456, 0.0342, 0.0323, 0.0235, 0.0246};
		double b[11] = {0.25, 0.5, 1, 2, 4, 6, 8, 10, 12, 14, 16};
		for (int i = 0; i < 11; i++) {
			b[i] = 1/b[i];
		}
		double aux;
		for (int i = 0; i < 11; i++) {
			aux = a[i] - (x[0]*(b[i]*b[i]+b[i]*x[1]))/(b[i]*b[i] + b[i]*x[2] + x[3]);
			result += aux * aux;
		}

		f[0] = result;
*/
	}

	void Function_F::f16(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 16;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 16;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*
		double result = 0.0;

		result = 4*x[0]*x[0] - 2.1*x[0]*x[0]*x[0]*x[0] + (pow(x[0], 6))/(3.0) + x[0]*x[1] -4*x[1]*x[1] + 4*x[1]*x[1]*x[1]*x[1];

		f[0] = result;
*/
	}

	void Function_F::f17(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 17;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 17;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*
		double result = 0.0;

		double aux = x[1] - (5.1*x[0]*x[0])/(4*PI*PI) + (5*x[0])/PI - 6;
		result = aux*aux + 10*(1-1/(8*PI))*cos(x[0]) + 10;

		f[0] = result;
*/
	}

	void Function_F::f18(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 18;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 18;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*
		double result = 0.0;

		double aux1 = x[0] + x[1] + 1;
		double aux2 = 2*x[0] - 3*x[1];
		result = (1+aux1*aux1*(19-14*x[0]+3*x[0]*x[0]-14*x[1]+6*x[0]*x[1]+3*x[1]*x[1]))*(30+aux2*aux2*(18-32*x[0]+12*x[0]*x[0]+48*x[1]-36*x[0]*x[1]+27*x[1]*x[1]));

		f[0] = result;
*/
	}

	void Function_F::f19(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 19;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 19;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*
		int dimension = nx;
		double result = 0.0;

		double a[4][3] = {{3, 10, 30},
				{0.1, 10, 35},
				{3, 10, 30},
				{0.1, 10, 35}};
		double c[4] = {1, 1.2, 3, 3.2};
		double p[4][3] = {{0.3689, 0.1170, 0.2673},
				{0.4699, 0.4387, 0.7470},
				{0.1091, 0.8732, 0.5547},
				{0.038150, 0.5743, 0.8828}};
		double aux;
		double sum;
		for (int i = 0; i < 4; i++) {
			sum = 0;
			for (int j = 0; j < dimension; j++) {
				aux = x[j]-p[i][j];
				sum -= a[i][j]*aux*aux;
			}
			result -= c[i]*exp(sum);
		}

		f[0] = result;
*/
	}

	void Function_F::f20(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 20;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 20;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

	double a[4][6] = {{10, 3, 17, 3.5, 1.7, 8},
				{0.05, 10, 17, 0.1, 8, 14},
				{3, 3.5, 1.7, 10, 17, 8},
				{17, 8, 0.05, 10, 0.1, 14}};
		double c[4] = {1, 1.2, 3, 3.2};
		double p[4][6] = {{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886},
				{0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
				{0.2348, 0.1415, 0.3522, 0.2883, 0.3047, 0.6650},
				{0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}};
		double aux;
		double sum;
		for (int i = 0; i < 4; i++) {
			sum = 0;
			for (int j = 0; j < dimension; j++) {
				aux = x[j]-p[i][j];
				sum -= a[i][j]*aux*aux;
			}
			result -= c[i]*exp(sum);
		}

		f[0] = result;
*/
	}

	void Function_F::f21(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 21;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 21;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double a[5][4] = {{4, 4, 4, 4},
				{1, 1, 1, 1},
				{8, 8, 8, 8},
				{6, 6, 6, 6},
				{3, 7, 3, 7}};
		double c[5] = {0.1, 0.2, 0.2, 0.4, 0.4};
		double *aux;
		int m = 5;
		for (int i = 0; i < m; i++) {
			aux = new double[dimension];
			for (int j = 0; j < dimension; j++) {
				aux[j] = x[j] - a[i][j];
			}
			result -= 1.0/(product(aux, aux, dimension) + c[i]);
		}

		delete aux;
		f[0] = result;
*/
	}

	double Function_F::product(double *v1, double *v2, int n) {

		double result = 0;
		int i = 0;
		for (int j = 0; j < n; j++) {
			double d = v1[j];
			result += d*v2[i];
			i++;
		}
		return result;
	}

	void Function_F::f22(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 22;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 22;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double a[7][4] = {{4, 4, 4, 4},
				{1, 1, 1, 1},
				{8, 8, 8, 8},
				{6, 6, 6, 6},
				{3, 7, 3, 7},
				{2, 9, 2, 9},
				{5, 5, 3, 3}};
		double c[7] = {0.1, 0.2, 0.2, 0.4, 0.4, 0.6, 0.3};
		double *aux;
		int m = 7;
		for (int i = 0; i < m; i++) {
			aux = new double[dimension];
			for (int j = 0; j < dimension; j++) {
			aux[j] = x[j] - a[i][j];
			}
			result -= 1.0/(product(aux, aux, dimension) + c[i]);
		}

		delete aux;
		f[0] = result;
*/
	}

	void Function_F::f23(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 23;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 23;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*		int dimension = nx;
		double result = 0.0;

		double a[10][4] = {{4, 4, 4, 4},
				{1, 1, 1, 1},
				{8, 8, 8, 8},
				{6, 6, 6, 6},
				{3, 7, 3, 7},
				{2, 9, 2, 9},
				{5, 5, 3, 3},
				{8, 1, 8, 1},
				{6, 2, 6, 2},
				{7, 3.6, 7, 3.6}};
		double c[10] = {0.1, 0.2, 0.2, 0.4, 0.4, 0.6, 0.3, 0.7, 0.5, 0.5};
		double *aux;
		int m = 10;
		for (int i = 0; i < m; i++) {
			aux = new double[dimension];
			for (int j = 0; j < dimension; j++) {
				aux[j] = x[j] - a[i][j];
			}
			result -= 1.0/(product(aux, aux, dimension) + c[i]);
		}

		delete aux;
		f[0] = result;
*/
	}

	void Function_F::f24(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 24;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 24;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*
		double result = 0.0;

		//
		//		FRACTAL - Nao implementado
		//

		f[0] = result;
*/
	}

	void Function_F::f25(double *x, double *f, int nx)
	{
		int i;
		Functions_Code code;
		code.nreal = nx;
		code.nfunc = 25;
		code.allocate_memory();

		//recupera a funcao a ser otimizada
		int func = 25;

		code.initialize_f(func);
		*f = code.calc_benchmark_func(func, x);

		/* Routine to free the memory allocated at run time */
		code.free_memory();

/*
		double result = 0.0;

		//
		//		Nao implementado
		//

		f[0] = result;
*/
	}

	void Function_F::f26(double *x, double *f, int nx)
	{
		/* objective function */
		double result = 0.0;

		/**
				Nao implementado
		*/

		f[0] = result;
	}

	void Function_F::f27(double *x, double *f, int nx)
	{
		/* objective function */
		double result = 0.0;

		/**
				Nao implementado
		*/


		f[0] = result;
	}

	void Function_F::f28(double *x, double *f, int nx)
	{
		/* objective function */
		double result = 0.0;

		/**
				Nao implementado
		*/

		f[0] = result;
	}

	void Function_F::f29(double *x, double *f, int nx)
	{
		int dimension = nx;
		/* objective function */
		double result = 0.0;

		double sum = 0.0;
		for (int i = 0; i < dimension-1; i++) {
			sum += (-x[i] * sin(sqrt(fabs(x[i] - (x[i+1] + 47)))) - (x[i+1] + 47) * sin(sqrt(fabs(x[i+1] + 47 + (x[i] / 2)))));
		}
		result = sum;

		f[0] = result;
	}

	Function_F::~Function_F(){

	}

} /* namespace function */
}

