/*
 * Function_Truss.cpp
 *
 *  Created on: 18/05/2012
 *      Author: krempser
 */

#include "Function_Truss.h"

#include "../base/Tools.h"
using namespace opt::base;

namespace opt {
namespace function {

	Function_Truss::Function_Truss(int id){
		idFunction = -id;

		if (idFunction == 10){
			problem = new Function_Truss_10_Bar();
		} else if (idFunction == 11){
			problem = new Function_Truss_10_Bar_Discrete();
		} else if (idFunction == 25){
			problem = new Function_Truss_25_Bar();
		} else if (idFunction == 26){
			problem = new Function_Truss_25_Bar_Discrete();
		} else if (idFunction == 60){
			problem = new Function_Truss_60_Bar();
		} else if (idFunction == 61){
			problem = new Function_Truss_60_Bar_Discrete();
		} else if (idFunction == 72){
			problem = new Function_Truss_72_Bar();
		} else if (idFunction == 73){
			problem = new Function_Truss_72_Bar_Discrete();
		} else if (idFunction == 942){
			problem = new Function_Truss_942_Bar();
		} else if (idFunction == 943){
			problem = new Function_Truss_942_Bar_Discrete();
		} else if (idFunction == 200){
			//problem = new F111Truss200Bar();
		} else if (idFunction == 201){
			//problem = new F112Truss200BarDiscrete();
		} else if (idFunction == 960){
			//problem = new F113Truss960Bar();
		} else if (idFunction == 961){
			//problem = new F114Truss960BarDiscrete();
		}


		nDimensions  = problem->getDimension();
		nConstraints = problem->getNumberConstraints();

		//Define the bounds
		setBounds();
	}

	void Function_Truss::calc(const vector<double> values, double &fitness, vector<double> &constVal){
		Function::calc(values, fitness, constVal);

		//Convert the variables in correct range
		int j;
		double *xTemp, *g;
		char fName[4];
		makeName(idFunction, fName);
		xTemp = (double *)malloc(nDimensions*sizeof(double));
		for (j = 0; j < nDimensions; j++){
			xTemp[j] = convertToRealRange(j, values[j]);
		}

		//Evaluate
		g = (double*)malloc((nConstraints+1)*sizeof(double));

		problem->evaluate(xTemp, g);

		//Set values
		fitness = g[0];

		constVal.clear();
		//Set constraints
		for (int i = 1; i <= nConstraints; i++){
			constVal.push_back(g[i]);
		}

		free( g );
		free( xTemp );
	}

	double Function_Truss::convertToRealRange(int index, double val){
		int discrete = 0;

		for(int i = 0; i < (int)discreteVariables.size(); i++){
			if (discreteVariables[i] == index){
				discrete = 1;
			}
		}

		if (!discrete){
			//return ((val)*(boundMax[index] - boundMin[index])) + boundMin[index];
			return Tools::convertToRealRange(index, val);
		} else {
			//val = ((val)*(boundMax[index] - boundMin[index])) + boundMin[index];
			val = Tools::convertToRealRange(index, val);
			double dif, difTemp, temp;
			temp = discretization[0];
			dif  = fabs(val - discretization[0]);
			for (int i = 1; i < (int)discretization.size(); i++){
				difTemp = fabs(val - discretization[i]);
				if (difTemp < dif){
					dif = difTemp;
					temp = discretization[i];
				}
			}
			return temp;
		}
	}

	double Function_Truss::getBoundMax(int index){
		return boundMax[index];
	}

	double Function_Truss::getBoundMin(int index){
		return boundMin[index];
	}

