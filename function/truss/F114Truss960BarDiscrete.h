/*
 * File:   F114Truss960BarDiscrete.h
 * Author: Heder S. Bernardino
 *
 * Created on October 24, 2014, 14:00 PM
 */

#ifndef _F114TRUSS960BARDISCRETE_H
#define	_F114TRUSS960BARDISCRETE_H

#include "F113Truss960Bar.h"

namespace opt {
namespace function {
namespace truss {

    class F114Truss960BarDiscrete: public F113Truss960Bar {
    public:
        F114Truss960BarDiscrete();
        F114Truss960BarDiscrete(const F114Truss960BarDiscrete& orig);
        virtual ~F114Truss960BarDiscrete();
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

#endif	/* _F114TRUSS960BARDISCRETE_H */

