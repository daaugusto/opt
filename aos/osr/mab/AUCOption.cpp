

#include "AUCOption.h"


AUCOption::AUCOption(int Num, double v_Scaling) : Option(Num, v_Scaling){	}

void AUCOption::ApplyReward(double reward, double _times, bool used){
	//cout << num << "\t" << reward << "\t" << timeNow << "\t" << used << endl;
	expectation = reward; //\hat{p}==AUC evaluation
	times = (int)_times; //timeNow==number of times operator appears in the AUC window
	if(used) tried=true;
}

