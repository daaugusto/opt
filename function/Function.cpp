/*
 * Function.cpp
 *
 *  Created on: 07/02/2012
 *      Author: Eduardo Krempser
 */

#include "Function.h"

#include "../base/Input.h"
#include "../base/Tools.h"
using namespace opt::base;

namespace opt {
namespace function {

	Function::Function() {
		nDimensions  = 2;
		nConstraints = 0;
		knowBest = 0;
		//Define the bounds
		setBounds();

		//Start number of calls
		this->nCalls   = 0;
		//Indicates the max number of calls (-1 -- didn't define)
		this->maxCalls = -1;
	}

	void Function::calc(const vector<double> values, double &fitness, vector<double> &constVal){
		this->nCalls += 1;
	}

	int Function::getNDimensions(){
		return nDimensions;
	}

	void Function::setNDimensions(int dim){
		nDimensions = dim;
	}

	int Function::getNConstraints(){
		return nConstraints;
	}

	double Function::getBest(){
	    return knowBest;
	}

	double Function::convertToRealRange(int index, double val){
		return Tools::convertToRealRange(index, val);
	}

	void Function::convertToRealRange(vector<double> &values) {
		for (int i = 0; i < nDimensions; i++){
			values[i] = Tools::convertToRealRange(i, values[i]);
		}
	}

	double Function::getBoundMax(int index){
		return boundMax[index];
	}

	double Function::getBoundMin(int index){
		return boundMin[index];
	}

	//Protected
	//Define the bounds of the variables
	void Function::setBounds(){
		boundMin.clear();
		boundMax.clear();
		for(int i = 0; i < nDimensions; i++){
			boundMin.push_back(1.0);
			boundMax.push_back(10.0);
		}
	}

	Function::~Function() {
	}

	void Function::initialize(){

	}

	void Function::finalize(){

	}

	void Function::setNCalls(double n){
		this->nCalls = n;
	}

	double Function::getNCalls(){
		return this->nCalls;
	}

	void Function::setMaxCalls(double n){
		this->maxCalls = n;
	}

	double Function::getMaxCalls(){
		return this->maxCalls;
	}

} /* namespace base */
}
