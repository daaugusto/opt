/*
 * Function_Truss_942_Bar_Discrete.h
 *
 *  Created on: 17/11/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_942_BAR_DISCRETE_H_
#define FUNCTION_TRUSS_942_BAR_DISCRETE_H_

#include "Function_Truss_942_Bar.h"

namespace opt {
namespace function {
namespace truss {

class Function_Truss_942_Bar_Discrete : public Function_Truss_942_Bar{
	public:
		Function_Truss_942_Bar_Discrete();
		Function_Truss_942_Bar_Discrete(const Function_Truss_942_Bar_Discrete& orig);
		virtual ~Function_Truss_942_Bar_Discrete();
	};

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_942_BAR_DISCRETE_H_ */
