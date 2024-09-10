/*
 * Algorithm.h
 *
 *  Created on: 09/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "float.h"

#include "../base/Tools.h"
#include "../base/Individual.h"
#include "../evaluate/Evaluate.h"
#include "../base/Input.h"
#include "../operator/Operator.h"
#include "../operator/Manager_Operator.h"

#include "../operator/Operator_MT_DE_Best.h"
#include "../operator/Operator_MT_DE_Current_Rand.h"
#include "../operator/Operator_MT_DE_Rand2.h"
#include "../operator/Operator_MT_DE_Rand.h"
#include "../operator/Operator_MT_DE_Rand_Best.h"
#include "../operator/Operator_MT_DE_Current_Best.h"
#include "../operator/Operator_MT_Delta.h"
#include "../operator/Operator_MT_NonUniform.h"
#include "../operator/Operator_MT_Rand.h"
#include "../operator/Operator_CX_1X.h"
#include "../operator/Operator_CX_BLXa.h"
#include "../operator/Operator_CX_SBX.h"
#include "../operator/Operator_CX_Uniform.h"

using namespace opt::base;
using namespace opt::evaluate;
using namespace opt::operators;

namespace opt {
namespace algorithm{

	class Algorithm {
		protected:
			vector<IndividualPtr> pop;
			Evaluate *eval;
			Function *function;

			int popSize;
			int maxGen;
			int dimensions;
		public:
			Algorithm(){}
			Algorithm(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			Algorithm(Evaluate *pEval);

			virtual void createPop();
			virtual void runAll();
			virtual void run_generate(vector<IndividualPtr> &pop);
			virtual void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);

			virtual void addOperatorsByInput(Manager_Operator *manager, string type = "ALL");

			virtual void reset();

			virtual ~Algorithm();
	};

} /* namespace operators */
} /* namespace opt */
#endif /* ALGORITHM_H_ */
