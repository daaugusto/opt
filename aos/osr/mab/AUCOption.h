
#ifndef AUCOPTION_H_
#define AUCOPTION_H_

#include "Option.h"


class AUCOption : public Option{
public:
	AUCOption(int Num, double v_Scaling);
	void ApplyReward(double reward, double _times, bool used);
};

#endif /* AUCOPTION_H_ */
