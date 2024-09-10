/*
 * Evaluate_Deb.h
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef EVALUATE_DEB_H_
#define EVALUATE_DEB_H_

#include "Evaluate.h"

namespace opt {
namespace evaluate {

	class Evaluate_Deb: public Evaluate {
		public:
			Evaluate_Deb(Function *func): Evaluate(func){};
			virtual double calcFitness(IndividualPtr &ind) const;

			//1 -- first best, 0 -- equals, -1 -- second best
			virtual int compare(IndividualPtr &ind1, IndividualPtr &ind2) const;
			virtual double difference(IndividualPtr ind1, IndividualPtr ind2) const;
	};

} /* namespace evaluate */
} /* namespace opt */
#endif /* EVALUATE_DEB_H_ */
