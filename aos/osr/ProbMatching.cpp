

#include "ProbMatching.h"

ProbMatching::ProbMatching(int N_operators, string OutputFile, double P_min, double Alpha) : OperatorSelection(N_operators, OutputFile){
	p_min = P_min;
	alpha = Alpha;
	quality = new double[n_operators];
	prob = new double[n_operators];
	opTimes = new int[n_operators];
	// Included in 2012/01/18
        Reset();
}

void ProbMatching::Reset(){
	for(unsigned i=0; i<n_operators; i++){
		prob[i] = 1.0/((double)n_operators);
		quality[i] = 1.0;
		opTimes[i] = 0;
	}
	best_quality=0;
}

double ProbMatching::ApplyReward(unsigned op){
	if(best_op==op) exploit++;
	else explore++;
	double reward = GetReward(op);
	UpdateQualityVector(op, reward);
	UpdateProbabilityVector();
	updateBestOp(op);
	opTimes[op]++;
	times++;

	/*cout << times << " " << best_op << " " << best_quality;
	for(int i=0; i<n_operators; i++)
		cout << " " << quality[i];
	cout << endl;*/
	return reward;
}

void ProbMatching::updateBestOp(unsigned op){
	double exploit_op=quality[op];
	//if the one that was the best has a lower \hat p, check between all; or if the previous best changed
	if((best_op==op && exploit_op < best_quality) || (best_op >= 0 && quality[best_op] != best_quality)){
		best_quality = -1; best_op = 0;
		double exploit_aux=-1;
		for(unsigned i=0; i<n_operators; i++){
			exploit_aux = quality[i];
			if(exploit_aux > best_quality){
				best_quality = exploit_aux;
				best_op = i;
			}
		}
	} else if(exploit_op >= best_quality){ //else if it is best than the previous best
		best_op=op;
		best_quality = exploit_op;
	}
}


int ProbMatching::OptionNotTried()
{
	int i = (int)(genrand_real1() * n_operators);
	for (unsigned j=0; j < n_operators; j++) {
		int k = (i + j) % n_operators;
		if (opTimes[k] == 0)
			return k;
	}
	printf(" We are in big trouble - ProbMatching::OptionNotTried\n");
	exit(1);
}

int ProbMatching::SelectOperator(){
	if(times < n_operators)
		return OptionNotTried();
	else{
		unsigned op;
		double sorted = genrand_real1();
		double sum = 0;
		for(op = 0; op < n_operators-1; op++){
			sum += prob[op];
			if(sum > sorted)
				return op;
		}
		return op;
	}
	printf(" We are in big trouble - ProbMatching::SelectOperator \n");
		exit(1);
}

void ProbMatching::UpdateQualityVector(unsigned op, double reward){
	if(credit[0]->getType()<3)
		quality[op] = quality[op] + (alpha * (reward - quality[op]) );
	else
		quality[op] = reward;
}

void ProbMatching::UpdateProbabilityVector(){
double sum = 0.0;
for(unsigned i=0; i<n_operators; i++)	sum += quality[i];
for(unsigned i=0; i<n_operators; i++)
	prob[i] = p_min + ((1.0 - ((double)n_operators) * p_min) * (quality[i]/sum));
}

void ProbMatching::PrintSpecificResults(FILE * file){}

ProbMatching::~ProbMatching(){
	delete [] quality;
	delete [] prob;
	delete [] opTimes;
}
