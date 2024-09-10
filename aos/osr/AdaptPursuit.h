#ifndef ADAPTPURSUIT_H_
#define ADAPTPURSUIT_H_

#include "ProbMatching.h"


class AdaptPursuit : public ProbMatching {
public:
	AdaptPursuit(int N_operators, string OutputFile, double P_min, double Alpha, double Beta);
	void UpdateProbabilityVector();
	~AdaptPursuit();

private:
	double p_max;
	double beta;
};


#endif /* ADAPTPURSUIT_H_ */
