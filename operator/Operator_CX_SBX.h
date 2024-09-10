/*
 * Operator_CX_SBX.h
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#ifndef OPERATOR_CX_SBX_H_
#define OPERATOR_CX_SBX_H_

#include "Operator.h"
#include "math.h"

namespace opt {
namespace operators {

	class Operator_CX_SBX: public Operator {
		private:
			double n;
		public:
			Operator_CX_SBX();
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring);

			void setParameterN(double val);
	};

} /* namespace operators */
} /* namespace opt */
#endif /* OPERATOR_CX_SBX_H_ */
