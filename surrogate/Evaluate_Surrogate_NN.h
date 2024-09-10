/*
 * Evaluate_Surrogate_NN.h
 *
 *  Created on: 18/04/2012
 *      Author: krempser
 */

#ifndef EVALUATE_SURROGATE_NN_H_
#define EVALUATE_SURROGATE_NN_H_

#include "math.h"
#include "Evaluate_Surrogate.h"
#include "kdtree/KDTree.h"
using namespace opt::surrogate;
using namespace opt::surrogate::kdtree;

#define KNN 0
#define RNN 1

namespace opt {
namespace surrogate {

class Evaluate_Surrogate_NN: public Evaluate_Surrogate {
	private:
		KDTree *tree;
		double r;
		int k;
		int type;
	public:
		Evaluate_Surrogate_NN(Function *func, int k);
		Evaluate_Surrogate_NN(Function *func, double r);
		Evaluate_Surrogate_NN(Function *func, int k, double r);
		virtual ~Evaluate_Surrogate_NN();

		virtual double calcFitness(IndividualPtr &ind);
		virtual double similarity(IndividualPtr &ind1, IndividualPtr &ind2);

		void insert(IndividualPtr ind);

		//Set a parameter to surrogate model
		virtual void setParam(string param, double value);
		virtual void setParam(string param, int value);

		//Update evaluate info
		void update(Evaluate *eval);

};

} /* namespace surrogate */
} /* namespace opt */
#endif /* EVALUATE_SURROGATE_NN_H_ */
