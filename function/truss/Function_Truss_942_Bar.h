/*
 * Function_Truss_942_Bar.h
 *
 *  Created on: 21/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_942_BAR_H_
#define FUNCTION_TRUSS_942_BAR_H_

#include "Truss_Bar_Structure_Static_Problem.h"

namespace opt {
namespace function {
namespace truss {

class Function_Truss_942_Bar  : public Truss_Bar_Structure_Static_Problem{
public:
	Function_Truss_942_Bar();
	Function_Truss_942_Bar(const Function_Truss_942_Bar& orig);
	virtual ~Function_Truss_942_Bar();

protected:
        virtual int* const getGrouping();
		virtual void fillAreasAux(double* x);
private:
	int* grouping;
};

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_942_BAR_H_ */
