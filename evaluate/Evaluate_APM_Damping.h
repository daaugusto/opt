/*
 * Evaluate_APM_Damping.h
 *
 *  Created on: 08/02/2012
 *      Author: Edurdo Krempser
 */

#ifndef EVALUATE_APM_DAMPING_H_
#define EVALUATE_APM_DAMPING_H_

#include "Evaluate_APM.h"
#include "math.h"

#define  TETA 0.7

namespace opt {
namespace evaluate {

	class Evaluate_APM_Damping : public Evaluate_APM{
	public:
		Evaluate_APM_Damping(Function *func):Evaluate_APM(func){};
		virtual void update(vector<IndividualPtr> pop);
	};

} /* namespace evaluate */
}
#endif /* EVALUATE_APM_DAMPING_H_ */
