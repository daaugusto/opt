/*
 * Algorithm_SLSDE.h
 *
 *  Created on: 22/05/2012
 *      Author: krempser
 */

#ifndef ALGORITHM_SLSDE_H_
#define ALGORITHM_SLSDE_H_

#define LOCALSEARCH_SMHC "SMHC"
#define LOCALSEARCH_SMSP "SMSP"
#define LOCALSEARCH_SMGS "SMGS"
#define LOCALSEARCH_HC   "HC"
#define LOCALSEARCH_GS   "GS"
#define LOCALSEARCH_SP   "SP"
#define LOCALSEARCH_RAND "RAND"
#define LOCALSEARCH_SFLS "SFLS"

#define F_BOUND_MIN -1.0
#define F_BOUND_MAX  1.0
#define H_STEP 0.5

#include <string>
#include <sstream>

#include "../base/Individual.h"
#include "../algorithm/Algorithm_DE.h"
#include "../surrogate/Evaluate_Surrogate.h"
#include "../surrogate/Evaluate_Surrogate_LWR.h"
#include "../surrogate/Evaluate_Surrogate_RBF.h"
#include "../surrogate/Evaluate_Surrogate_NN.h"
#include "../smde/Algorithm_SMDE.h"
using namespace opt::base;
using namespace opt::algorithm;
using namespace opt::surrogate;
using namespace opt::smde;

namespace opt {
namespace slsde {

class Algorithm_SLSDE : public Algorithm_SMDE{
protected:
	string sl;
double avgErr, sumErr;
public:
	Algorithm_SLSDE(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, string sl, int seed);
	Algorithm_SLSDE(Evaluate *pEval, Evaluate_Surrogate *pEvalSur);
	virtual ~Algorithm_SLSDE();

	void setConfig(int pMaxGen, int pPopSize, Evaluate *pEval, Evaluate_Surrogate *pEvalSur, int napp, string smp, string sl, int seed);

	virtual void createExtraHeaderInfo(ostringstream &extra);
	virtual void createExtraGenerationInfo(ostringstream &extra);

	virtual void run_generate(vector<IndividualPtr> &pop);

	virtual void crossover(IndividualPtr parent, IndividualPtr &off, vector<int> index);
	virtual double localSearch(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> &indexCrossOver, int nApp, string sl);

	virtual double hillClimb(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> indexCrossOver, int nApp, string sl);
	virtual double goldenSearch(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> indexCrossOver, int nApp, string sl);

	virtual double split(vector<IndividualPtr> &pop, int current, Operator *op, vector<int> indexParent, vector<int> indexCrossOver, int nApp, string sl);
};

} /* namespace slsde */
} /* namespace opt */
#endif /* ALGORITHM_SLSDE_H_ */
