/*
 * Function_Truss_25_Bar_Discrete.h
 *
 *  Created on: 21/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_25_BAR_DISCRETE_H_
#define FUNCTION_TRUSS_25_BAR_DISCRETE_H_

#include "Function_Truss_25_Bar.h"

namespace opt {
namespace function {
namespace truss {

class Function_Truss_25_Bar_Discrete : public Function_Truss_25_Bar{
public:
	Function_Truss_25_Bar_Discrete();
	Function_Truss_25_Bar_Discrete(Function_Truss_25_Bar_Discrete& orig);
	virtual ~Function_Truss_25_Bar_Discrete();
};

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_25_BAR_DISCRETE_H_ */
