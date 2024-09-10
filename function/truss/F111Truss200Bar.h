/*
 * File:   F111Truss200Bar.h
 * Author: Heder S. Bernardino
 *
 * Created on October 17, 2014, 16:00
 */

#ifndef _F111TRUSS200BAR_H
#define	_F111TRUSS200BAR_H

#include "Truss_Bar_Structure_Static_Problem.h"

namespace opt {
namespace function {
namespace truss {

    class F111Truss200Bar: public Truss_Bar_Structure_Static_Problem {
    public:
        F111Truss200Bar();
        F111Truss200Bar(const F111Truss200Bar& orig);
        virtual ~F111Truss200Bar();
//		virtual void evaluation(void* vector, void* values);
	protected:
		virtual void fillAreasAux(double* x);
    private:
    };

} /* namespace truss */
} /* namespace function */
} /* namespace opt */

#endif	/* _F111TRUSS200BAR_H */

