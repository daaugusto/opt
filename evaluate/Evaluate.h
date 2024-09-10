/*
 * Evaluate.h
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef EVALUATE_H_
#define EVALUATE_H_

#include "../base/Individual.h"
#include "../function/Function.h"
#include <vector>
using namespace std;
using namespace opt::base;
using namespace opt::function;

namespace opt {
namespace evaluate {

	class Evaluate {
		protected:
			Function *function;
		public:
			Evaluate(Function *func);
			virtual double calcFitness(IndividualPtr &ind) const;
			virtual double calcFitness(IndividualPtr &ind, bool calculated) const;
			virtual void setFunction(Function *funct);
			Function* getFunction() const;
			bool isValid(const IndividualPtr ind) const;
			bool isValid(const vector<double> constraints) const;
			bool operator() (IndividualPtr i,IndividualPtr j);

			//1 -- first best, 0 -- equals, -1 -- second best
			virtual int compare(IndividualPtr &ind1, IndividualPtr &ind2) const;
			virtual void update(const vector<IndividualPtr> pop);
			virtual double difference(const IndividualPtr ind1, const IndividualPtr ind2) const;

			//Initialize and finalize function informations (BBOB)
			virtual void initialize();
			virtual void finalize();

			virtual ~Evaluate();

			//Return and set the number of fitness evaluations
			virtual double getNEvals();
			virtual void setNEvals(double n);

			//Return and set the max number of fitness evaluations
			virtual double getMaxEvals();
			virtual void setMaxEvals(double n);
	};

} /* namespace evaluate */
}
#endif /* EVALUATE_H_ */
