/*
 * Operator_MT_NonUniform.h
 *
 *  Created on: 09/02/2012
 *      Author: krempser
 */

#ifndef OPERATOR_MT_NONUNIFORM_H_
#define OPERATOR_MT_NONUNIFORM_H_

#include "Operator.h"
#include "math.h"

namespace opt {
namespace operators {

	class Operator_MT_NonUniform: public Operator {
		public:
			Operator_MT_NonUniform();
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring);

			//Apply operator with setted parameter
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param);

			//Apply operator with the index of the parents
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index);
	};

} /* namespace operators */
} /* namespace opt */
#endif /* OPERATOR_MT_NONUNIFORM_H_ */
