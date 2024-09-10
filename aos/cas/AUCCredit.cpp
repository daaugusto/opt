#include "AUCCredit.h"
#include <iostream>

AUCCredit::AUCCredit(int _W, bool _delta_fitness, unsigned _n_operators, bool _just_positive, bool _cut_negative, int _typeRank, double _decay)
	: RankingCredit(_W, _delta_fitness, _n_operators, _typeRank, _decay){
	just_positive=_just_positive;
	cut_negative=_cut_negative;
	wAUCs = new double [_n_operators];
	w_x = new int[_W];
	w_y = new int[_W];
	sumdelta = new double[_W];
	for(unsigned i=0; i<_n_operators; i++)	wAUCs[i] = 0;
	weights = new double[_W];
}

void AUCCredit::updateQueue(int op, double reward){
	RankingCredit::updateQueue(op, reward);
	updateRewards();
}

double AUCCredit::getReward(int op, bool nonorm){
	if(sum_auc==0) return 0;
	return wAUCs[op]/sum_auc;
}

void AUCCredit::updateRewards(){
	sum_auc = 0;
	for(unsigned i=0; i<n_operators; i++){
		wAUCs[i] = calculateAUC(i);
		sum_auc += wAUCs[i];
	}
}

double AUCCredit::calculateAUC(unsigned op){

	unsigned count_x=0, count_y=0;
	double x=0, y=0, y_old=0, reward=0, thisdelta=0, thisdelta_x, thisdelta_y;
	for(unsigned i=0; i<wRewards.size(); i++)
		w_x[i] = w_y[i] = sumdelta[i] = 0;

	//here I count the number of ExAquos for each reward, and the sum of each axis (to be used in its normalization)
	for(unsigned i=0; i<wRewards.size() && !(just_positive && cut_negative && wRewards[rank[i]]==DBL_MAX); i += w_x[i] + w_y[i]){
		for(unsigned j=i; j<wRewards.size() && (wRewards[rank[i]]==wRewards[rank[j]] || (just_positive && !cut_negative && wRewards[rank[i]]==DBL_MAX && wRewards[rank[j]]==DBL_MAX )); j++){ //check for Ex-Aquos
			sumdelta[i] += delta[j];
			if(wOps[rank[j]]==op) {
				count_y++; w_y[i]++;
			} else {
				count_x++; w_x[i]++;
			}
		}
	}

	//if this is the only participant in the current window, "full" reward.
	if(count_y==wRewards.size()) reward=1;
	//or if there are no participations in the current window for the given op, "null" reward
	else if(count_y==0) reward=0;
	else{ //I calculate the AUC area
		for(unsigned i=0; i<wRewards.size() && !(just_positive && cut_negative && wRewards[rank[i]]==DBL_MAX); i += w_x[i] + w_y[i]){
			if((w_x[i]+w_y[i]) > 1){ //if there was any Ex-Aquo
				thisdelta = sumdelta[i]/(w_x[i]+w_y[i]);
				thisdelta_x = thisdelta_y = thisdelta;
				y_old = y;
				x += w_x[i] * thisdelta_x;
				y += w_y[i] * thisdelta_y;
				reward += y_old * (w_x[i] * thisdelta_x); //sum the rectangle are below the "triangle" formed by this "diagonal" line
				reward += .5 * (w_y[i] * thisdelta_y) * (w_x[i] * thisdelta_x); // and sum the "triangle" formed by this line
			}
			else if(wOps[rank[i]] == op){ //update y
				thisdelta = delta[i];
				y += thisdelta;
			}
			else{  //update x
				thisdelta = delta[i];
				x += thisdelta;
				reward += (y * thisdelta);
			}
		}
	}
	return reward;
}

void AUCCredit::calculateAUCAll(){

}

AUCCredit::~AUCCredit(){
	delete []wAUCs;
	delete []w_x;
	delete []w_y;
	delete []sumdelta;
	delete []weights;
}
