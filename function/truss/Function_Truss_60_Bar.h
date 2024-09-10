/*
 * Function_Truss_60_Bar.h
 *
 *  Created on: 21/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_60_BAR_H_
#define FUNCTION_TRUSS_60_BAR_H_

#include "Truss_Bar_Structure_Static_Problem.h"

namespace opt {
namespace function {
namespace truss {

class Function_Truss_60_Bar  : public Truss_Bar_Structure_Static_Problem{
public:
	Function_Truss_60_Bar();
	Function_Truss_60_Bar(const Function_Truss_60_Bar& orig);

	virtual void evaluation(void* vector, void* values);

	virtual ~Function_Truss_60_Bar();

protected:
    virtual int* const getGrouping();
	virtual void fillAreasAux(double* x);

private:
    int* grouping;
	double displacementConstraint2;
	double displacementConstraint3;
};

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_60_BAR_H_ */
