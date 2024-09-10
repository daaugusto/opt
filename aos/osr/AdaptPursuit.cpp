#include "AdaptPursuit.h"




AdaptPursuit::AdaptPursuit(int N_operators, string OutputFile, double P_min, double Alpha, double Beta):ProbMatching(N_operators, OutputFile, P_min, Alpha){
		p_max = 1.0 - (((double)n_operators - 1.0) * P_min);
		beta = Beta;alpha = Alpha;
}

void AdaptPursuit::UpdateProbabilityVector(){
	unsigned opmax=0;
	double qualmax=0.0;
	for(unsigned i=0; i<n_operators; i++)
		if(quality[i]>qualmax){
			qualmax = quality[i];
			opmax=i;
		}
	prob[opmax] = prob[opmax] + ( beta * (p_max-prob[opmax]) );
	for(unsigned i=0; i<n_operators; i++)
		if(i!=opmax)
			prob[i] = prob[i] + ( beta * (p_min-prob[i]) );
}

AdaptPursuit::~AdaptPursuit(){}
