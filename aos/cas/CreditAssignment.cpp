#include "CreditAssignment.h"
#include <iostream>
using namespace std;


CreditAssignment::CreditAssignment(int _W, bool _delta_fitness, int _type, int _norm){
	W=_W;
	type = _type;
	if(_norm==1 || _norm==3) //vide parameter description in the main file
		normalized = 1;
	else normalized = 0;
	delta_fitness = _delta_fitness;
	clearCredit();
}

bool CreditAssignment::isNorm(){
	//cout << "isNorm" << endl;
	return normalized;
}

int CreditAssignment::getType(){
	return type;
}

int CreditAssignment::getTimesOp(int op){
	return wRewards.size();
}

//to use with mutation
void CreditAssignment::addFitnessImprov(int op, double fit_old, double fit_new){
	//cout << "addFitnessImprov1" << endl;
	double diff = fit_new - fit_old;
	if(delta_fitness)
		updateQueue(op, diff);
	else{
		if (diff <= 0) fit_new = 0;
		updateQueue(op, fit_new);
	}

}

//### I could have twice the information, by using both generated offspring to reward the operators
//### In the current way, there is always twice the information for the mutation operators
//### What might explain the difference in the best values found for W (to be checked).
//to use with crossover
void CreditAssignment::addFitnessImprov(int op, double fit_old1, double fit_old2, double fit_new1, double fit_new2){
	//cout << "addFitnessImprov2" << endl;
	double best_old, best_new;

	if(fit_old1 > fit_old2) best_old = fit_old1;
	else best_old = fit_old2;

	if(fit_new1 > fit_new2) best_new = fit_new1;
	else best_new = fit_new2;

	double diff = best_new - best_old;
	if(delta_fitness)
		updateQueue(op, diff);
	else{
		if(diff <= 0) best_new = 0;
		updateQueue(op, best_new);
	}
}

void CreditAssignment::addReward(int op, double reward){
	//cout << "===================" << endl;
	//printQueue();
	updateQueue(op, reward);
	//cout << "===================" << endl;
	//printQueue();
	//cout << "===================" << endl;
}

void CreditAssignment::setMaxReward(double _max){
	//cout << "setMaxReward" << endl;
	if(_max < 0) maxReward = 0;
	else maxReward = _max;
}

double CreditAssignment::getMaxReward(){
	//cout << "getMaxReward" << endl;
	return maxReward;
}

double CreditAssignment::getReward(int op, bool nonorm){
	if(!type){
		return getBestReward(nonorm); //Extreme
	} else if(type==1){
		return getAvgReward(nonorm); //Average
	} else if(type==2){
		return getLastReward(op, nonorm); //Instantaneous
	} else {
		return 0;
	}
}

double CreditAssignment::getLastReward(int op, bool nonorm){
	//cout << "getLastReward" << endl;
	double instRew, divide;

	if(!normalized || nonorm || !maxReward) divide=1.0;
	else divide = maxReward;

	if(wRewards.size()){
		instRew = wRewards.front();
		double reward = instRew/divide;
		if(reward > 0) return reward;
	}

	return 0;
}

double CreditAssignment::getBestReward(bool nonorm){
	//cout << "getBestReward" << endl;
	double divide;

	if(!normalized || nonorm || !maxReward) divide=1.0;
	else divide=maxReward;

	double reward=bestReward/divide;
	if(reward > 0)	return reward;
	return 0;
}

double CreditAssignment::getAvgReward(bool nonorm){
	//cout << "getAvgReward" << endl;
	double divide, avg = (double)sumReward/(double)wRewards.size();

	if(!normalized || nonorm || !maxReward) divide=1.0;
	else divide=maxReward;

	double reward = avg/divide;
	if(reward>0) return reward;
	return 0;
}

void CreditAssignment::updateQueue(int op, double reward){
	//cout << "updateQueue \t" << op << "\t" << reward << "\t" << wRewards.size() << "\t" << W << endl;
	sumReward += reward; //update the sum, used to extract the average, counts also the negative rewards.
	wRewards.push_front(reward); //insert the latest reward in the queue

	if(reward > bestReward)	//if it is better than the actual best,
		bestReward = reward;//update the best

	if(wRewards.size() > W){ 		//if the queue becomes bigger than W
		double back = wRewards.back();//keeps the last one's value
		sumReward -= back;			//used to extract the average
		wRewards.pop_back(); 		//removes the last one from the queue
		if(back == bestReward){		//if last was the best
			bestReward = 0;
			deque<double>::reverse_iterator myIterator;
			for(myIterator=wRewards.rbegin(); myIterator!=wRewards.rend(); ++myIterator)
				  if(*myIterator > bestReward) //searches for the actual best
					  bestReward = *myIterator;
		}
	}
}

bool CreditAssignment::checkFullQueue(){
	if(wRewards.size()<W) return false;
	else	return true;
}

void CreditAssignment::printQueue(){
//cout << "printQueue" << endl;
	deque<double>::reverse_iterator myIterator;
   for(myIterator=wRewards.rbegin(); myIterator!=wRewards.rend(); ++myIterator)
	  std::cout << " " << *myIterator << " ";
   std::cout << std::endl;
}

void CreditAssignment::clearCredit(){
	wRewards.clear();
	bestReward = sumReward = maxReward = 0;
}

void CreditAssignment::printRankedQueue(){

}

CreditAssignment::~CreditAssignment(){

}
