#ifndef BANDITRESTART_H_
#define BANDITRESTART_H_

#include "BanditAlone.h"
#include "mab/AdaptivePH.h"

class BanditRestart : public BanditAlone {
public:
	BanditRestart(int N_operators, string OutputFile, bool User, double v_Scaling, double v_Gamma, int _normalize=0);
	double ApplyReward(unsigned op);
	void Reset();
	void PrintSpecificResults(FILE * file);
	bool getRestart();
	~BanditRestart();

protected:
	bool change;
	AdaptivePH * adaptPH;
};

#endif /* BANDITRESTART_H_ */
