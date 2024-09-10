/*
 * File:   F113Truss960Bar.h
 * Author: Heder S. Bernardino
 *
 * Created on October 24, 2014, 14:00 PM
 */

#ifndef _F113TRUSS960BAR_H
#define	_F113TRUSS960BAR_H

#include "Truss_Bar_Structure_Static_Problem.h"

namespace opt {
namespace function {
namespace truss {

    class F113Truss960Bar: public Truss_Bar_Structure_Static_Problem {
    public:
        F113Truss960Bar();
        F113Truss960Bar(const F113Truss960Bar& orig);
        virtual ~F113Truss960Bar();
		virtual void evaluation(void* vector, void* values);
    };

} /* namespace truss */
} /* namespace function */
} /* namespace opt */

#endif	/* _F113TRUSS960BAR_H */

