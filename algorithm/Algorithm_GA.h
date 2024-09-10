/*
 * Algorithm_GA.h
 *
 *  Created on: 10/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_GA_H_
#define ALGORITHM_GA_H_

#include "Algorithm.h"
#include "../base/Individual.h"
#include "../base/Tools.h"
#include "../operator/Operator.h"
#include "../operator/Operator_MT_Delta.h"
#include "../operator/Operator_MT_NonUniform.h"
#include "../operator/Operator_MT_Rand.h"
#include "../operator/Operator_CX_1X.h"
#include "../operator/Operator_CX_BLXa.h"
#include "../operator/Operator_CX_SBX.h"
#include "../operator/Operator_CX_Uniform.h"
#include "../operator/Manager_Operator.h"
using namespace opt::base;
using namespace opt::operators;

namespace opt {
namespace algorithm {

	class Algorithm_GA : public Algorithm{
		protected:
			Manager_Operator *manager_op_cx;
			Manager_Operator *manager_op_mt;
		public:
			Algorithm_GA(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			Algorithm_GA(Evaluate *pEval);
			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			void runAll();
			void run_generate(vector<IndividualPtr> &pop);
			virtual ~Algorithm_GA(){};
	};

} /* namespace operators */
} /* namespace opt */
#endif /* ALGORITHM_GA_H_ */
