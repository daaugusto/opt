#ifndef OPERATORSELECTION_H_
#define OPERATORSELECTION_H_

#include <string>
#include <iostream>
#include "../ubcsat/random.h"
#include "../cas/CreditAssignment.h"
#include "stdio.h"
#include "stdlib.h"

using namespace std;

class OperatorSelection{
public:
	OperatorSelection(unsigned N_operators, std::string OutputFile, bool User=false);
	void PrintResults(int generation, double fitness, double reward, unsigned op);
	void addFitnessImprov(unsigned op, double fit_old, double fit_new); //to use with mutation
	void addFitnessImprov(unsigned op, double fit_old1, double fit_old2, double fit_new1, double fit_new2); //to use with crossover
	void addReward(unsigned op, double reward); //to use with any other thing
	void verifyRewNormal(unsigned op); //update the normalization factor based on the highest output between all ops
	double GetReward(unsigned op);
	void printRankedQueue(); //just for the rank-based CASs
	void setFitnessType(int _fitnessType);

	virtual double ApplyReward(unsigned op) = 0;
	virtual void PrintSpecificResults(FILE * file) = 0;
	virtual int OptionNotTried() = 0;
	virtual int SelectOperator() = 0;
	virtual bool getRestart(){return 0;}
	virtual ~OperatorSelection();
	virtual void Reset() = 0;
	CreditAssignment ** credit;

protected:
	bool user;
	unsigned n_operators;
	unsigned times;
	FILE * outputFile;
	double TCR;
	int bestChosen;
	int explore, exploit;
	unsigned best_op;
	int fitnessType;
};

#endif /* OPERATORSELECTION_H_ */
