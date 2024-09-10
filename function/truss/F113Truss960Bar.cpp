/*
 * File:   F113Truss960Bar.cpp
 * Author: Heder S. Bernardino
 *
 * Created on October 24, 2014, 14:00 PM
 */

#include <cmath>
#include <memory.h>
#include "F113Truss960Bar.h"

using namespace std;

namespace opt {
namespace function {
namespace truss {

    F113Truss960Bar::F113Truss960Bar(): Truss_Bar_Structure_Static_Problem(960, NULL, 10000, 1, 759, 960, 0.000283, 0, 4.16, "input960.dat", 1, 30) {
		//maximum displacement of the reference = 4.16
		//maximum displacement suggested by Lemonge = 1.5 X 4.16 = 6.24 in
		//other possibility = 5

    }

    F113Truss960Bar::F113Truss960Bar(const F113Truss960Bar& orig): Truss_Bar_Structure_Static_Problem(orig) {

    }

    F113Truss960Bar::~F113Truss960Bar() {

    }

	void F113Truss960Bar::evaluation(void* vector, void* values) {

		double* x = (double*) vector;
		this->fillAreasAux(x);

        double* val = (double*) values;
        double objectiveFunctionValue = 0;

        this->getSimulator()->stap(this->getAreasAux(), &objectiveFunctionValue, this->getStressDisplacementAux());
        val[0] = objectiveFunctionValue;

		int stress = this->getNLCase()*this->getNumberOfBars();

		for(int i=0; i< this->numberConstraints; i++) {
            val[i+1] = fabs( this->getStressDisplacementAux()[stress+i] )/this->getDisplacementConstraint() - 1;
        }

    }

}
}
}
