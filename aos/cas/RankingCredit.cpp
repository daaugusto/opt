#include "RankingCredit.h"



RankingCredit::RankingCredit(int _W, bool _delta_fitness, unsigned _n_operators, int _typeRank, double _decay)
: CreditAssignment(_W, _delta_fitness, 3){
	n_operators = _n_operators;
	typeRank = _typeRank;
	decay = _decay;

	rank = new int[_W];
	delta = new double[_W];
	times_op = new unsigned[n_operators];

	for(int i=0; i<_W; i++) delta[i] = getDelta(i+1);

	clearCredit();
}

void RankingCredit::updateQueue(int op, double reward){
	times_op[op]++;
	if((wRewards.size()+1) > W){ 		//if the queue becomes bigger than W
		times_op[wOps.back()]--;
		excludeRank(wRewards.back());
		wRewards.pop_back(); 		//removes the last one from the queue
		wOps.pop_back();
	}
	includeRank(reward);
	wRewards.push_front(reward); //insert the latest reward in the queue
	wOps.push_front(op);
}

int RankingCredit::includeRank(double reward){

	//find the place to put this reward (top-down)
	int pos_rank=-1;
	for(unsigned i=0; i<wRewards.size(); i++){
		//std::cout << "Comparing " << wRewards[rank[i]] << " to " << reward << std::endl;
		if(wRewards[rank[i]]>=reward) { //minimization, the lowest the reward the better (f(offspring)-f(parent)) gives a negative value
			pos_rank = i; break;
		}
	}

	if(pos_rank == -1){
		if(wRewards.size()<W) pos_rank=wRewards.size(); //to be added in the last position
		else{
			printf(" We are in big trouble (BoolRankingCredit-includeRank)\n");
			exit(1);
		}
	}

	//as the new rewarded was inserted in the front of the queue
	//update all the rewards ranked before it with a +1
	for(int i=0; i<pos_rank; i++)
		rank[i]++;
	//then update all the rewards after it, letting one free space for it
	for(unsigned i=wRewards.size(); i>(unsigned)pos_rank; i--) {
		if(i>=W) continue;
		rank[i]=rank[i-1]+1;
	}
	//finally, the new inserted reward, which is in the position 0 of the queue
	rank[pos_rank]=0;

	return pos_rank;
}

void RankingCredit::excludeRank(double reward){

	//find the ranking of this reward (bottom-up)
	int pos_rank=-1;
	for(int i=wRewards.size()-1; i>=0; i--)
		if(wRewards[rank[i]]==reward) {
			pos_rank = i; break;
		}

	//just in case...
	if(pos_rank == -1){
		printf(" We are in big trouble (BoolRankingCredit-excludeRank)\n");
		exit(1);
	}

	for(unsigned i=pos_rank; i<wRewards.size()-1; i++)
		rank[i] = rank[i+1];

}

double RankingCredit::getDelta(int rank){
	int complrank= W - rank + 1;
	if(typeRank==2)
		return pow((double)decay,(double)rank); //k^r
	else if(typeRank==1){
		rank = W - rank + 1;
		return (pow(2.0,(double)complrank)-1)/log(1+rank); //NDCG = (2^(w-r) - 1)/log(1+r))
	}
	else if(typeRank==3) //equal
		return 1.0;
	return pow((double)decay,(double)rank) * complrank; //k^r * (w - r)
}


void RankingCredit::printQueue(){
	for(unsigned i=0; i<wRewards.size(); i++)
		std::cout << i << " " << wOps[i] << " " << wRewards[i] << std::endl;
}

void RankingCredit::printRankedQueue(){
	for(unsigned i=0; i<wRewards.size(); i++)
		std::cout << "Rk: " << i << " Pos: " <<  rank[i] << " Op: " << wOps[rank[i]] << " Rewd: " << wRewards[rank[i]] << std::endl;
}

void RankingCredit::clearCredit(){
	CreditAssignment::clearCredit();
	for(unsigned i=0; i<n_operators; i++) times_op[i]=0;
	for(unsigned i=0; i<W; i++)	rank[i]=i;
	wOps.clear();
}

bool RankingCredit::isNorm(){
	return 0;
}

int RankingCredit::getTimesOp(int op){
	return times_op[op];
}

RankingCredit::~RankingCredit(){
	wOps.clear();
	delete []rank;
	delete []times_op;
}
