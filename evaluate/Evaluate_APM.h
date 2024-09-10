/*
 * EvaluateAPM.h
 *
 *  Created on: 08/02/2012
 *      Author: krempser
 */

#ifndef EVALUATEAPM_H_
#define EVALUATEAPM_H_

#include "Evaluate.h"
#include "../base/Individual.h"
#include "../function/Function.h"
#include "math.h"
using namespace opt::base;
using namespace opt::function;

namespace opt{
namespace evaluate {

	class Evaluate_APM : public Evaluate{
		protected:
			double *k;
			double fAvg;
		public:
			Evaluate_APM(Function *func);
			virtual double calcFitness(IndividualPtr &ind) const;
			virtual double calcFitness(IndividualPtr &ind, bool calculed) const;

			//1 -- first best, 0 -- equals, -1 -- second best
			virtual void update(vector<IndividualPtr> pop);

			virtual int compare(IndividualPtr &ind1, IndividualPtr &ind2) const;

			virtual ~Evaluate_APM();
	};

} /* namespace evaluate */
}
#endif /* EVALUATEAPM_H_ */
