/*
 * Function_Truss_10_Bar.cpp
 *
 *  Created on: 18/05/2012
 *      Author: krempser
 */

#include "Function_Truss_10_Bar.h"

namespace opt {
namespace function {
namespace truss {

Function_Truss_10_Bar::Function_Truss_10_Bar(): Truss_Bar_Structure_Static_Problem(10, NULL, 280000, 1, 18, 10, 0.1, 25000, 2, "input10.dat", 0.1, 40) {

}

Function_Truss_10_Bar::Function_Truss_10_Bar(const Function_Truss_10_Bar& orig): Truss_Bar_Structure_Static_Problem(orig) {

}

Function_Truss_10_Bar::~Function_Truss_10_Bar() {

}

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
