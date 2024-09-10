/*
 * Algorithm_ESMDE.h
 *
 *  Created on: 23/07/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_ESMDE_H_
#define ALGORITHM_ESMDE_H_


#include <string>
#include <sstream>

#include "../base/Individual.h"
#include "../smde/Algorithm_SMDE.h"
#include "../surrogate/Evaluate_Surrogate.h"
#include "../surrogate/Manager_Surrogate.h"
#include "../surrogate/Evaluate_Surrogate_NN.h"
#include "../surrogate/Evaluate_Surrogate_LLR.h"
#include "../surrogate/Evaluate_Surrogate_LWR.h"
#include "../surrogate/Evaluate_Surrogate_RBF.h"
#include "../aos/AOS.h"
using namespace opt::base;
using namespace opt::smde;
using namespace opt::surrogate;
using namespace opt::aos;

namespace opt {
namespace esmde {

	class Algorithm_ESMDE : public Algorithm_SMDE{
		protected:
			int nApp;
			Manager_Surrogate *manager_surrogate;
			AOS *aos;
		public:
			Algorithm_ESMDE(int pMaxGen, int pPopSize, Evaluate *pEval, string surrogate_names, int napp, string smp, int seed);

			Algorithm_ESMDE(Evaluate *pEval, string surrogate_names);


			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, string surrogate_names, int napp, string smp, int seed);

			//Run all DE
			void runAll();

			virtual void run_generate(vector<IndividualPtr> &pop);

			virtual ~Algorithm_ESMDE();

			//Create the generation information to print parcial results
			virtual void createExtraHeaderInfo(ostringstream &extra);
			virtual void createExtraGenerationInfo(ostringstream &extra);

			//Set surrogates
			virtual void setSurrogates(string surrogate_names, Evaluate *pEval);
			virtual void addSurrogateByInput(Manager_Surrogate *manager, char name[10], char smp[7], Evaluate *pEval);

			virtual void applyReward(int index, double w);
			virtual void insertIndividualInSurrogate(IndividualPtr ind);
	};

} /* namespace esmde */
} /* namespace opt */
#endif /* ALGORITHM_ESMDE_H_ */
