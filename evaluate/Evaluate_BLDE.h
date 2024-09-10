/*
 * Evaluate_BLDE.h
 *
 *  Created on: 13/03/2019
 *      Author: Eduardo Krempser
 */

#ifndef EVALUATE_BLDE_H_
#define EVALUATE_BLDE_H_

#include "Evaluate.h"
#include "../function/Function_SMD.h"

namespace opt {
namespace evaluate {

	class Evaluate_BLDE: public Evaluate {
		protected:
//			Function_SMD *functionSMD;
			//Number of follower's calcs
			double nCallsFollower;
			//Max number of evaluations (if there is)
			double maxCallsFollower;
		public:
			Evaluate_BLDE(Function *func);
			virtual double calcFitness(IndividualPtr &ind) const;

			//1 -- first best, 0 -- equals, -1 -- second best
			virtual int compare(IndividualPtr &ind1, IndividualPtr &ind2) const;
			virtual double difference(IndividualPtr ind1, IndividualPtr ind2) const;

			//Calc fitness to leader or follower
			virtual double calcFitness(IndividualPtr &indLeader, IndividualPtr &indFollower, int level) const;
//			virtual Function_SMD* getFunctionSMD() const;

			//Return and set the number of follower's fitness evaluations 
			virtual double getNEvalsFollower();
			virtual void setNEvalsFollower(double n);
	};

} /* namespace evaluate */
} /* namespace opt */
#endif /* EVALUATE_BLDE_H_ */
