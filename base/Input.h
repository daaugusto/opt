/*
 * Input.h
 *
 *  Created on: 03/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "stdlib.h"
#include "string.h"
using namespace std;

#include "../function/Function.h"
using namespace opt::function;


namespace opt{
	namespace base {

	class Input {
		public:
			static Function *function;
			static bool normalized;

			//Public configuration values
			static int idFunction;
			static int hybrid, show;
			static int dim, idTest, run;
			static int gen, currentIndividual, seedValue, popSize, maxGen;
			static double pDE, pGA, c, cDE, cGA;
			static string algorithm, tEval, sm, smp, sel;
			static int nap;
			static double F;
			static string sl;

			//for bilevel problems
			static int level; 
			static int popSizeF, maxGenF;
			static int napF;
			static int recalc;

			//Operators
			static vector<int> opDE;
			static vector<int> opGA;

			//AOS parameters
			static int aos;
			static int aos_de, aos_ga;
			static double aos_p_min, aos_alpha, aos_beta, aos_v_scaling, aos_v_gamma, aos_decay;
			static int aos_W, aos_delta_fitness, aos_type, aos_norm;
			static double aos_de_p_min, aos_de_alpha, aos_de_beta, aos_de_v_scaling, aos_de_v_gamma, aos_de_decay;
			static int aos_de_W, aos_de_delta_fitness, aos_de_type, aos_de_norm;
			static double aos_ga_p_min, aos_ga_alpha, aos_ga_beta, aos_ga_v_scaling, aos_ga_v_gamma, aos_ga_decay;
			static int aos_ga_W, aos_ga_delta_fitness, aos_ga_type, aos_ga_norm;

			//BBOB parameters
			static string path, algname;

			//Methods
			static void setParams(int argc, char *argv[]);
			static string help();
	};

	} /* namespace base */
}
#endif /* INPUT_H_ */
