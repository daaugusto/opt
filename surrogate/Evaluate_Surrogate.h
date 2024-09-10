/*
 * Evaluate_Surrogate.h
 *
 *  Created on: 18/04/2012
 *      Author: Eduardo Krempser
 */

#ifndef EVALUATE_SURROGATE_H_
#define EVALUATE_SURROGATE_H_

#define SURROGATE_KNN		"KNN"
#define SURROGATE_RNN		"RNN"
#define SURROGATE_LWR		"LWR"
#define SURROGATE_RBF		"RBF"
#define SURROGATE_LLR		"LLR"

#include "../evaluate/Evaluate.h"
#include "algebra/Algebra.h"
#include "../base/Input.h"
using namespace opt::evaluate;
using namespace opt::surrogate::algebra;
using namespace opt::base;

namespace opt {
namespace surrogate {

class Evaluate_Surrogate  : public Evaluate{
	protected:
		int nEval;
		string key;
	public:
		Evaluate_Surrogate(Function *func);
		virtual ~Evaluate_Surrogate();

		virtual double calcFitness(IndividualPtr &ind);
		virtual double calcFitness(IndividualPtr &ind, bool calculated);

		bool isValid(const IndividualPtr ind) const;
		bool operator() (IndividualPtr i,IndividualPtr j);

		//1 -- first best, 0 -- equals, -1 -- second best
		virtual int compare(IndividualPtr &ind1, IndividualPtr &ind2) const;
		virtual void update(const vector<IndividualPtr> pop);
		virtual void update( Evaluate* eval );
		virtual double difference(const IndividualPtr ind1, const IndividualPtr ind2) const;

		//Initialize and finalize function informations (BBOB)
		virtual void initialize();
		virtual void finalize();

		//Return and set the number of fitness evaluations
		virtual double getNEvals();
		virtual void setNEvals(double n);

		//Insert new information to surrogate model
		virtual void insert(IndividualPtr ind);

		//Set a parameter to surrogate model
		virtual void setParam(string param, double value);
		virtual void setParam(string param, int value);
		virtual void setParam(string param, string value);

		//Set surrogate's identification
		virtual void setKey(string k);
		virtual string getKey();

		//Return the mean and variance of the model, if exists
		virtual double getMean();
		virtual double getVariance();
		//Calc Expected Improviment
		virtual double calcEI(double y, double yMin, double mean, double variance);
};

} /* namespace surrogate */
} /* namespace opt */
#endif /* EVALUATE_SURROGATE_H_ */
