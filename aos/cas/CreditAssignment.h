#ifndef CREDITASSIGNMENT_H_
#define CREDITASSIGNMENT_H_

#include <deque>
#include <float.h>
#include "stdio.h"
#include "stdlib.h"

class CreditAssignment{
public:
	CreditAssignment(int _W, bool _delta_fitness=0, int _type = 0, int _norm = 0);
	CreditAssignment(int _W, int _type = 0, int _norm = 0);
	virtual bool isNorm();
	int getType();
	virtual int getTimesOp(int op);
	void addFitnessImprov(int op, double fit_old, double fit_new); //to use with mutation
	void addFitnessImprov(int op, double fit_old1, double fit_old2, double fit_new1, double fit_new2); //to use with crossover
	void addReward(int op, double reward);
	void setMaxReward(double _max);
	double getMaxReward();
	virtual double getReward(int op, bool nonorm);
	virtual double getLastReward(int op, bool nonorm);
	double getBestReward(bool nonorm=false);
	double getAvgReward(bool nonorm=false);
	virtual void updateQueue(int op, double reward);
	bool checkFullQueue();
	virtual void printQueue();
	virtual void printRankedQueue();
	virtual void clearCredit();
	virtual ~CreditAssignment();

protected:
	std::deque<double> wRewards;
	unsigned int W;//size of the sliding window
	int type; //extreme (0), average (1) and rank-based
	double bestReward;
	double sumReward;
	bool normalized;
	double maxReward; //keeps the maximum value of all the ops, for normalization
	bool delta_fitness; //used to select between delta_fitness and fitness (few hours to deadline, so global variable for sure! :-)
};


#endif /* CREDITASSIGNMENT_H_ */
