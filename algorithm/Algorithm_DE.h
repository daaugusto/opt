/*
 * Algorithm_DE.h
 *
 *  Created on: 10/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_DE_H_
#define ALGORITHM_DE_H_

#include "Algorithm.h"
#include "../base/Individual.h"
#include "../base/Tools.h"
#include "../operator/Operator.h"
#include "../operator/Operator_MT_DE_Best.h"
#include "../operator/Operator_MT_DE_Current_Rand.h"
#include "../operator/Operator_MT_DE_Rand2.h"
#include "../operator/Operator_MT_DE_Rand.h"
#include "../operator/Operator_MT_DE_Rand_Best.h"
#include "../operator/Manager_Operator.h"
using namespace opt::base;
using namespace opt::operators;



namespace opt {
namespace algorithm{

	class Algorithm_DE : public Algorithm{
		protected:
			int iBest;
			Manager_Operator *manager_op_mt;
		public:
			Algorithm_DE(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			Algorithm_DE(Evaluate *pEval);
			virtual ~Algorithm_DE( );
			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			void run_generate(vector<IndividualPtr> &pop);
			void runAll();
	};

} /* namespace algorithm */
} /* namespace opt */
#endif /* ALGORITHM_DE_H_ */
