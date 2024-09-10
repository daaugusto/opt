/*
 * BLDE_Follower_Follower.h
 *
 *  Created on: 13/03/2019
 *      Author: Eduardo Krempser
 */

#ifndef BLDE_FOLLOWER_H_
#define BLDE_FOLLOWER_H_

#include <string>
#include <sstream>

#include "../base/Individual.h"
#include "../algorithm/Algorithm_DE.h"
#include "../surrogate/Evaluate_Surrogate.h"
#include "../evaluate/Evaluate_BLDE.h"
using namespace opt::base;
using namespace opt::algorithm;
using namespace opt::surrogate;


namespace opt {
namespace blde {

	class Algorithm_BLDE_Follower : public Algorithm_DE{
		protected:
			int nApp;
			Evaluate_Surrogate *evalSurrogate;
			int countErrors;
			int goodChoice;

			int dimensionsFollower;
			IndividualPtr indLeader;
		public:
			Algorithm_BLDE_Follower(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed, int dimFollower, IndividualPtr indLeader);

			Algorithm_BLDE_Follower(Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int dimFollower, IndividualPtr indLeader);


			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed, int dimFollower, IndividualPtr pIndLeader);

			//Run all DE
			void runAll();

			virtual void run_generate(vector<IndividualPtr> &pop);

			virtual ~Algorithm_BLDE_Follower();

			//Create the generation information to print parcial results
			virtual void createExtraHeaderInfo(ostringstream &extra);
			virtual void createExtraGenerationInfo(ostringstream &extra, int iBest_);

			virtual void createPop();
			virtual IndividualPtr getBest();

	};

} /* namespace blde */
} /* namespace opt */
#endif /* SMDE_H_ */
