/*
 * SMDE.h
 *
 *  Created on: 17/04/2012
 *      Author: krempser
 */

#ifndef SMDE_H_
#define SMDE_H_

#include <string>
#include <sstream>

#include "../base/Individual.h"
#include "../algorithm/Algorithm_DE.h"
#include "../surrogate/Evaluate_Surrogate.h"
using namespace opt::base;
using namespace opt::algorithm;
using namespace opt::surrogate;


namespace opt {
namespace smde {

	class Algorithm_SMDE : public Algorithm_DE{
		protected:
			int nApp;
			Evaluate_Surrogate *evalSurrogate;
			int countErrors;
			int goodChoice;
		public:
			Algorithm_SMDE(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed);

			Algorithm_SMDE(Evaluate *pEval, Evaluate_Surrogate *pEvalSur);


			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed);

			//Run all DE
			void runAll();

			virtual void run_generate(vector<IndividualPtr> &pop);

			virtual ~Algorithm_SMDE();

			//Create the generation information to print parcial results
			virtual void createExtraHeaderInfo(ostringstream &extra);
			virtual void createExtraGenerationInfo(ostringstream &extra, int iBest_);
	};

} /* namespace smde */
} /* namespace opt */
#endif /* SMDE_H_ */
