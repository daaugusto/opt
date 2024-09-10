/*
 * Function_G.cpp
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#include "Function_G.h"

namespace opt {
namespace function {

	Function_G::Function_G(int id){
		idFunction = id;

		nDimensions  = getN();
		nConstraints = getNConstH() + getNConstG();

		//Define the bounds
		setBounds();

		g = 0;
		h = 0;
	}

	void Function_G::calc(const vector<double> values, double &fitness, vector<double> &constVal){
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
			case 1: g01(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 2: g02(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 3: g03(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 4: g04(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 5: g05(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 6: g06(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 7: g07(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 8: g08(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 9: g09(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 10: g10(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 11: g11(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 12: g12(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 13: g13(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 14: g14(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 15: g15(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 16: g16(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 17: g17(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 18: g18(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 19: g19(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 20: g20(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 21: g21(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 22: g22(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 23: g23(xTemp, &f, g, h, n, 1, ng, nh);
				break;
			case 24: g24(xTemp, &f, g, h, n, 1, ng, nh);
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

	/*
	double Function_G::convertToRealRange(int index, double val){
		return ((val)*(boundMax[index] - boundMin[index])) + boundMin[index];
	}
	*/

	double Function_G::getBoundMax(int index){
			return boundMax[index];
		}

	double Function_G::getBoundMin(int index){
		return boundMin[index];
	}


	//Define the bounds of the variables
	void Function_G::setBounds(){
		boundMin.clear();
		boundMax.clear();
		for(int variable = 0; variable < getNDimensions(); variable++){
	//////////////
			switch(idFunction){
				case 1:{
					if (variable < 9){
						boundMin.push_back(0.0);
						boundMax.push_back(1.0);
					} else if (variable < 12){
						boundMin.push_back(0.0);
						boundMax.push_back(100.0);
					} else {
						boundMin.push_back(0.0);
						boundMax.push_back(1.0);
					}
				} break;
				case 2:{
					boundMin.push_back(0.0);
					boundMax.push_back(10.0);
				} break;
				case 3:{
					boundMin.push_back(0.0);
					boundMax.push_back(1.0);
				} break;
				case 4:{
					if (variable < 1){
						boundMin.push_back(78.0);
						boundMax.push_back(102.0);
					} else if (variable < 2){
						boundMin.push_back(33.0);
						boundMax.push_back(45.0);
					} else {
						boundMin.push_back(27.0);
						boundMax.push_back(45.0);
					}
				} break;
				case 5:{
					if (variable < 1){
						boundMin.push_back(10.0);
						boundMax.push_back(1200.0);
					} else if (variable < 2){
						boundMin.push_back(0.0);
						boundMax.push_back(1200.0);
					} else if (variable < 3){
						boundMin.push_back(-0.55);
						boundMax.push_back(0.55);
					} else {
						boundMin.push_back(-0.55);
						boundMax.push_back(0.55);
					}
				} break;
				case 6:{
					if (variable < 1){
						boundMin.push_back(13.0);
						boundMax.push_back(100.0);
					}else {
						boundMin.push_back(10.0);
						boundMax.push_back(100.0);
					}
				} break;
				case 7:{
					boundMin.push_back(-10.0);
					boundMax.push_back(10.0);
				} break;
				case 8:{
					boundMin.push_back(0.0);
					boundMax.push_back(10.0);
				}break;
				case 9:{
					boundMin.push_back(-10.0);
					boundMax.push_back(10.0);
				}break;
				case 10:{
					if (variable < 1){
						boundMin.push_back(100.0);
						boundMax.push_back(10000.0);
					} else if (variable < 3){
						boundMin.push_back(1000.0);
						boundMax.push_back(10000.0);
					} else {
						boundMin.push_back(10.0);
						boundMax.push_back(1000.0);
					}
				}break;
				case 11:{
					boundMin.push_back(-1.0);
					boundMax.push_back(1.0);
				}break;
				case 12:{
					boundMin.push_back(0.0);
					boundMax.push_back(10.0);
				}break;
				case 13:{
					if (variable < 2){
						boundMin.push_back(-2.3);
						boundMax.push_back(2.3);
					} else {
						boundMin.push_back(-3.2);
						boundMax.push_back(3.2);
					}
				}break;
				case 14:{
					boundMin.push_back(0.0);
					boundMax.push_back(10.0);
				}break;
				case 15:{
					boundMin.push_back(0.0);
					boundMax.push_back(10.0);
				}break;
				case 16:{
					if (variable < 1){
						boundMin.push_back(704.4148);
						boundMax.push_back(906.3855);
					} else if (variable < 2){
						boundMin.push_back(68.6);
						boundMax.push_back(288.88);
					} else if (variable < 3){
						boundMin.push_back(0.0);
						boundMax.push_back(134.75);
					} else if (variable < 4){
						boundMin.push_back(193.0);
						boundMax.push_back(287.0966);
					} else {
						boundMin.push_back(25.0);
						boundMax.push_back(84.1988);
					}
				}break;
				case 17:{
					if (variable < 1){
						boundMin.push_back(0.0);
						boundMax.push_back(400.0);
					} else if (variable < 2){
						boundMin.push_back(0.0);
						boundMax.push_back(1000.0);
					} else if (variable < 3){
						boundMin.push_back(340.0);
						boundMax.push_back(420.0);
					} else if (variable < 4){
						boundMin.push_back(340.0);
						boundMax.push_back(420.0);
					} else if (variable < 5){
						boundMin.push_back(-1000.0);
						boundMax.push_back(1000.0);
					} else {
						boundMin.push_back(0.0);
						boundMax.push_back(0.5236);
					}
				}break;
				case 18:{
					if (variable < 8){
						boundMin.push_back(-10.0);
						boundMax.push_back(10.0);
					} else {
						boundMin.push_back(0.0);
						boundMax.push_back(20.0);
					}
				}break;
				case 19:{
					boundMin.push_back(0.0);
					boundMax.push_back(10.0);
				}break;
				case 20:{
					boundMin.push_back(0.0);
					boundMax.push_back(10.0);
				}break;
				case 21:{
					if (variable < 1){
						boundMin.push_back(0.0);
						boundMax.push_back(1000.0);
					} else if (variable < 3){
						boundMin.push_back(0.0);
						boundMax.push_back(40.0);
					} else if (variable < 4){
						boundMin.push_back(100.0);
						boundMax.push_back(300.0);
					} else if (variable < 5){
						boundMin.push_back(6.3);
						boundMax.push_back(6.7);
					} else if (variable < 6){
						boundMin.push_back(5.9);
						boundMax.push_back(6.4);
					} else {
						boundMin.push_back(4.5);
						boundMax.push_back(6.25);
					}
				}break;
				case 22:{
					 if (variable < 1){
						boundMin.push_back(0.0);
						boundMax.push_back(20000.0);
					} else if (variable < 4){
						boundMin.push_back(0.0);
						boundMax.push_back(1.0E6);
					} else if (variable < 7){
						boundMin.push_back(0.0);
						boundMax.push_back(4.0E7);
					} else if (variable < 8){
						boundMin.push_back(100.0);
						boundMax.push_back(299.99);
					} else if (variable < 9){
						boundMin.push_back(10.0);
						boundMax.push_back(399.99);
					} else if (variable < 10){
						boundMin.push_back(10.1);
						boundMax.push_back(300.0);
					} else if (variable < 11){
						boundMin.push_back(100.0);
						boundMax.push_back(400.0);
					} else if (variable < 12){
						boundMin.push_back(100.0);
						boundMax.push_back(600.0);
					} else if (variable < 15){
						boundMin.push_back(0.0);
						boundMax.push_back(500.0);
					} else if (variable < 16){
						boundMin.push_back(0.01);
						boundMax.push_back(300.0);
					} else if (variable < 17){
						boundMin.push_back(0.01);
						boundMax.push_back(400.0);
					} else{
						boundMin.push_back(-4.7);
						boundMax.push_back(6.25);
					}
				}break;
				case 23:{
					if (variable < 2){
						boundMin.push_back(0.0);
						boundMax.push_back(300.0);
					} else if (variable < 3){
						boundMin.push_back(0.0);
						boundMax.push_back(100.0);
					} else if (variable < 4){
						boundMin.push_back(0.0);
						boundMax.push_back(200.0);
					} else if (variable < 5){
						boundMin.push_back(0.0);
						boundMax.push_back(100.0);
					} else if (variable < 6){
						boundMin.push_back(0.0);
						boundMax.push_back(300.0);
					} else if (variable < 7){
						boundMin.push_back(0.0);
						boundMax.push_back(100.0);
					} else if (variable < 8){
						boundMin.push_back(0.0);
						boundMax.push_back(200.0);
					} else {
						boundMin.push_back(0.01);
						boundMax.push_back(0.03);
					}
				}break;
				case 24:{
					if (variable < 1){
						boundMin.push_back(0.0);
						boundMax.push_back(3.0);
					} else {
						boundMin.push_back(0.0);
						boundMax.push_back(4.0);
					}
				} break;
			}
		/////////
		}
	}


	//Internal methods
	int Function_G::getN(){
		switch(idFunction){
		case 1:
		return 13;
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
	  return 0;
	}

	int Function_G::getNConstG(){
	  switch(idFunction){
		case 1:
		return 9;
		case 2:
		return 2;
		case 4:
		return 6;
		case 5:
		return 2;
		case 6:
		return 2;
		case 7:
		return 8;
		case 8:
		return 2;
		case 9:
		return 4;
		case 10:
		return 6;
		case 12:
		return 1;
		case 16:
		return 38;
		case 17:
		return 0;
		case 18:
		return 13;
		case 19:
		return 5;
		case 20:
		return 6;
		case 21:
		return 1;
		case 22:
		return 1;
		case 23:
		return 2;
		case 24:
		return 2;
	  }
	  return 0;
	}

	int Function_G::getNConstH(){
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
	double Function_G::getBest(){
		switch(idFunction){
		case 1:
		return -15;
		case 2:
		return -0.8036191042;
		case 3:
		return -1.0005001000;
		case 4:
		return -30665.5386717834;
		case 5:
		return 5126.4967140071;
		case 6:
		return -6961.8138755802;
		case 7:
		return 24.3062090681;
		case 8:
		return -0.0958250415;
		case 9:
		return 680.6300573745;
		case 10:
		return 7049.2480205286;
		case 11:
		return 0.7499000000;
		case 12:
		return -1.0;
		case 13:
		return 0.0539415140;
		case 14:
		return -47.7648884595;
		case 15:
		return 961.7150222899;
		case 16:
		return -1.9051552586;
		case 17:
		return 8853.5396748064;
		case 18:
		return -0.8660254038;
		case 19:
		return 32.6555929502;
		case 20:
		return 0.2049794002;
		case 21:
		return 193.7245100700;
		case 22:
		return 236.4309755040;
		case 23:
		return -400.0551;
		case 24:
		return -5.5080132716;
	  }
	  return 0;
	}

	void Function_G::makeName(int f, char *name){
	  if (f < 10){
		sprintf(name, "g0%d", f);
	  } else {
		sprintf(name, "g%d", f);
	  }
	}

	void Function_G::g01 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  int j;

	  /* objective function */
	  f[0] = 5.0 * (x[0] + x[1] + x[2] + x[3]) - 5.0 * (x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3]);
	  for (j = 4; j < 13; j++)
		f[0] = f[0] - x[j];
	  /* constraints g<=0 */
	  g[0] = 2.0 * x[0] + 2.0 * x[1] + x[9] + x[10] - 10.;
	  g[1] = 2.0 * x[0] + 2.0 * x[2] + x[9] + x[11] - 10.;
	  g[2] = 2.0 * x[1] + 2.0 * x[2] + x[10] + x[11] - 10.;
	  g[3] = -8.0 * x[0] + x[9];
	  g[4] = -8.0 * x[1] + x[10];
	  g[5] = -8.0 * x[2] + x[11];
	  g[6] = -2.0 * x[3] - x[4] + x[9];
	  g[7] = -2.0 * x[5] - x[6] + x[10];
	  g[8] = -2.0 * x[7] - x[8] + x[11];
	}

	void Function_G::g02 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  int j;
	  double f1, f2, f3, g1, g2;

	  /* objective function */
	  f1 = 0.;
	  f2 = 1.;
	  f3 = 0.;
	  g1 = 1.;
	  g2 = 0.;
	  for (j = 0; j < nx; j++)
		{
		  f1 = f1 + pow (cos (x[j]), 4);
		  f2 = f2 * cos (x[j]) * cos (x[j]);
		  f3 = f3 + ((double) (j + 1)) * x[j] * x[j];
		  g1 = g1 * x[j];
		  g2 = g2 + x[j];
		}
	  f[0] = fabs ((f1 - 2 * f2) / sqrt (f3));
	  f[0] = -f[0]; /* Max-->Min, Modified by Jane,Nov 22 2005 */
	  /* constraints g<=0 */
	  g[0] = 0.75 - g1;
	  g[1] = g2 - 7.5 * ((double) nx);
	}

	void Function_G::g03 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  int j;
	  double f1, f2, f3 = sqrt ((double) nx);

	  /* objective function */
	  f1 = 1.;
	  f2 = 0.;
	  for (j = 0; j < nx; j++)
		{
		  f1 = f3 * f1 * x[j];
		  f2 = f2 + x[j] * x[j];
		}
	  f[0] = f1;
	  f[0] = -f[0]; /* Max-->Min, Modified by Jane,Nov 22 2005 */
	  /* constraints g<=0 */
	  h[0] = f2 - 1.0;
	}

	void Function_G::g04 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = 5.3578547 * x[2] * x[2] + 0.8356891 * x[0] * x[4] + 37.293239 * x[0] - 40792.141;
	  /* constraints g<=0 */
	  g[0] = 85.334407 + 0.0056858 * x[1] * x[4] + 0.0006262 * x[0] * x[3] - 0.0022053 * x[2] * x[4] - 92.;
	  g[1] = -85.334407 - 0.0056858 * x[1] * x[4] - 0.0006262 * x[0] * x[3] + 0.0022053 * x[2] * x[4];
	  g[2] = 80.51249 + 0.0071317 * x[1] * x[4] + 0.0029955 * x[0] * x[1] + 0.0021813 * x[2] * x[2] - 110.;
	  g[3] = -80.51249 - 0.0071317 * x[1] * x[4] - 0.0029955 * x[0] * x[1] - 0.0021813 * x[2] * x[2] + 90.;
	  g[4] = 9.300961 + 0.0047026 * x[2] * x[4] + 0.0012547 * x[0] * x[2] + 0.0019085 * x[2] * x[3] - 25.;
	  g[5] = -9.300961 - 0.0047026 * x[2] * x[4] - 0.0012547 * x[0] * x[2] - 0.0019085 * x[2] * x[3] + 20.;
	}

	void Function_G::g05 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = 3.0 * x[0] + 0.000001 * pow (x[0], 3) + 2.0 * x[1] + (0.000002 / 3.0) * pow (x[1], 3);
	  /* constraints h=0 => g=|h|-delta<=0 */
	  g[0] = -x[3] + x[2] - 0.55;
	  g[1] = -x[2] + x[3] - 0.55;
	  h[0] = 1000.0 * sin (-x[2] - 0.25) + 1000.0 * sin (-x[3] - 0.25) + 894.8 - x[0];
	  h[1] = 1000.0 * sin (x[2] - 0.25) + 1000.0 * sin (x[2] - x[3] - 0.25) + 894.8 - x[1];
	  h[2] = 1000.0 * sin (x[3] - 0.25) + 1000.0 * sin (x[3] - x[2] - 0.25) + 1294.8;
	}

	void Function_G::g06 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = pow ((x[0] - 10.), 3) + pow ((x[1] - 20.), 3);
	  /* constraints */
	  g[0] = 100. - (x[0] - 5.) * (x[0] - 5.) - (x[1] - 5.) * (x[1] - 5.);
	  g[1] = (x[0] - 6.) * (x[0] - 6.) + (x[1] - 5.) * (x[1] - 5.) - 82.81;
	}

	void Function_G::g07 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] =
		x[0] * x[0] + x[1] * x[1] + x[0] * x[1] - 14.0 * x[0] - 16.0 * x[1] + (x[2] - 10.0) * (x[2] - 10.0) + 4.0 * (x[3] -
															 5.0) *
		(x[3] - 5.0) + (x[4] - 3.0) * (x[4] - 3.0) + 2.0 * (x[5] - 1.0) * (x[5] - 1.0) + 5.0 * x[6] * x[6] + 7.0 * (x[7] -
															11) *
		(x[7] - 11) + 2.0 * (x[8] - 10.0) * (x[8] - 10.0) + (x[9] - 7.0) * (x[9] - 7.0) + 45.;
	  /* constraints g<=0 */
	  g[0] = -105.0 + 4.0 * x[0] + 5.0 * x[1] - 3.0 * x[6] + 9.0 * x[7];
	  g[1] = 10.0 * x[0] - 8.0 * x[1] - 17.0 * x[6] + 2.0 * x[7];
	  g[2] = -8.0 * x[0] + 2.0 * x[1] + 5.0 * x[8] - 2.0 * x[9] - 12.0;
	  g[3] = 3.0 * (x[0] - 2.0) * (x[0] - 2.0) + 4.0 * (x[1] - 3.0) * (x[1] - 3.0) + 2.0 * x[2] * x[2] - 7.0 * x[3] - 120.0;
	  g[4] = 5.0 * x[0] * x[0] + 8.0 * x[1] + (x[2] - 6.0) * (x[2] - 6.0) - 2.0 * x[3] - 40.0;
	  g[5] = x[0] * x[0] + 2.0 * (x[1] - 2.0) * (x[1] - 2.0) - 2.0 * x[0] * x[1] + 14.0 * x[4] - 6.0 * x[5];
	  g[6] = 0.5 * (x[0] - 8.0) * (x[0] - 8.0) + 2.0 * (x[1] - 4.0) * (x[1] - 4.0) + 3.0 * x[4] * x[4] - x[5] - 30.0;
	  g[7] = -3.0 * x[0] + 6.0 * x[1] + 12.0 * (x[8] - 8.0) * (x[8] - 8.0) - 7.0 * x[9];
	}

	void Function_G::g08 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{

	  double pi = 4.0 * atan (1.0);

	/* objective function */
	  f[0] = pow (sin (2 * pi * x[0]), 3) * sin (2 * pi * x[1]) / (pow (x[0], 3) * (x[0] + x[1]));
	  f[0] = -f[0]; /* Max-->Min, Modified by Jane,Nov 22 2005 */
	/* constraints */
	  g[0] = x[0] * x[0] - x[1] + 1.0;
	  g[1] = 1.0 - x[0] + (x[1] - 4.0) * (x[1] - 4.0);
	}

	void Function_G::g09 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] =
		(x[0] - 10.0) * (x[0] - 10.0) + 5.0 * (x[1] - 12.0) * (x[1] - 12.0) + pow (x[2],
											   4) + 3.0 * (x[3] - 11.0) * (x[3] -
														   11.0) +
		10.0 * pow (x[4], 6) + 7.0 * x[5] * x[5] + pow (x[6], 4) - 4.0 * x[5] * x[6] - 10.0 * x[5] - 8.0 * x[6];
	  /* constraints g<=0 */
	  g[0] = -127.0 + 2 * x[0] * x[0] + 3.0 * pow (x[1], 4) + x[2] + 4.0 * x[3] * x[3] + 5.0 * x[4];
	  g[1] = -282.0 + 7.0 * x[0] + 3.0 * x[1] + 10.0 * x[2] * x[2] + x[3] - x[4];
	  g[2] = -196.0 + 23.0 * x[0] + x[1] * x[1] + 6.0 * x[5] * x[5] - 8.0 * x[6];
	  g[3] = 4.0 * x[0] * x[0] + x[1] * x[1] - 3.0 * x[0] * x[1] + 2.0 * x[2] * x[2] + 5.0 * x[5] - 11.0 * x[6];
	}

	void Function_G::g10 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = x[0] + x[1] + x[2];
	  /* constraints g<=0 */
	  g[0] = -1.0 + 0.0025 * (x[3] + x[5]);
	  g[1] = -1.0 + 0.0025 * (x[4] + x[6] - x[3]);
	  g[2] = -1.0 + 0.01 * (x[7] - x[4]);
	  g[3] = -x[0] * x[5] + 833.33252 * x[3] + 100.0 * x[0] - 83333.333;
	  g[4] = -x[1] * x[6] + 1250.0 * x[4] + x[1] * x[3] - 1250.0 * x[3];
	  g[5] = -x[2] * x[7] + 1250000.0 + x[2] * x[4] - 2500.0 * x[4];
	}

	void Function_G::g11 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = x[0] * x[0] + (x[1] - 1.0) * (x[1] - 1.0);
	  /* constraints g<=0 */
	  h[0] = x[1] - x[0] * x[0];
	}

	void Function_G::g12 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  double gt;
	  int i, j, k;

	/* objective function */
	  f[0] = (100. - (x[0] - 5.) * (x[0] - 5.) - (x[1] - 5.) * (x[1] - 5.) - (x[2] - 5.) * (x[2] - 5.)) / 100.;
	  f[0] = -f[0]; /* Max-->Min, Modified by Jane,Nov 22 2005 */
	/* constraints */
	  g[0] = (x[0] - 1.) * (x[0] - 1.) + (x[1] - 1.) * (x[1] - 1.) + (x[2] - 1.) * (x[2] - 1.) - 0.0625;
	  for (i = 1; i <= 9; i++)
		{
		  for (j = 1; j <= 9; j++)
		{
		  for (k = 1; k <= 9; k++)
			{
			  gt = (x[0] - i) * (x[0] - i) + (x[1] - j) * (x[1] - j) + (x[2] - k) * (x[2] - k) - 0.0625;
			  if (gt < g[0])
			g[0] = gt;
			}
		}
		}
	}

	void Function_G::g13 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = exp (x[0] * x[1] * x[2] * x[3] * x[4]);
	  /* constraints h(x) = 0 */
	  h[0] = x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3] + x[4] * x[4] - 10.0;
	  h[1] = x[1] * x[2] - 5.0 * x[3] * x[4];
	  h[2] = pow (x[0], 3) + pow (x[1], 3) + 1.0;
	}

	void Function_G::g14 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  int i;
	  double sumlog = 0.0, sum = 0.0;
	  double C[10] = { -6.089, -17.164, -34.054, -5.914, -24.721, -14.986, -24.100, -10.708, -26.662, -22.179 };

	  /* objective function */
	  for (i = 0; i < 10; i++)
		sumlog += x[i];
	  for (i = 0; i < 10; i++)
		sum += x[i] * (C[i] + log (x[i] / sumlog));
	  f[0] = sum;
	  /* constraints h=0 */
	  h[0] = x[0] + 2.0 * x[1] + 2.0 * x[2] + x[5] + x[9] - 2.0;
	  h[1] = x[3] + 2.0 * x[4] + x[5] + x[6] - 1.0;
	  h[2] = x[2] + x[6] + x[7] + 2.0 * x[8] + x[9] - 1.0;
	}

	void Function_G::g15 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = 1000.0 - pow (x[0], 2.0) - 2.0 * x[1] * x[1] - x[2] * x[2] - x[0] * x[1] - x[0] * x[2];
	  /* constraints h=0 */
	  h[0] = pow (x[0], 2.0) + pow (x[1], 2.0) + pow (x[2], 2.0) - 25.0;
	  h[1] = 8.0 * x[0] + 14.0 * x[1] + 7.0 * x[2] - 56.0; /* BUG FIXED was 8.0 * x[1] */
	}

	void Function_G::g16 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  double x1, x2, x3, x4, x5;
	  double C[17], Y[17];

	  x1 = x[0];
	  x2 = x[1];
	  x3 = x[2];
	  x4 = x[3];
	  x5 = x[4];

	  Y[0] = x2 + x3 + 41.6;
	  C[0] = 0.024 * x4 - 4.62;
	  Y[1] = (12.5 / C[0]) + 12.0;
	  C[1] = 0.0003535 * pow (x1, 2.0) + 0.5311 * x1 + 0.08705 * Y[1] * x1;
	  C[2] = 0.052 * x1 + 78.0 + 0.002377 * Y[1] * x1;
	  Y[2] = C[1] / C[2];
	  Y[3] = 19.0 * Y[2];
	  C[3] = 0.04782 * (x1 - Y[2]) + ((0.1956 * pow (x1 - Y[2], 2.0)) / x2) + 0.6376 * Y[3] + 1.594 * Y[2];
	  C[4] = 100 * x2;
	  C[5] = x1 - Y[2] - Y[3];
	  C[6] = 0.950 - (C[3] / C[4]);
	  Y[4] = C[5] * C[6];
	  Y[5] = x1 - Y[4] - Y[3] - Y[2];
	  C[7] = (Y[4] + Y[3]) * 0.995;
	  Y[6] = C[7] / Y[0];
	  Y[7] = C[7] / 3798.0;
	  C[8] = Y[6] - (0.0663 * Y[6] / Y[7]) - 0.3153;
	  Y[8] = (96.82 / C[8]) + 0.321 * Y[0];
	  Y[9] = 1.29 * Y[4] + 1.258 * Y[3] + 2.29 * Y[2] + 1.71 * Y[5];
	  Y[10] = 1.71 * x1 - 0.452 * Y[3] + 0.580 * Y[2];
	  C[9] = 12.3 / 752.3;
	  C[10] = 1.75 * Y[1] * 0.995 * x1;
	  C[11] = 0.995 * Y[9] + 1998.0;
	  Y[11] = C[9] * x1 + (C[10] / C[11]);
	  Y[12] = C[11] - 1.75 * Y[1];
	  Y[13] = 3623.0 + 64.4 * x2 + 58.4 * x3 + (146312.0 / (Y[8] + x5));
	  C[12] = 0.995 * Y[9] + 60.8 * x2 + 48 * x4 - 0.1121 * Y[13] - 5095.0;
	  Y[14] = Y[12] / C[12];
	  Y[15] = 148000.0 - 331000.0 * Y[14] + 40.0 * Y[12] - 61.0 * Y[14] * Y[12];
	  C[13] = 2324 * Y[9] - 28740000 * Y[1];
	  Y[16] = 14130000 - 1328.0 * Y[9] - 531.0 * Y[10] + (C[13] / C[11]);
	  C[14] = (Y[12] / Y[14]) - (Y[12] / 0.52);
	  C[15] = 1.104 - 0.72 * Y[14];
	  C[16] = Y[8] + x5;

	  /* objective function */
	  f[0] = 0.0000005843 * Y[16] - 0.000117 * Y[13] - 0.1365 - 0.00002358 * Y[12] - 0.000001502 * Y[15] - 0.0321 * Y[11] - 0.004324 * Y[4] - 0.0001 * (C[14] / C[15]) - 37.48 * (Y[1] / C[11]);
	  f[0] = -f[0]; /* Max-->Min, Modified by Jane,Nov 22 2005 */
	  /* constraints g(x) <= 0 */
	  g[0] = -Y[3] + (0.28 / 0.72) * Y[4];
	  g[1] = -1.5 * x2 + x3;
	  g[2] = -21.0 + 3496.0 * (Y[1] / C[11]);
	  g[3] = -(62212.0 / C[16]) + 110.6 + Y[0];
	  g[4] = 213.1 - Y[0];
	  g[5] = Y[0] - 405.23;
	  g[6] = 17.505 - Y[1];
	  g[7] = Y[1] - 1053.6667;
	  g[8] = 11.275 - Y[2];
	  g[9] = Y[2] - 35.03;
	  g[10] = 214.228 - Y[3];
	  g[11] = Y[3] - 665.585;
	  g[12] = 7.458 - Y[4];
	  g[13] = Y[4] - 584.463;
	  g[14] = 0.961 - Y[5];
	  g[15] = Y[5] - 265.916;
	  g[16] = 1.612 - Y[6];
	  g[17] = Y[6] - 7.046;
	  g[18] = 0.146 - Y[7];
	  g[19] = Y[7] - 0.222;
	  g[20] = 107.99 - Y[8];
	  g[21] = Y[8] - 273.366;
	  g[22] = 922.693 - Y[9];
	  g[23] = Y[9] - 1286.105;
	  g[24] = 926.832 - Y[10];
	  g[25] = Y[10] - 1444.046;
	  g[26] = 18.766 - Y[11];
	  g[27] = Y[11] - 537.141;
	  g[28] = 1072.163 - Y[12];
	  g[29] = Y[12] - 3247.039;
	  g[30] = 8961.448 - Y[13];
	  g[31] = Y[13] - 26844.086;
	  g[32] = 0.063 - Y[14];
	  g[33] = Y[14] - 0.386;
	  g[34] = 71084.33 - Y[15];
	  g[35] = Y[15] - 140000.0;
	  g[36] = 2802713.0 - Y[16];
	  g[37] = Y[16] - 12146108.0;
	}

	void Function_G::g17 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  double f1, f2, x1, x2, x3, x4, x5, x6;
	  double aux1, aux2, aux5, aux4;

	  x1 = x[0];
	  x2 = x[1];
	  x3 = x[2];
	  x4 = x[3];
	  x5 = x[4];
	  x6 = x[5];

	  aux1 = 300.0 - (((x3 * x4) * cos (1.48477 - x6)) - ((0.90798 * pow (x3, 2.0)) * cos (1.47588))) / 131.078;
	  aux2 = -(((x3 * x4)  * cos (1.48477 + x6)) - ((0.90798 * pow (x4, 2.0))  * cos (1.47588)))/ 131.078;
	  aux5 = -(((x3 * x4)  * sin (1.48477 + x6)) - ((0.90798 * pow (x4, 2.0))  * sin (1.47588)))/ 131.078;
	  aux4 = 200.0 - (((x3 * x4)  * sin (1.48477 - x6)) - ((0.90798 * pow (x3, 2.0))  * sin (1.47588)))/ 131.078;


	  /* objective fucntion */
	  if (x1 >= 0.0 && x1 < 300.0)
		{
		  f1 = 30.0 * aux1;
		}
	  else
		{
		  if (x1 >= 300.0 && x1 <= 400.0)
		{
		  f1 = 31.0 * aux1;
		}
		}
	  if (x2 >= 0.0 && x2 < 100.0)
		{
		  f2 = 28.0 * aux2;
		}
	  else
		{
		  if (x2 >= 100.0 && x2 < 200.0)
		{
		  f2 = 29.0 * aux2;
		}
		  else
		{
		  if (x2 >= 200.0 && x2 <= 1000.0)
			{
			  f2 = 30.0 * aux2;
			}
		}
		}
	  f[0] = f1 + f2;

	  /* constraint function h = 0 */
	  h[0] = aux1 - x1;
	  h[1] = aux2 - x2;
	  h[2] = aux5 - x5;
	  h[3] = aux4;
	}

	void Function_G::g18 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = 0.5 * (x[0] * x[3] - x[1] * x[2] + x[2] * x[8] - x[4] * x[8] + x[4] * x[7] - x[5] * x[6]);
	  f[0] = -f[0]; /* Max-->Min, Modified by Jane,Nov 22 2005 */
	  /* constraint function g <= 0 */
	  g[0] = -1.0 + pow (x[2], 2.0) + pow (x[3], 2.0);
	  g[1] = -1.0 + pow (x[8], 2.0);
	  g[2] = -1.0 + pow (x[4], 2.0) + pow (x[5], 2.0);
	  g[3] = -1.0 + pow (x[0], 2.0) + pow (x[1] - x[8], 2.0);
	  g[4] = -1.0 + pow (x[0] - x[4], 2.0) + pow (x[1] - x[5], 2.0);
	  g[5] = -1.0 + pow (x[0] - x[6], 2.0) + pow (x[1] - x[7], 2.0);
	  g[6] = -1.0 + pow (x[2] - x[4], 2.0) + pow (x[3] - x[5], 2.0);
	  g[7] = -1.0 + pow (x[2] - x[6], 2.0) + pow (x[3] - x[7], 2.0);
	  g[8] = -1.0 + pow (x[6], 2.0) + pow (x[7] - x[8], 2.0);/* bug fixed by Jane,Nov 25 2005 */
	  g[9] = -x[0] * x[3] + x[1] * x[2];
	  g[10] = -x[2] * x[8];
	  g[11] = x[4] * x[8];
	  g[12] = -x[4] * x[7] + x[5] * x[6];
	}

	void Function_G::g19 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  int i, j;
	  double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
	  double A[10][5] = {
			  	  {-16.0,  2.0,  0.0,  1.0,  0.0},
				  {  0.0, -2.0,  0.0,  0.4,  2.0},
				  { -3.5,  0.0,  2.0,  0.0,  0.0},
				  {  0.0, -2.0,  0.0, -4.0, -1.0},
				  {  0.0, -9.0, -2.0,  1.0, -2.8},
				  {  2.0,  0.0, -4.0,  0.0,  0.0},
				  { -1.0, -1.0, -1.0, -1.0, -1.0},
				  { -1.0, -2.0, -3.0, -2.0, -1.0},
				  {  1.0,  2.0,  3.0,  4.0,  5.0},
				  {  1.0,  1.0,  1.0,  1.0,  1.0}
	  };
	  double B[10] = { -40.0, -2.0, -0.25, -4.0, -4.0, -1.0, -40.0, -60.0, 5.0, 1.0 };
	  double C[5][5] = {
			  	  { 30.0, -20.0, -10.0,  32.0, -10.0},
				  {-20.0,  39.0,  -6.0, -31.0,  32.0},
				  {-10.0,  -6.0,  10.0,  -6.0, -10.0},
				  { 32.0, -31.0,  -6.0,  39.0, -20.0},
				  {-10.0,  32.0, -10.0, -20.0,  30.0}
	  };
	  double D[5] = { 4.0, 8.0, 10.0, 6.0, 2.0 };
	  double E[5] = { -15.0, -27.0, -36.0, -18.0, -12.0 };

	  /* objective function */
	  for (i = 0; i < 10; i++)
		{
		  sum1 += B[i] * x[i];
		}
	  for (i = 0; i < 5; i++)
		{
		  for (j = 0; j < 5; j++)
		{
		  sum2 += C[i][j] * x[10 + i] * x[10 + j];
		}
		}
	  for (i = 0; i < 5; i++)
		{
		  sum3 += D[i] * pow (x[10 + i], 3.0);
		}
	  f[0] = sum1 - sum2 - 2.0 * sum3;
	  f[0] = -f[0]; /* Max-->Min, Modified by Jane,Nov 22 2005 */
	  /* constraints g <= 0 */
	  for (j = 0; j < 5; j++)
		{
		  sum1 = 0.0;
		  for (i = 0; i < 5; i++)
		sum1 += C[i][j] * x[10 + i];
		  sum2 = 0.0;
		  for (i = 0; i < 10; i++)
		sum2 += A[i][j] * x[i];
		  g[j] = -((2.0 * sum1) + (3.0 * D[j] * pow (x[10 + j], 2.0)) + E[j] - sum2);
		}
	}

	void Function_G::g20 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  double sum1, sum2, sumtotal;
	  int i, j;
	  double A[24] = { 0.0693, 0.0577, 0.05, 0.2, 0.26, 0.55, 0.06, 0.1, 0.12, 0.18, 0.1, 0.09, 0.0693, 0.0577, 0.05, 0.2, 0.26, 0.55, 0.06, 0.1, 0.12, 0.18, 0.1, 0.09 };
	  double B[24] = { 44.094, 58.12, 58.12, 137.4, 120.9, 170.9, 62.501, 84.94, 133.425, 82.507, 46.07, 60.097, 44.094, 58.12, 58.12, 137.4, 120.9, 170.9, 62.501, 84.94, 133.425, 82.507, 46.07, 60.097 };
	  double C[12] = { 123.7, 31.7, 45.7, 14.7, 84.7, 27.7, 49.7, 7.1, 2.1, 17.7, 0.85, 0.64 };
	  double D[12] = { 31.244, 36.12, 34.784, 92.7, 82.7, 91.6, 56.708, 82.7, 80.8, 64.517, 49.4, 49.1 };
	  double E[6] = { 0.1, 0.3, 0.4, 0.3, 0.6, 0.3 };

	  /* objective function */
	  f[0] = 0.0;
	  for (j = 0; j < 24; j++)
		{
		  f[0] += A[j] * x[j];
		}
	  /* constraints h(x) = 0 and g(x) <= 0 */
	  sum1 = 0.0;
	  for (j = 0; j < 12; j++)
		sum1 += x[j] / B[j];
	  sum2 = 0.0;
	  for (j = 12; j < 24; j++)
		sum2 += x[j] / B[j];
	  for (i = 0; i < 12; i++)
		h[i] = (x[i + 12] / (B[i + 12] * sum2)) - ((C[i] * x[i]) / (40.0 * B[i] * sum1));
	  sumtotal = 0.0;
	  for (j = 0; j < 24; j++)
		sumtotal += x[j];
	  h[12] = sumtotal - 1.0;
	  sum1 = 0.0;
	  for (j = 0; j < 12; j++)
		sum1 += x[j] / D[j];
	  sum2 = 0.0;
	  for (j = 12; j < 24; j++)
		sum2 += x[j] / B[j];
	  h[13] = sum1 + (0.7302 * 530.0 * (14.7 / 40)) * sum2 - 1.671;
	  for (j = 0; j < 3; j++)
		g[j] = (x[j] + x[j + 12]) / (sumtotal + E[j]);
	  for (j = 3; j < 6; j++)
		g[j] = (x[j + 3] + x[j + 15]) / (sumtotal + E[j]);
	}

	void Function_G::g21 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{


	  /* objective function */
	  f[0] = x[0];
	  /* constraint functions h(x) and g(x) <= 0 */
	  g[0] = -x[0] + 35.0 * pow (x[1], 0.6) + 35.0 * pow (x[2], 0.6);
	  h[0] = -300.0 * x[2] + 7500 * x[4] - 7500 * x[5] - 25.0 * x[3] * x[4] + 25.0 * x[3] * x[5] + x[2] * x[3];
	  h[1] = 100.0 * x[1] + 155.365 * x[3] + 2500 * x[6] - x[1] * x[3] - 25.0 * x[3] * x[6] - 15536.5;
	  h[2] = -x[4] + log (-x[3] + 900.0);
	  h[3] = -x[5] + log (x[3] + 300.0);
	  h[4] = -x[6] + log (-2.0 * x[3] + 700.0);
	}

	void Function_G::g22 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{

	  /* objective function */
	  f[0] = x[0];
	  /* constraint functions */
	  g[0] = -x[0] + pow (x[1], 0.6) + pow (x[2], 0.6) + pow (x[3], 0.6);
	  h[0] = x[4] - 100000.0 * x[7] + 10000000.0;
	  h[1] = x[5] + 100000.0 * x[7] - 100000.0 * x[8];
	  h[2] = x[6] + 100000.0 * x[8] - 50000000.0;
	  h[3] = x[4] + 100000.0 * x[9] - 33000000.0;
	  h[4] = x[5] + 100000 * x[10] - 44000000.0;
	  h[5] = x[6] + 100000 * x[11] - 66000000.0;
	  h[6] = x[4] - 120.0 * x[1] * x[12];
	  h[7] = x[5] - 80.0 * x[2] * x[13];
	  h[8] = x[6] - 40.0 * x[3] * x[14];
	  h[9] = x[7] - x[10] + x[15];
	  h[10] = x[8] - x[11] + x[16];
	  h[11] = -x[17] + log (x[9] - 100.0);/*bug fixed by Jane,Nov 25 2005*/
	  h[12] = -x[18] + log (-x[7] + 300.0);
	  h[13] = -x[19] + log (x[15]);
	  h[14] = -x[20] + log (-x[8] + 400.0);
	  h[15] = -x[21] + log (x[16]);
	  h[16] = -x[7] - x[9] + x[12] * x[17] - x[12] * x[18] + 400.0;
	  h[17] = x[7] - x[8] - x[10] + x[13] * x[19] - x[13] * x[20] + 400.0;
	  h[18] = x[8] - x[11] - 4.60517 * x[14] + x[14] * x[21] + 100.0;
	}

	void Function_G::g23 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{

	  /* objective function */
	  f[0] = -9.0 * x[4] - 15.0 * x[7] + 6.0 * x[0] + 16.0 * x[1] + 10.0 * (x[5] + x[6]);
	  /* constraint function */
	  g[0] = x[8] * x[2] + 0.02 * x[5] - 0.025 * x[4];
	  g[1] = x[8] * x[3] + 0.02 * x[6] - 0.015 * x[7];
	  h[0] = x[0] + x[1] - x[2] - x[3];
	  h[1] = 0.03 * x[0] + 0.01 * x[1] - x[8] * (x[2] + x[3]);
	  h[2] = x[2] + x[5] - x[4];
	  h[3] = x[3] + x[6] - x[7];
	}

	void Function_G::g24 (double *x, double *f, double *g, double *h, int nx, int nf, int ng, int nh)
	{
	  /* objective function */
	  f[0] = -x[0] - x[1];
	  /* constraint function */
	  g[0] = -2.0 * pow (x[0], 4.0) + 8.0 * pow (x[0], 3.0) - 8.0 * pow (x[0], 2.0) + x[1] - 2.0;
	  g[1] = -4.0 * pow (x[0], 4.0) + 32.0 * pow (x[0], 3.0) - 88.0 * pow (x[0], 2.0) + 96.0 * x[0] + x[1] - 36.0;
	}




} /* namespace function */
} /* namespace opt */
