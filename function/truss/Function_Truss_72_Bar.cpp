/*
 * Function_Truss_72_Bar.cpp
 *
 *  Created on: 21/05/2012
 *      Author: krempser
 */

#include "Function_Truss_72_Bar.h"

namespace opt {
namespace function {
namespace truss {

Function_Truss_72_Bar::Function_Truss_72_Bar(): Truss_Bar_Structure_Static_Problem(16, NULL, 35000, 1, 168, 72, 0.1, 25000, 0.25, "input72.dat", 0.1, 2.5), grouping(NULL) {

}

Function_Truss_72_Bar::Function_Truss_72_Bar(const Function_Truss_72_Bar& orig): Truss_Bar_Structure_Static_Problem(orig), grouping(NULL) {

}

Function_Truss_72_Bar::~Function_Truss_72_Bar() {
	 delete[] this->grouping;
}

int* const Function_Truss_72_Bar::getGrouping () {
	if (this->grouping==NULL) {
		this->grouping = new int[ this->getNumberOfBars() ];
		this->grouping[0] = 4;
		this->grouping[1] = 12;
		this->grouping[2] = 16;
		this->grouping[3] = 18;
		this->grouping[4] = 22;
		this->grouping[5] = 30;
		this->grouping[6] = 34;
		this->grouping[7] = 36;
		this->grouping[8] = 40;
		this->grouping[9] = 48;
		this->grouping[10] = 52;
		this->grouping[11] = 54;
		this->grouping[12] = 58;
		this->grouping[13] = 66;
		this->grouping[14] = 70;
		this->grouping[15] = 72;
	}
	return this->grouping;
}

void Function_Truss_72_Bar::evaluation(void* vector, void* values) {

	Truss_Bar_Structure_Static_Problem::evaluation(vector, values);

	double* val = (double*) values;

	int i=this->getNLCase()*this->getNumberOfBars();
	int max = i+12;

	for(; i< max; i++) {
		val[i+1+12] = fabs(this->getStressDisplacementAux()[i+this->getNumberOfDisplacements()])/this->getDisplacementConstraint() - 1;
	}

}

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
