#ifndef RANKINGCREDIT_H_
#define RANKINGCREDIT_H_



#include "CreditAssignment.h"

#include <string>
#include <deque>
#include <iostream>
#include <math.h>



//this is a cleaner "template" for the rank-based methods
class RankingCredit : public CreditAssignment{
public:
	RankingCredit(int _W, bool _delta_fitness, unsigned _n_operators, int _typeRank=0, double _decay=1);
	virtual void updateQueue(int op, double reward);
	virtual double getReward(int op, bool nonorm=false)=0;
	int includeRank(double reward);
	void excludeRank(double reward);
	int getTimesOp(int op);
	double getDelta(int rank);

	void printQueue();
	void printRankedQueue();
	void clearCredit();
	bool isNorm();
	virtual ~RankingCredit();
protected:
	std::deque <unsigned> wOps; //keeps the chosen operators, synchronized with the respective rank
	int * rank;
	unsigned n_operators;
	unsigned *times_op; //keeps the total participations of each op on the current window
	int typeRank;
	double decay;
	double * delta;
};

#endif /* RANKINGCREDIT_H_ */
