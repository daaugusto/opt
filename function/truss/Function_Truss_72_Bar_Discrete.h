/*
 * Function_Truss_72_Bar_Discrete.h
 *
 *  Created on: 14/11/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_72_BAR_DISCRETE_H_
#define FUNCTION_TRUSS_72_BAR_DISCRETE_H_

#include "Function_Truss_72_Bar.h"

namespace opt {
namespace function {
namespace truss {

class Function_Truss_72_Bar_Discrete : public Function_Truss_72_Bar{
	public:
		Function_Truss_72_Bar_Discrete();
		Function_Truss_72_Bar_Discrete(const Function_Truss_72_Bar_Discrete& orig);
		virtual ~Function_Truss_72_Bar_Discrete();
	};


} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_72_BAR_DISCRETE_H_ */
