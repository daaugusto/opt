
#include "Option.h"


Option::Option(int Num, double v_Scaling){
	v_scaling = v_Scaling;
	num = Num;
	dividePchapeau=1.0;
	Initialize();
}

double Option::Score(double nb_total){
	return (getExploitation() + getExploration(nb_total));
	//return (expectation + ( v_scaling * sqrt( 2 * log(nb_total) / times) ));
}

void Option::setNormPchapeau(double _divide){
	dividePchapeau=_divide;
}

double Option::getNormPchapeau(){
	return dividePchapeau;
}

double Option::getExploration(double nb_total){
	//cout << nb_total << " " << times << endl;
	return (v_scaling * sqrt( 2.0 * log((double)nb_total) / (double)times));
}

double Option::getExploitation(){
	return (double)expectation/(double)dividePchapeau;
}

double Option::getPchapeau(){
	return expectation;
}

void Option::ApplyReward(double reward, double timeNow, bool used){
	//cout << "Applying reward " << reward << " to operator " << num << endl;
	// just updates the average
	expectation = ((double)times * expectation + reward)/((double)times + 1);
	times++;
	tried=true;

}

void Option::setTried(bool tried_){
	tried=tried_;
}
bool Option::getTried(){
	return tried;
}


void Option::Initialize(){
	expectation = 0.0;
	times = 0;
	tried=false;
}

int Option::getTimes(){
	return times;
}

void Option::setTimes(int _times){
	times = _times;
}

double Option::getTimesDyn(){
	return 0;
}

void Option::setTimesDyn(double _times){}

Option::~Option(){}
