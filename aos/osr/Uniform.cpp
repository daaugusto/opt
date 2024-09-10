

#include "Uniform.h"


Uniform::Uniform(int N_operators, string OutputFile) : OperatorSelection(N_operators, OutputFile){}

double Uniform::ApplyReward(unsigned op){
	double reward = GetReward(op);
	times++;
	return reward;
}

int Uniform::OptionNotTried(){
	return SelectOperator();
}

int Uniform::SelectOperator(){
	return (int)(genrand_real1() * n_operators);
}

void Uniform::PrintSpecificResults(FILE * file){}

void Uniform::Reset(){}

Uniform::~Uniform(){}
