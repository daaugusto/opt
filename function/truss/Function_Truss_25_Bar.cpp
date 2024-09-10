/*
 * Function_Truss_25_Bar.cpp
 *
 *  Created on: 21/05/2012
 *      Author: krempser
 */

#include "Function_Truss_25_Bar.h"

namespace opt {
namespace function {
namespace truss {

Function_Truss_25_Bar::Function_Truss_25_Bar(): Truss_Bar_Structure_Static_Problem(8, NULL, 240000, 1, 29, 25,  0.1, 40000, 0.35, "input25.dat", 0.1, 3.4), grouping(NULL) {

}

Function_Truss_25_Bar::Function_Truss_25_Bar(Function_Truss_25_Bar& orig): Truss_Bar_Structure_Static_Problem(orig), grouping(NULL) {

}

Function_Truss_25_Bar::~Function_Truss_25_Bar(){
	 delete[] this->grouping;
}

int* const Function_Truss_25_Bar::getGrouping () {
	if (this->grouping==NULL) {
		this->grouping = new int[ this->getDimension() ];
		this->grouping[0] = 1;
		this->grouping[1] = 5;
		this->grouping[2] = 9;
		this->grouping[3] = 11;
		this->grouping[4] = 13;
		this->grouping[5] = 17;
		this->grouping[6] = 21;
		this->grouping[7] = 25;
	}

	return this->grouping;
}

void Function_Truss_25_Bar::evaluation(void* vector, void* values) {

	Truss_Bar_Structure_Static_Problem::evaluation(vector, values);

	double* val = (double*) values;

	int i = this->getNLCase()*this->getNumberOfBars();
	val[i+1+2] = fabs(this->getStressDisplacementAux()[i+3])/this->getDisplacementConstraint() - 1;
	val[i+1+3] = fabs(this->getStressDisplacementAux()[i+4])/this->getDisplacementConstraint() - 1;

}

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
