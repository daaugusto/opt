
#ifndef OPTION_H_
#define OPTION_H_


#include <math.h>
#include "stdio.h"
#include "stdlib.h"

class Option{
public:
	Option(int Num, double v_Scaling);
	double Score(double nb_total);
	virtual void ApplyReward(double reward, double timeNow, bool used);
	void Initialize();
	virtual ~Option();

	void setNormPchapeau(double _divide);
	double getNormPchapeau();
	virtual double getExploration(double nb_total);
	double getExploitation();
	double getPchapeau();
	void setTried(bool tried_);
	bool getTried();
	int getTimes();
	void setTimes(int _times);
	virtual double getTimesDyn();
	virtual void setTimesDyn(double _times);

protected:
	int times;
	double expectation;
	double v_scaling;
	int num;
	double dividePchapeau;
	bool tried;
};

typedef Option *pOption;


#endif /* OPTION_H_ */
