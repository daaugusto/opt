/*
 * Algorithm_GA_AOS.h
 *
 *  Created on: 16/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef ALGORITHM_GA_AOS_H_
#define ALGORITHM_GA_AOS_H_

#include <ostream>
#include "../algorithm/Algorithm_GA.h"
#include "../aos/AOS.h"
using namespace opt::algorithm;
using namespace opt::aos;
using namespace std;

namespace opt {
namespace hybridAos{

	class Algorithm_GA_AOS  : public Algorithm_GA{
		private:
			AOS *aos_mt;
			AOS *aos_cx;
		public:
			Algorithm_GA_AOS(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			Algorithm_GA_AOS(Evaluate *pEval);
			void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, int seed = 0);
			void run_generate(vector<IndividualPtr> &pop);
			void runAll();

			double generateIndividual(int iCurrent, int iBest, vector<IndividualPtr> &pop, vector<IndividualPtr> &offspring);
			void applyRewardCx(int index, double w);
			void applyRewardMt(int index, double w);
			int selection(vector<IndividualPtr> &pop);
			double wSum;

	};

} /* namespace hybridAos */
} /* namespace opt */
#endif /* ALGORITHM_GA_AOS_H_ */
