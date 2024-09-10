/*
 * BLDE.h
 *
 *  Created on: 13/03/2019
 *      Author: Eduardo Krempser
 */

#ifndef BLDE_H_
#define BLDE_H_

#include <string>
#include <sstream>

#include "../base/Individual.h"
#include "../algorithm/Algorithm_DE.h"
#include "../blde/Algorithm_BLDE_Follower.h"
#include "../surrogate/Evaluate_Surrogate.h"
#include "../evaluate/Evaluate_BLDE.h"
using namespace opt::base;
using namespace opt::algorithm;
using namespace opt::surrogate;
using namespace opt::evaluate;


namespace opt {
namespace blde {

	class Algorithm_BLDE : public Algorithm_DE{
		protected:
			int nApp, nAppF;
			Evaluate_Surrogate *evalSurrogate;
			int countErrors;
			int goodChoice;

			//Follower variables - the leader variables are default -> declared in Algorithm.h
			vector<IndividualPtr> popFollower; //Follower population
			Evaluate *evalFollower;  //Evaluate the follower population
			int dimensionsFollower;

			string smp;
			int realEvals; //Number of real evalutations
		public:
			Algorithm_BLDE(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed);

			Algorithm_BLDE(Evaluate *pEval, Evaluate_Surrogate *pEvalSur);


			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, int seed);

			//Run all DE
			void runAll();

			virtual void run_generate(vector<IndividualPtr> &pop, vector<IndividualPtr> &popFollower);

			virtual ~Algorithm_BLDE();

			//Create the generation information to print parcial results
			virtual void createExtraHeaderInfo(ostringstream &extra);
			virtual void createExtraGenerationInfo(ostringstream &extra, int iBest_);

			//Bilevel functions
			virtual void createPopFollower(); //create follower population

			virtual double extractFitnessFollower(int iBest);
	};

} /* namespace blde */
} /* namespace opt */
#endif /* SMDE_H_ */
