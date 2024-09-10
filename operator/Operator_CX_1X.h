/*
 * Operator_CX_1X.h
 *
 *  Created on: 08/02/2012
 *      Author: krempser
 */

#ifndef OPERATOR_CX_1X_H_
#define OPERATOR_CX_1X_H_

#include "Operator.h"

namespace opt {
namespace operators {

	class Operator_CX_1X : public Operator{
	public:
		Operator_CX_1X();
		virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring);
	};

} /* namespace operators */
} /* namespace opt */
#endif /* OPERATOR_CX_1X_H_ */
