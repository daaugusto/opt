/*
 * Algorithm_HybridOp_AOS.h
 *
 *  Created on: 24/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_HYBRIDOP_AOS_H_
#define ALGORITHM_HYBRIDOP_AOS_H_

#include "../base/Tools.h"
#include "Algorithm_Hybrid_AOS.h"
using namespace opt::base;

namespace opt {
namespace hybridAos {

	class Algorithm_HybridOp_AOS : public Algorithm_Hybrid_AOS{
		public:
			Algorithm_HybridOp_AOS(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0):Algorithm_Hybrid_AOS(pMaxGen, pPopSize, pEval, seed){}
			Algorithm_HybridOp_AOS(Evaluate *pEval):Algorithm_Hybrid_AOS(pEval){}
			virtual void run_generate(vector<IndividualPtr> &pop);
	};

} /* namespace hybridAos */
} /* namespace opt */
#endif /* ALGORITHM_HYBRIDOP_AOS_H_ */
