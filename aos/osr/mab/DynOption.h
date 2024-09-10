

#ifndef DYNOPTION_H_
#define DYNOPTION_H_

#include "Option.h"


class DynOption : public Option{
public:
	DynOption(int Num, double v_Scaling, int _W) : Option(Num, v_Scaling){
		W=_W;
		timeLast=0;
		timesDyn=1;
	}

	virtual void ApplyReward(double reward, double timeNow, bool used){
		//cout << "APPLICATION Op: " << num << "; Rewd: " << reward << endl;
		expectation = expectation * (W/(W+(timeNow - timeLast))) + (1/(timesDyn+1)) * reward;
		timesDyn = timesDyn * ( W/(W + (timeNow - timeLast)) + 1/(timesDyn+1));
		//cout << timeNow << " " << num << " " << timeLast << " " << reward << " " << expectation << " " << timesDyn << " " << W << " " << used << endl;
		if(used){
			timeLast = timeNow;
			times++;
			tried=true;
		}
	}

	double getExploration(double nb_total){
		return (v_scaling * sqrt( 2.0 * log(nb_total) / timesDyn));
	}

	double getTimesDyn(){
		return timesDyn;
	}

	virtual ~DynOption(){

	}
protected:
	double W;
	double timeLast;
	double timesDyn;
};

//typedef DynOption *pDynOption;


#endif /* DYNOPTION_H_ */
