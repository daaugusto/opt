/*
 * Evaluate_APM_Monotonic.h
 *
 *  Created on: 08/02/2012
 *      Author: krempser
 */

#ifndef EVALUATE_APM_MONOTONIC_H_
#define EVALUATE_APM_MONOTONIC_H_

#include "Evaluate_APM.h"
#include "math.h"

namespace opt{
namespace evaluate{

	class Evaluate_APM_Monotonic : public Evaluate_APM{
		public:
			Evaluate_APM_Monotonic(Function *func):Evaluate_APM(func){};
			virtual void update(vector<IndividualPtr> pop);
	};

} /* namespace evaluate */
}
#endif /* EVALUATE_APM_MONOTONIC_H_ */