	//Define the bounds of the variables
	void Function_Truss::setBounds(){
		boundMin.clear();
		boundMax.clear();
		discreteVariables.clear();
		discretization.clear();

		for(int variable = 0; variable < getNDimensions(); variable++){
	//////////////
			switch(idFunction){
				case 10:{
					boundMin.push_back(0.1);
					boundMax.push_back(40.0);
				} break;
				case 11:{
						boundMin.push_back(1.62);
						boundMax.push_back(33.50);

						if (discretization.size() <= 0){
							discretization.push_back(1.62);
							discretization.push_back(1.80);
							discretization.push_back(1.99);
							discretization.push_back(2.13);
							discretization.push_back(2.38);
							discretization.push_back(2.62);
							discretization.push_back(2.63);
							discretization.push_back(2.88);
							discretization.push_back(2.93);
							discretization.push_back(3.09);
							discretization.push_back(3.13);
							discretization.push_back(3.38);
							discretization.push_back(3.47);
							discretization.push_back(3.55);
							discretization.push_back(3.63);
							discretization.push_back(3.84);
							discretization.push_back(3.87);
							discretization.push_back(3.88);
							discretization.push_back(4.18);
							discretization.push_back(4.22);
							discretization.push_back(4.49);
							discretization.push_back(4.59);
							discretization.push_back(4.80);
							discretization.push_back(4.97);
							discretization.push_back(5.12);
							discretization.push_back(5.74);
							discretization.push_back(7.22);
							discretization.push_back(7.97);
							discretization.push_back(11.50);
							discretization.push_back(13.50);
							discretization.push_back(13.90);
							discretization.push_back(14.20);
							discretization.push_back(15.50);
							discretization.push_back(16.00);
							discretization.push_back(16.90);
							discretization.push_back(18.80);
							discretization.push_back(19.90);
							discretization.push_back(22.00);
							discretization.push_back(22.90);
							discretization.push_back(26.50);
							discretization.push_back(30.00);
							discretization.push_back(33.50);
						}

						discreteVariables.push_back(variable);
				} break;
				case 25:{
					boundMin.push_back(0.1);
					boundMax.push_back(3.4);
				} break;
				case 26:{
					boundMin.push_back(0.1);
					boundMax.push_back(3.4);

					if (discretization.size() <= 0){
						discretization.push_back(0.1);
						discretization.push_back(0.2);
						discretization.push_back(0.3);
						discretization.push_back(0.4);
						discretization.push_back(0.5);
						discretization.push_back(0.6);
						discretization.push_back(0.7);
						discretization.push_back(0.8);
						discretization.push_back(0.9);
						discretization.push_back(1.0);
						discretization.push_back(1.1);
						discretization.push_back(1.2);
						discretization.push_back(1.3);
						discretization.push_back(1.4);
						discretization.push_back(1.5);
						discretization.push_back(1.6);
						discretization.push_back(1.7);
						discretization.push_back(1.8);
						discretization.push_back(1.9);
						discretization.push_back(2.0);
						discretization.push_back(2.1);
						discretization.push_back(2.2);
						discretization.push_back(2.3);
						discretization.push_back(2.4);
						discretization.push_back(2.5);
						discretization.push_back(2.6);
						discretization.push_back(2.8);
						discretization.push_back(3.0);
						discretization.push_back(3.2);
						discretization.push_back(3.4);
					}

					discreteVariables.push_back(variable);
				} break;
				case 60:{
					boundMin.push_back(0.5);
					boundMax.push_back(5.0);
				} break;
				case 61:{
					boundMin.push_back(0.5);
					boundMax.push_back(5.0);

					int dist = 46;
					discretization.push_back(0.5);
					for(int i = 1; i < dist; i++){
						discretization.push_back(discretization[i - 1] + 0.1);
					}
					discreteVariables.push_back(variable);
				} break;
				case 72:{
					boundMin.push_back(0.1);
					boundMax.push_back(2.5);
				} break;
				case 73:{
					boundMin.push_back(0.1);
					boundMax.push_back(2.5);

					int dist = 25;
					discretization.push_back(0.1);
					for(int i = 1; i < dist; i++){
						discretization.push_back(discretization[i - 1] + 0.1);
					}
					discreteVariables.push_back(variable);
				} break;
				case 942:{
					boundMin.push_back(1.0);
					boundMax.push_back(200);
				} break;
				case 943:{
					boundMin.push_back(1.0);
					boundMax.push_back(200);

					int dist = 200;
					discretization.push_back(1.0);
					for(int i = 1; i < dist; i++){
						discretization.push_back(discretization[i - 1] + 1.0);
					}
					discreteVariables.push_back(variable);
				} break;
				case 200:{
					boundMin.push_back(0.1);
					boundMax.push_back(30);
				} break;
				case 201:{
					boundMin.push_back(0.1);
					boundMax.push_back(30);
					int dist = 31;
					discretization.push_back(0.1);
					discretization.push_back(1.0);
					for(int i = 2; i < dist; i++){
						discretization.push_back(discretization[i - 1] + 1.0);
					}
					discreteVariables.push_back(variable);
				} break;
				case 960:{
					boundMin.push_back(1.0);
					boundMax.push_back(30);
				} break;
				case 961:{
					boundMin.push_back(1.0);
					boundMax.push_back(30);
					int dist = 30;
					discretization.push_back(1.0);
					for(int i = 1; i < dist; i++){
						discretization.push_back(discretization[i - 1] + 1.0);
					}
					discreteVariables.push_back(variable);
				} break;

			}
		/////////
		}
	}


	//Best known values
	double Function_Truss::getBest(){
		switch(idFunction){
		case 10:
			return 5060.85;
		case 11: // 10 - discrete
			return 5490.70;
		case 25:
			return 484.05;
		case 26: //25 - discrete
			return 484.85;
		case 60:
			return 309.14;
		case 61:
			return 309.14; //TODO verificar esse valor
		case 72:
			return 379.62;
		case 73:
			return 379.62; //TODO verificar esse valor
		case 942:
			return 141208.00;
		case 943: // 942 - discrete
			return 141241.00; //TODO verificar esse valor
		case 200:
			return 24852.58;
		case 201:
			return 24852.58;
		case 960:
			return 1.0;
		case 961:
			return 1.0;
	  }
	  return 0;
	}

	void Function_Truss::makeName(int f, char *name){
	  if (f < 10){
		sprintf(name, "Truss0%d", f);
	  } else {
		sprintf(name, "Truss%d", f);
	  }
	}

	Function_Truss::~Function_Truss() {

		delete this->problem;

	}




} /* namespace function */
} /* namespace opt */
