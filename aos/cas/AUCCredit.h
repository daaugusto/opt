#ifndef AUCCREDIT_H_
#define AUCCREDIT_H_

#include "RankingCredit.h"



//this code implements exactly the same technique than the old "AUCRankingCredit1xAllv2"
//but in a cleaner way

class AUCCredit : public RankingCredit{
public:
	AUCCredit(int _W, bool _delta_fitness, unsigned _n_operators, bool _just_positive, bool _cut_negative, int _typeRank=0, double _decay=1);
	void updateQueue(int op, double reward);
	double getReward(int op, bool nonorm=false);
	void updateRewards();
	double calculateAUC(unsigned op);
	void calculateAUCAll();
	~AUCCredit();
protected:
	double * wAUCs;
	double sum_auc;
	int * w_x;
	int * w_y;
	double *sumdelta;
	bool just_positive;
	bool cut_negative;
	double *weights;
	int rank_inserted; //index of the lastly inserted reward
	int rank_deleted; //index of the most recently inserted reward
};

#endif /* AUCCREDIT_H_ */
