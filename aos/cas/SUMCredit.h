#ifndef SUMCREDIT_H_
#define SUMCREDIT_H_

#include "RankingCredit.h"



//this code implements exactly the same technique than the old "AUCRankingCredit1xAllv2"
//but in a cleaner way

class SUMCredit : public RankingCredit{
public:
	SUMCredit(int _W, bool _delta_fitness, unsigned _n_operators, bool _just_positive, bool _cut_negative, int _typeRank=0, double _decay=1);
	double getReward(int op, bool nonorm=false);
	void updateQueue(int op, double reward);
	void updateRewards();
	double calculateSUM(unsigned op);
	void updateRewardsAll();
	void calculateSUMAll();
	~SUMCredit();
protected:
	bool just_positive;
	bool cut_negative;
	double sum_sum;
	double *wSUMs;
};


#endif /* SUMCREDIT_H_ */
