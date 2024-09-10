/*
 * Function_Truss_72_Bar.h
 *
 *  Created on: 21/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_72_BAR_H_
#define FUNCTION_TRUSS_72_BAR_H_

#include "Truss_Bar_Structure_Static_Problem.h"

namespace opt {
namespace function {
namespace truss {

class Function_Truss_72_Bar  : public Truss_Bar_Structure_Static_Problem{
public:
	Function_Truss_72_Bar();
	Function_Truss_72_Bar(const Function_Truss_72_Bar& orig);

	virtual void evaluation(void* vector, void* values);

	virtual ~Function_Truss_72_Bar();

protected:
    virtual int* const getGrouping();

private:
    int* grouping;
};

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_72_BAR_H_ */
