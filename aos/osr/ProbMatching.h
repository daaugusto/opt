
#ifndef PROBMATCHING_H_
#define PROBMATCHING_H_

#include "OperatorSelection.h"

class ProbMatching : public OperatorSelection {
public:

	ProbMatching(int N_operators, string OutputFile, double P_min, double Alpha);
	double ApplyReward(unsigned op);
	void updateBestOp(unsigned op);
	int OptionNotTried();
	int SelectOperator();
	void UpdateQualityVector(unsigned op, double reward);
	virtual void UpdateProbabilityVector();
	void PrintSpecificResults(FILE * file);
	void Reset();
	virtual ~ProbMatching();

protected:
	double p_min;
	double alpha;
	double * quality;
	double * prob;
	int * opTimes;
	double best_quality;
};

#endif /* PROBMATCHING_H_ */
