/*
 * Function_Truss_10_Bar.h
 *
 *  Created on: 18/05/2012
 *      Author: krempser
 */

#ifndef FUNCTION_TRUSS_10_BAR_H_
#define FUNCTION_TRUSS_10_BAR_H_

#include "Truss_Bar_Structure_Static_Problem.h"

namespace opt {
namespace function {
namespace truss {

	class Function_Truss_10_Bar : public Truss_Bar_Structure_Static_Problem{
	public:
		Function_Truss_10_Bar();
		Function_Truss_10_Bar(const Function_Truss_10_Bar& orig);
		virtual ~Function_Truss_10_Bar();
	};

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_TRUSS_10_BAR_H_ */
