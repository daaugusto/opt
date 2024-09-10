#include "BanditAlone.h"

BanditAlone::BanditAlone(int N_operators, string OutputFile, bool User, double v_Scaling, int _normalize, int _W):OperatorSelection(N_operators, OutputFile, User){
	normPchapeau=0;
	if(_normalize>1) normPchapeau=1; //0: no normalization; 1: normalize reward; 2: normalize pchapeau; 3: normalize reward and pchapeau.
	lst_option = new pOption[n_operators];
	if(!_W){//if MAB or DMAB
		for (unsigned i=0; i < n_operators; i++)
			lst_option[i] = new Option(i, v_Scaling);
	}else{//if SlMAB or SlMAB+
		for (unsigned i=0; i < n_operators; i++)
			lst_option[i] = new DynOption(i, v_Scaling, _W);
	}
	best_pchapeau=0;
	//counter=0;
}

void BanditAlone::Reset(){
	// re-initialize the Bandit
	best_pchapeau=times=0;
	best_op=0;
	for (unsigned i=0; i < n_operators; i++)
		lst_option[i]->Initialize();
}

double BanditAlone::ApplyReward(unsigned op){
	//check if this operator was chosen based on \hat{p} or on sqrt{n}
	double reward = GetReward(op);
	times++;
	if(credit[0]->getType()<3 || times>n_operators){
		if(best_op==op) exploit++;
		else explore++;
		lst_option[op]->ApplyReward(reward, times, true);
		updateBestOp(op);
		if(normPchapeau) updateNormPchapeau();
	}else{
		lst_option[op]->setTried(true);
		explore++;
	}

	/*cout << times << " " << best_op << " " << best_pchapeau;
	for (unsigned i=0; i<n_operators; i++)
		cout << " " << lst_option[i]->getExploitation();
	cout << endl;*/

	return reward;
}

void BanditAlone::updateBestOp(unsigned op){
	double exploit_op=lst_option[op]->getExploitation();
	//if the one that was the best has a lower \hat p, check between all; or if the previous best changed
	if((best_op==op && exploit_op < best_pchapeau) || (best_op >= 0 && lst_option[best_op]->getExploitation() != best_pchapeau)){
		best_pchapeau = -1; best_op = 0;
		double exploit_aux=-1;
		for(unsigned i=0; i<n_operators; i++){
			exploit_aux = lst_option[i]->getExploitation();
			if(exploit_aux > best_pchapeau){
				best_pchapeau = exploit_aux;
				best_op = i;
			}
		}
	} else if(exploit_op >= best_pchapeau){ //else if it is best than the previous best
		best_op=op;
		best_pchapeau = exploit_op;
	}
}

void BanditAlone::updateNormPchapeau(){
	double divide=1.0;
	if(best_pchapeau > 0) divide=best_pchapeau;
	if(divide != lst_option[0]->getNormPchapeau())
		for (unsigned i=0; i < n_operators; i++)
			lst_option[i]->setNormPchapeau(divide);
}

int BanditAlone::OptionNotTried()
{
	int i = (int)(genrand_real1() * n_operators);
	for (unsigned j=0; j < n_operators; j++) {
		int k = (i + j) % n_operators;
		//if (lst_option[k]->getTimes() == 0)
		if (!lst_option[k]->getTried())
			return k;
	}
	printf(" We are in big trouble -  BanditAlone::OptionNotTried\n");
	exit(1);
}

int BanditAlone::SelectOperator(double times_total)
{
	if (times < n_operators){
		//cout << 1 << endl;
		return OptionNotTried();
	}else{
		/*if(credit[0]->getType()>=3 && !credit[0]->checkFullQueue()){
			counter++;
			return (int) (rng.uniform() * n_operators);
		}else{*/

		//delayed reward for the ranking-based after 1x for each operator
		if(credit[0]->getType()>=3 && times==n_operators){
			//cout << 2 << endl;
			for (unsigned i=0; i < n_operators; i++){
				lst_option[i]->ApplyReward(credit[0]->getReward(i, false), times, true);
				updateBestOp(i);
			}
			if(normPchapeau) updateNormPchapeau();
		}//else cout << 3 << endl;

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
		//}
	}
	printf(" We are in big trouble - BanditAlone::SelectOperator\n");
	exit(1);
}

int BanditAlone::SelectOperator(){
	return SelectOperator((double)times);
}

void BanditAlone::PrintSpecificResults(FILE * file){
	if(user)
		for (unsigned i=0; i<n_operators; i++)
			fprintf(file, "%d %g %g ", lst_option[i]->getTimes(), lst_option[i]->getExploration(times), lst_option[i]->getExploitation());
}

BanditAlone::~BanditAlone(){
	//delete scaling;
	delete [] lst_option;
}
