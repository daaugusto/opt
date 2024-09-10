#ifndef BANDITALONE_H_
#define BANDITALONE_H_

#include "OperatorSelection.h"
#include "mab/DynOption.h"

class BanditAlone : public OperatorSelection{
public:
	BanditAlone(int N_operators, string OutputFile, bool User, double v_Scaling, int _normalize=0, int _W=0);
	virtual double ApplyReward(unsigned op);
	void updateBestOp(unsigned op);
	void updateNormPchapeau();
	int OptionNotTried();
	int SelectOperator(double times_total);
	virtual int SelectOperator();
	virtual void Reset();
	virtual void PrintSpecificResults(FILE * file);
	virtual ~BanditAlone();

protected:
	pOption *lst_option;
	bool normPchapeau;
	double best_pchapeau;
	//int counter;
};

#endif /* BANDITALONE_H_ */
