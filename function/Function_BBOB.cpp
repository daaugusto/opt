/*
 * Function_BBOB.cpp
 *
 *  Created on: 16/02/2012
 *      Author: Eduardo Krempser
 */

#include "Function_BBOB.h"

namespace opt {
namespace function {


	Function_BBOB::Function_BBOB(int id){
		//The id to BBOB will be values between 1001 and 1130
		//Convert to original id
		if (id > 1000){
			idFunction = id - 1000;
		} else {
			idFunction = id;
		}

		nDimensions   = Input::dim;
		nConstraints  = getNConstH() + getNConstG();

		//Set the max number of evaluations
		this->maxCalls = 100000. * nDimensions;

		//Fixed the population size as 10*number of dimensions
		//Input::popSize = 10*nDimensions;
		Input::maxGen  = this->maxCalls/Input::popSize;

		//Define the bounds
		setBounds();
	}

	void Function_BBOB::initialize(){
		/* retrieve all default parameters of BBOB calls  */
		ParamStruct params = fgeneric_getDefaultPARAMS();

		params.DIM = nDimensions;
		params.funcId = idFunction;
		params.instanceId = Input::idTest;

		strcpy(params.dataPath, Input::path.c_str());
		strcpy(params.algName, Input::algname.c_str());
		strcpy(params.comments, "PUT MORE DETAILED INFORMATION, PARAMETER SETTINGS ETC");
		/* call the BBOB initialization */
		fgeneric_initialize(params);
	}

	void Function_BBOB::finalize(){
		fgeneric_finalize();
	}

	void Function_BBOB::calc(const vector<double> values, double &fitness, vector<double> &constVal){
		Function::calc(values, fitness, constVal);

		//Set values
		double *v = new double[nDimensions];
		for (int jOff = 0; jOff < nDimensions; jOff++)
			v[jOff] = convertToRealRange(jOff, values[jOff]);
		fitness = fgeneric_evaluate(v);
		delete [] v;
	}


	/*
	double Function_BBOB::convertToRealRange(int index, double val){
		return ((val)*(boundMax[index] - boundMin[index])) + boundMin[index];
	}
	*/
	double Function_BBOB::getBoundMax(int index){
			return boundMax[index];
		}

	double Function_BBOB::getBoundMin(int index){
		return boundMin[index];
	}


	//Define the bounds of the variables
	void Function_BBOB::setBounds(){
		boundMin.clear();
		boundMax.clear();
		for(int variable = 0; variable < getNDimensions(); variable++){
					boundMin.push_back(-5.0); //Segundo o código do Álvaro
					boundMax.push_back(5.0);
		}
	}


	//Internal methods
	int Function_BBOB::getN(){
		return nDimensions;
	}

	int Function_BBOB::getNConstG(){
	  return 0;
	}

	int Function_BBOB::getNConstH(){
	  return 0;
	}

	//Best known values
	double Function_BBOB::getBest(){
		return fgeneric_ftarget();
	}

} /* namespace hybridAos */
} /* namespace opt */
