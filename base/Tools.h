/*
 * Tools.h
 *
 *  Created on: 03/02/2012
 *      Author: Eduardo Krempser
 */
#ifndef TOOLS_H_
#define TOOLS_H_

#include "stdlib.h"
#include "time.h"
#include <sys/time.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include "Individual.h"
#include "../evaluate/Evaluate.h"
#include "../function/Function.h"
#include "../function/Function_SMD.h"
using namespace opt::evaluate;
using namespace opt::function;

namespace opt{
	namespace base {

		class Tools {
			public:
				static void generateSeed(int s = -1);
				static double newRand(double min, double max);
				static double treatBasicBounds(double &x, int index);
				static double initializeGene(int index);
				static double convertToRealRange(int index, double val);
				static int getBest(vector<IndividualPtr> &pop, Evaluate *eval);
				static int getBestFeasible(vector<IndividualPtr> &pop, Evaluate *eval);
				static int getWorst(vector<IndividualPtr> &pop, Evaluate *eval);
				static void order(vector<IndividualPtr> &pop, Evaluate *eval);
				//order by parameter
				static void order(vector<IndividualPtr> &pop, Evaluate *eval, string Param);

				static void printPopulation(vector<IndividualPtr> pop, Evaluate *eval, bool showConst);
				static void printGenerationInfo(int G, vector<IndividualPtr> pop, int iBest, Evaluate *eval, string extra = "", bool showConst = true);
				static void printHeaderInfo(vector<IndividualPtr> pop, string extra = "", bool showConst = true);

				static string printIndividual(IndividualPtr ind, Evaluate *eval, bool showConst = true);
				static string printIndividualSimple(IndividualPtr ind, Evaluate *eval, bool showConst = true);

				static bool isEndProcess(Evaluate *eval, double bestFit);

				static double getTime();

				static void calcVariance(vector<IndividualPtr> pop, int dim, vector<double> &var);
		};

	} /* namespace base */
}
#endif /* TOOLS_H_ */
