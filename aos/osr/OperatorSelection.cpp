
#include "OperatorSelection.h"


OperatorSelection::OperatorSelection(unsigned N_operators, string OutputFile, bool User){
	times = TCR = bestChosen = explore = exploit = 0;
	n_operators = N_operators;
	user = User;
	//if (Seed==0)	Seed = time(0);
	//rng.reseed(Seed);
//	outputFile = fopen(OutputFile.c_str(), "w");
	best_op=0;//used to count the exploration and exploitation trials
}

void OperatorSelection::setFitnessType(int _fitnessType){
	fitnessType = _fitnessType;
}

void OperatorSelection::PrintResults(int generation, double fitness, double reward, unsigned op){
	fprintf(outputFile, "%d %d %g %g %d %d ", generation, times, fitness, reward, explore, exploit);
	//fprintf(outputFile, "%d %d %d %d ", generation, times, explore, exploit);
	PrintSpecificResults(outputFile);
	for(unsigned i=0; i<n_operators; i++)
		if(op==i)	fprintf(outputFile, "1 ");
		else		fprintf(outputFile, "0 ");
	if(fitnessType == 4)
		fprintf(outputFile, "%g %d ", TCR, bestChosen);
	fprintf(outputFile, "\n");
}

//to use with mutation
void OperatorSelection::addFitnessImprov(unsigned op, double fit_old, double fit_new){
	/*if(fitnessType == 4){
		//cout << artificial->getCycle() << " " << op << " " << artificial->getBestOp() << endl;
		if(op == artificial->getBestOp())
			bestChosen++;
	}*/

	//cout << "Adding deltaFitness " << (fit_new-fit_old) << ", op " << op << endl;
	if(credit[0]->getType()<3)
		credit[op]->addFitnessImprov(op, fit_old, fit_new);
	else
		credit[0]->addFitnessImprov(op, fit_old, fit_new);
}

void OperatorSelection::addReward(unsigned op, double reward){
	if(credit[0]->getType()<3)
		credit[op]->addReward(op, reward);
	else
		credit[0]->addReward(op, reward);
}

//to use with crossover
void OperatorSelection::addFitnessImprov(unsigned op, double fit_old1, double fit_old2, double fit_new1, double fit_new2){

	if(credit[0]->getType()<3)
		credit[op]->addFitnessImprov(op, fit_old1, fit_old2, fit_new1, fit_new2);
	else
		credit[0]->addFitnessImprov(op, fit_old1, fit_old2, fit_new1, fit_new2);
}

void OperatorSelection::verifyRewNormal(unsigned op){
	// in case "normalization" is on, checks which is the highest "output" (according to the chosen credit assignment)
	// between all operators, to set it in the used operator, so that the reward will be normalized when asked.
	if(credit[0]->isNorm()){
		double maxrew=0, temprew=0;
		for (unsigned i=0; i<n_operators; i++){
			temprew = credit[i]->getReward(i, true);
			if(temprew > maxrew) maxrew = temprew;
		}
		credit[op]->setMaxReward(maxrew);
	}
}

double OperatorSelection::GetReward(unsigned op){
	double reward, instRew;
	if(credit[0]->getType()<3){
		verifyRewNormal(op);
		reward = credit[op]->getReward(op, false);
		instRew = credit[op]->getLastReward(op, true);
	} else {
		reward = credit[0]->getReward(op, false);
		instRew = credit[0]->getLastReward(op, true);
	}
	//cout << instRew << endl;
	TCR+=instRew;
	return reward;
}

OperatorSelection::~OperatorSelection(){
	//fclose(outputFile);
}
