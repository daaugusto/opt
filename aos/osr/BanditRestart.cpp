#include "BanditRestart.h"


BanditRestart::BanditRestart(int N_operators, string OutputFile, bool User, double v_Scaling, double v_Gamma, int _normalize):BanditAlone(N_operators, OutputFile, User, v_Scaling, _normalize){
	adaptPH = new AdaptivePH(n_operators, v_Gamma);
	change=0;
}

double BanditRestart::ApplyReward(unsigned op){
	change=0;
	double rewardPH = BanditAlone::ApplyReward(op);

	if(best_op==op){
		change = adaptPH->CheckPH(op, rewardPH);
		if(change) Reset();
	}

	return rewardPH;
}

void BanditRestart::Reset(){
	BanditAlone::Reset();
	adaptPH->Restart();
}

void BanditRestart::PrintSpecificResults(FILE * file){
	fprintf(file, "%d ", change);
	if(user)
		for (unsigned i=0; i<n_operators; i++)
			fprintf(file, "%d %g %g %g %g ", lst_option[i]->getTimes(), lst_option[i]->getExploration(times), lst_option[i]->getExploitation(), adaptPH->getCummDiff(i), adaptPH->getMaxCummDiff(i));
}

bool BanditRestart::getRestart(){
	return change;
}

BanditRestart::~BanditRestart(){}
