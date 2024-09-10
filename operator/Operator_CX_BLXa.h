/*
 * Operator_CX_BLXa.h
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#ifndef OPERATOR_CX_BLXA_H_
#define OPERATOR_CX_BLXA_H_

#include "Operator.h"
#include "math.h"

namespace opt {
namespace operators {

	class Operator_CX_BLXa : public Operator{
		private:
			double alpha;
		public:
			Operator_CX_BLXa();
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring);

			void setParameterAlpha(double val);
	};

} /* namespace operators */
} /* namespace opt */
#endif /* OPERATOR_CX_BLXA_H_ */
