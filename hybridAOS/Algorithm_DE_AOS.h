/*
 * AlgorithmDEAOS.h
 *
 *  Created on: 15/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_DE_AOS_H_
#define ALGORITHM_DE_AOS_H_

#include <ostream>
#include "../algorithm/Algorithm_DE.h"
#include "../aos/AOS.h"
using namespace opt::algorithm;
using namespace opt::aos;
using namespace std;

namespace opt {
namespace hybridAos{

	class Algorithm_DE_AOS  : public Algorithm_DE{
		private:
			AOS *aos;
		public:
			Algorithm_DE_AOS(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			Algorithm_DE_AOS(Evaluate *pEval);
			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			void run_generate(vector<IndividualPtr> &pop);
			void runAll();

			double generateIndividual(int iCurrent, int iBest, vector<IndividualPtr> &pop, vector<IndividualPtr> &offspring);
			void applyReward(int index, double w);
			double wSum;

	};

} /* namespace hybridAos */
} /* namespace opt */
#endif /* ALGORITHM_DE_AOS_H_ */
