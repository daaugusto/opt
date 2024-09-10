/*
 * File:   F112Truss200BarDiscrete.h
 * Author: Heder S. Bernardino
 *
 * Created on October 17, 2014, 16:00
 */

#ifndef _F112TRUSS200BARDISCRETE_H
#define	_F112TRUSS200BARDISCRETE_H

#include "F111Truss200Bar.h"

namespace opt {
namespace function {
namespace truss {

    class F112Truss200BarDiscrete: public F111Truss200Bar {
    public:
        F112Truss200BarDiscrete();
        F112Truss200BarDiscrete(const F112Truss200BarDiscrete& orig);
        virtual ~F112Truss200BarDiscrete();
    protected:
		virtual void fillAreasAux(double* x);
    private:
        static const int DATA_TABLE_LENGTH = 30;
        double* dataTable;
		double* discreteX;

    };

} /* namespace truss */
} /* namespace function */
} /* namespace opt */

#endif	/* _F112TRUSS200BARDISCRETE_H */

