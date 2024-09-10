/*
 * Algorithm_Hybrid_AOS.h
 *
 *  Created on: 16/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_HYBRID_AOS_H_
#define ALGORITHM_HYBRID_AOS_H_

#include "../algorithm/Algorithm.h"
#include "Algorithm_DE_AOS.h"
#include "Algorithm_GA_AOS.h"
#include "../aos/AOS.h"
#include "../base/Tools.h"
using namespace opt::algorithm;
using namespace opt::aos;
using namespace opt::base;

namespace opt {
namespace hybridAos {

class Algorithm_Hybrid_AOS : public Algorithm {
		protected:
			AOS *aos;
			int iBest;
			double avgFitness;

			Algorithm_DE_AOS *de;
			Algorithm_GA_AOS *ga;

			int nDE, nGA;
		public:
			Algorithm_Hybrid_AOS(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			Algorithm_Hybrid_AOS(Evaluate *pEval);
			virtual void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			virtual void run_generate(vector<IndividualPtr> &pop);
			virtual void runAll();

			virtual void reset();
};

} /* namespace hybridAos */
} /* namespace opt */
#endif /* ALGORITHM_HYBRID_AOS_H_ */
