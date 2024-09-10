#include "SUMCredit.h"
#include <iostream>


SUMCredit::SUMCredit(int _W, bool _delta_fitness, unsigned _n_operators, bool _just_positive, bool _cut_negative, int _typeRank, double _decay)
	: RankingCredit(_W, _delta_fitness, _n_operators, _typeRank, _decay){
	just_positive=_just_positive;
	cut_negative=_cut_negative;
	wSUMs = new double[_n_operators];
}

void SUMCredit::updateQueue(int op, double reward){
	RankingCredit::updateQueue(op, reward);
	//updateRewards();
	updateRewardsAll();
}

void SUMCredit::updateRewards(){
	sum_sum = 0;
	for(unsigned i=0; i<n_operators; i++){
		wSUMs[i] = calculateSUM(i);
		sum_sum += wSUMs[i];
	}
}

void SUMCredit::updateRewardsAll(){
	calculateSUMAll();
	sum_sum = 0;
	for(unsigned i=0; i<n_operators; i++)
		sum_sum += wSUMs[i];
}

double SUMCredit::getReward(int op, bool nonorm){
	if(sum_sum==0) return 0;
	return wSUMs[op]/sum_sum;
}

double SUMCredit::calculateSUM(unsigned op){
	unsigned count=0, ties=0, old_count=0;
	double reward=0, sum_op=0, total_delta=0, old_total_delta=0;

	for(unsigned i=0; i<wRewards.size() && !(just_positive && cut_negative && wRewards[rank[i]]==DBL_MAX); i+=ties, ties=0, old_count=count, old_total_delta=total_delta){
		for(unsigned j=i; j<wRewards.size() && (wRewards[rank[i]]==wRewards[rank[j]] || (just_positive && !cut_negative && wRewards[rank[i]]==DBL_MAX && wRewards[rank[j]]==DBL_MAX )); j++){ //check for Ex-Aquos
			ties++;
			total_delta += delta[j];
			if(wOps[rank[j]]==(unsigned)op)	count++;
		}

		sum_op += ((total_delta-old_total_delta)/ties) * (count-old_count);
		//cout << i << " " << ties << " " << ((total_delta-old_total_delta)/ties) << " " << ((total_delta-old_total_delta)/ties) * (count-old_count) << endl;
	}

	//if this is the only participant in the current window, "full" reward.
	if(count==wRewards.size()) reward=1;
	//or if there are no participations in the current window for the given op, "null" reward
	else if(count==0) reward=0;
	else reward	= sum_op/total_delta;

	return reward;
}

void SUMCredit::calculateSUMAll(){
	double sum_delta=0, share=0, ties=1;
	unsigned i=0, j=0;

	for(i=0; i<n_operators; i++) wSUMs[i]=0;

	for(i=0, ties=1; i<wRewards.size() && !(just_positive && cut_negative && wRewards[rank[i]]<=0); i+=ties, ties=1){
		sum_delta = delta[i];
		for(j=i+1; j<wRewards.size() && (wRewards[rank[i]]==wRewards[rank[j]] || (just_positive && !cut_negative && wRewards[rank[i]]<=0 && wRewards[rank[j]]<=0 )); j++, ties++) //check for Ex-Aquos
			sum_delta += delta[j];
		share = sum_delta/ties;
		for(j=i; j<(i+ties); j++)	wSUMs[wOps[rank[j]]] += share;
	}
}

SUMCredit::~SUMCredit(){
	delete []wSUMs;
}

