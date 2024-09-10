#include "AUCBandit.h"


//this code version implements just the AUCBandit, forgetting about the other variants that finally showed not to be useful
//just in order to have something cleaner for the technique we will continue to be using in the following

AUCBandit::AUCBandit(int N_operators, string OutputFile, bool User, double v_Scaling):OperatorSelection(N_operators, OutputFile, User){
	lst_option = new pOption[n_operators];
	//if AUCBandit (\hat{p}==AUC; n_i = times_i in credit window)
	for (unsigned i=0; i < n_operators; i++)
		lst_option[i] = new AUCOption(i, v_Scaling);
}

void AUCBandit::Reset(){
	// re-initialize the Bandit
	best_pchapeau=times=0;
	best_op=0;
	for (unsigned i=0; i < n_operators; i++)
		lst_option[i]->Initialize();
}

double AUCBandit::ApplyReward(unsigned op){
	bool flag;
	double reward=0, reward_op=0;
	times++;
	if(times>n_operators){
		//just check if this operator was chosen based on \hat{p} or on sqrt{n}
		if(best_op==op) exploit++;
		else explore++;

		//applying the reward
		for(unsigned i=0; i<n_operators; i++){
			if (i!=op){
				flag = false;
				reward = credit[0]->getReward(i, false);
			} else{
				flag = true;
				reward = reward_op = GetReward(op);
			}
			lst_option[i]->ApplyReward(reward, credit[0]->getTimesOp(i), flag);
		}
		updateBestOp();
	}else{
		lst_option[op]->setTried(true);
		explore++;
	}
	return reward_op;
}


void AUCBandit::updateBestOp(){
	best_pchapeau=-1; best_op=0;
	double exploit_aux=-1;
	for(unsigned i=0; i<n_operators; i++){
		exploit_aux = lst_option[i]->getExploitation();
		if(exploit_aux > best_pchapeau){
			best_pchapeau = exploit_aux;
			best_op = i;
		}
	}
}

int AUCBandit::OptionNotTried()
{
	int i = (int)(genrand_real1() * n_operators);
	for (unsigned j=0; j < n_operators; j++) {
		int k = (i + j) % n_operators;
		//if (lst_option[k]->getTimes() == 0)
		if (!lst_option[k]->getTried())
			return k;
	}
	printf(" We are in big trouble -- AUCBandit::OptionNotTried\n");
	exit(1);
}

int AUCBandit::SelectOperator(double times_total)
{
	if (times < n_operators){
		return OptionNotTried();
	}else{
		if(times==n_operators){ //delayed reward for the ranking-based after 1x for each operator
			for (unsigned i=0; i < n_operators; i++)
				lst_option[i]->ApplyReward(credit[0]->getReward(i, false), credit[0]->getTimesOp(i), true);
			updateBestOp();
		}

		int op = 0;
		double score_max = 0, vscore = 0;

		for (unsigned i=0; i < n_operators; i++)
		{
			vscore = lst_option[i]->Score(times_total);
			if (vscore > score_max) {
				score_max = vscore;
				op = i;
			}
		}
		return op;
	}
	printf(" We are in big trouble - AUCBandit::SelectOperator\n");
	exit(1);
}

double AUCBandit::getTimesDyn(){
	double timesDyn=0;
	for (unsigned i=0; i < n_operators; i++)
		timesDyn += credit[0]->getTimesOp(i);
	//### check if it is not always equal to |W|
	return timesDyn;
}

int AUCBandit::SelectOperator(){
	return SelectOperator(getTimesDyn());
}

void AUCBandit::PrintSpecificResults(FILE * file){
	if(user){
		//double sum=0;
		double timesDyn = getTimesDyn();
		for (unsigned i=0; i<n_operators; i++){
			//sum += lst_option[i]->getExploitation();
			fprintf(file, " %d %g %g %g ", lst_option[i]->getTimes(), lst_option[i]->getExploration(timesDyn), lst_option[i]->getExploitation(), lst_option[i]->Score(timesDyn));
		}
		//fprintf(file, "\n SUM: %g\n", sum);
	}
}

AUCBandit::~AUCBandit(){
	//delete scaling;
	delete [] lst_option;
}
