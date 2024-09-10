/*
 * Operator_MT_Rand.h
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#ifndef OPERATOR_MT_RAND_H_
#define OPERATOR_MT_RAND_H_

#include "Operator.h"

namespace opt {
namespace operators {

	class Operator_MT_Rand: public Operator {
		public:
			Operator_MT_Rand();
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring);
	};

} /* namespace operators */
} /* namespace opt */
#endif /* OPERATOR_MT_RAND_H_ */
