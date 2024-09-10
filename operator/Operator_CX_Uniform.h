/*
 * Operator_CX_Uniform.h
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#ifndef OPERATOR_CX_UNIFORM_H_
#define OPERATOR_CX_UNIFORM_H_

#include "Operator.h"

namespace opt {
namespace operators {

	class Operator_CX_Uniform: public Operator {
		public:
			Operator_CX_Uniform();
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring);
	};

} /* namespace operators */
} /* namespace opt */
#endif /* OPERATOR_CX_UNIFORM_H_ */
