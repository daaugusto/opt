/*
 * Algorithm_SMDE_aKnn.h
 *
 *  Created on: 04/05/2012
 *      Author: krempser
 */

#ifndef ALGORITHM_SMDE_AKNN_H_
#define ALGORITHM_SMDE_AKNN_H_

#include "Algorithm_SMDE.h"

using namespace opt::base;
using namespace opt::algorithm;
using namespace opt::surrogate;


namespace opt {
namespace smde {

	class Algorithm_SMDE_aKnn : public Algorithm_SMDE{
		public:
		Algorithm_SMDE_aKnn(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed);
		Algorithm_SMDE_aKnn(Evaluate *pEval, Evaluate_Surrogate *pEvalSur);
		void run_generate(vector<IndividualPtr> &pop);

		//Create the generation information to print parcial results
		void createExtraHeaderInfo(ostringstream &extra);
		void createExtraGenerationInfo(ostringstream &extra);
	};

} /* namespace function */
} /* namespace opt */
#endif /* ALGORITHM_SMDE_AKNN_H_ */
