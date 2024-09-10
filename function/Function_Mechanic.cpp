/*
 * FunctionMechanic.cpp
 *
 *  Created on: 02/05/2012
 *      Author: krempser
 */

#include "Function_Mechanic.h"

#include "../base/Tools.h"
using namespace opt::base;

namespace opt {
namespace function {

	Function_Mechanic::Function_Mechanic(int id){
		idFunction = -id;

		nDimensions  = getN();
		nConstraints = getNConstH() + getNConstG();

		//Define the bounds
		setBounds();

		g = 0;
		h = 0;
	}

	void Function_Mechanic::calc(const vector<double> values, double &fitness, vector<double> &constVal){
		Function::calc(values, fitness, constVal);
		int n, ng, nh, i;
		n = getNDimensions();
		ng = getNConstG();
		nh = getNConstH();

		//Convert the variables in correct range
		int j;
		double *xTemp;
		char fName[4];
		makeName(idFunction, fName);
		xTemp = (double *)malloc(n*sizeof(double));
		for (j = 0; j < n; j++){
			xTemp[j] = convertToRealRange(j, values[j]);
		}

		//Evaluate
		if (g == 0)
			g = (double*)malloc(ng*sizeof(double));
		else
			g = (double*)realloc(g, ng*sizeof(double));

		if (h == 0)
			h = (double*)malloc(nh*sizeof(double));
		else
			h = (double*)realloc(h, nh*sizeof(double));
		switch(idFunction){
			case 1: weldedBeam(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 2: pressureVessel(xTemp, &f, g, h, n, 1, ng, nh);
				break;
		}

		//Set values
		fitness = f;

		constVal.clear();
		//Set constraints
		for (i = 0; i < ng; i++){
			constVal.push_back(g[i]);
		}
		for (i = 0; i < nh; i++){
			if (fabs(h[i]) - 0.0001 > 0){//0.00001
				constVal.push_back(fabs(h[i]));
			} else {
				constVal.push_back(0.0);
			}
		}
	}

	double Function_Mechanic::convertToRealRange(int index, double val){
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

	double Function_Mechanic::getBoundMax(int index){
		return boundMax[index];
	}

	double Function_Mechanic::getBoundMin(int index){
		return boundMin[index];
	}

	//Define the bounds of the variables
	void Function_Mechanic::setBounds(){
		boundMin.clear();
		boundMax.clear();
		for(int variable = 0; variable < getNDimensions(); variable++){
	//////////////
			switch(idFunction){
				case 1:{
					if (variable < 1){
						boundMin.push_back(0.125);
						boundMax.push_back(10.0);
					} else {
						boundMin.push_back(0.1);
						boundMax.push_back(10.0);
					}
				} break;
				case 2:{
					if (variable < 2){
						boundMin.push_back(0.0625);
						boundMax.push_back(5.0);
						double sum = 0;
						for (int i = 0; i < 80; i++){
							sum += 0.0625;
							discretization.push_back(sum);
						}
						discreteVariables.push_back(variable);
					} else {
						boundMin.push_back(10.0);
						boundMax.push_back(200.0);
					}
				} break;
			}
		/////////
		}
	}


	//Internal methods
	int Function_Mechanic::getN(){
		switch(idFunction){
		case 1:
		return 4;
		case 2:
		return 4;
	  }
	  return 0;
	}

	int Function_Mechanic::getNConstG(){
	  switch(idFunction){
		case 1:
		return 5;
		case 2:
		return 3;
	  }
	  return 0;
	}

	int Function_Mechanic::getNConstH(){
	  switch(idFunction){
		case 3:
		return 1;
		case 5:
		return 3;
		case 11:
		return 1;
		case 13:
		return 3;
		case 14:
		return 3;
		case 15:
		return 2;
		case 17:
		return 4;
		case 20:
		return 14;
		case 21:
		return 5;
		case 22:
		return 19;
		case 23:
		return 4;
	  }
	  return 0;
	}

	//Best known values
	double Function_Mechanic::getBest(){
		switch(idFunction){
		case 1:
		return 2.3811;
		case 2:
		return 6059.71;
	  }
	  return 0;
	}

	void Function_Mechanic::makeName(int f, char *name){
	  if (f < 10){
		sprintf(name, "Mc0%d", f);
	  } else {
		sprintf(name, "Mc%d", f);
	  }
	}

	void Function_Mechanic::weldedBeam (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  //Objective function --> f(h, l, t, b)
	  f[0] = 1.10471*(x[0]*x[0])*x[1]+0.04811*x[2]*x[3]*(14.0+x[1]);

	  //Constraints g <= 0
	  double alpha = sqrt(0.25*(x[1] + pow(x[0] + x[2], 2)));
	  double tal_l = 6000/(sqrt(2)*x[0]*x[1]);
	  double tal_ll = (6000*( 14 + 0.5*x[1] )*alpha)/( 2*( 0.707*x[0]*x[1]*( x[1]/12 + 0.25*pow(x[0] + x[1], 2) ) ) );
	  double tal = sqrt(tal_l * tal_l + tal_ll * tal_ll + (x[1]*tal_l*tal_ll)/alpha);
	  double sigma = 504000/(x[2]*x[2]*x[3]);
	  double Pc = 64746.022 * ( 1 - 0.0282346*x[2] ) *x[2]*x[3]*x[3]*x[3];
	  double delta = 2.195/(x[2]*x[2]*x[2]*x[3]);

	  g[0] = tal - 13600;
	  g[1] = sigma - 30000;
	  g[2] = x[0] - x[3];
	  g[3] = Pc - 6000;
	  g[4] = delta - 0.25;
	}

	void Function_Mechanic::pressureVessel(double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  double Ts, Th, R, L;
	  Ts = x[0];
	  Th = x[1];
	  R =  x[2];
	  L =  x[3];
	  f[0] = 0.6224*Ts*R*L+1.7781*Th*R*R +3.1661*Ts*Ts*L+19.84*Ts*Ts*R;
	  g[0] = 0.0193*R - Ts;
	  g[1] = 0.00954*R - Th;
	  g[2] = -(M_PI*R*R*L) - (1.33333)*(M_PI*R*R*R) + 1296000;
	}





} /* namespace function */
} /* namespace opt */
