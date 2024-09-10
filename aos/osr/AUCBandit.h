#ifndef AUCBANDIT_H_
#define AUCBANDIT_H_

#include "OperatorSelection.h"
#include "mab/AUCOption.h"

class AUCBandit : public OperatorSelection{
public:
	AUCBandit(int N_operators, string OutputFile, bool User, double v_Scaling);
	virtual double ApplyReward(unsigned op);
	void updateBestOp();
	int OptionNotTried();
	int SelectOperator(double times_total);
	double getTimesDyn();
	virtual int SelectOperator();
	void Reset();
	virtual void PrintSpecificResults(FILE * file);
	virtual ~AUCBandit();

protected:
	pOption *lst_option;
	int W;
	double best_pchapeau;
	int updateAll; //0-update just applied; 1-update all; 2-update all, except when exploring
};

#endif /* AUCBANDIT_H_ */
