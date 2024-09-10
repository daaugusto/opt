
#ifndef UNIFORM_H_
#define UNIFORM_H_

#include "OperatorSelection.h"

class Uniform : public OperatorSelection {
public:

	Uniform(int N_operators, string OutputFile);
	double ApplyReward(unsigned op);
	int OptionNotTried();
	int SelectOperator();
	void PrintSpecificResults(FILE * file);
	void Reset();
	virtual ~Uniform();
};


#endif /* UNIFORM_H_ */
