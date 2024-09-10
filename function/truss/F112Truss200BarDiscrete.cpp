/*
 * File:   F112Truss200BarDiscrete.cpp
 * Author: Heder S. Bernardino
 *
 * Created on October 17, 2014, 16:00
 */

#include "F112Truss200BarDiscrete.h"

namespace opt {
namespace function {
namespace truss {

    F112Truss200BarDiscrete::F112Truss200BarDiscrete(): F111Truss200Bar() {
        double** b = (double**)this->bounds;
        for (int i = 0; i < dimension; i++) {
            b[i][0] = 0.0;
            b[i][1] = F112Truss200BarDiscrete::DATA_TABLE_LENGTH;
        }
        this->dataTable = new double[F112Truss200BarDiscrete::DATA_TABLE_LENGTH];
        this->dataTable[0] = 1;
        for(int i=1; i<F112Truss200BarDiscrete::DATA_TABLE_LENGTH; i++) {
            this->dataTable[i] = this->dataTable[i-1] + 1.0;
        }
		this->discreteX = new double[ this->dimension ];
    }

    F112Truss200BarDiscrete::F112Truss200BarDiscrete(const F112Truss200BarDiscrete& orig): F111Truss200Bar(orig) {

    }

    F112Truss200BarDiscrete::~F112Truss200BarDiscrete() {
        delete[] this->dataTable;
		delete[] this->discreteX;
    }

    void F112Truss200BarDiscrete::fillAreasAux(double* x) {

		int index;
		for (int i = 0; i < this->dimension; i++) {
			index = (int) x[i];
			discreteX[i] = index < F112Truss200BarDiscrete::DATA_TABLE_LENGTH? this->dataTable[ index ]: this->dataTable[ F112Truss200BarDiscrete::DATA_TABLE_LENGTH-1 ];
		}
		F111Truss200Bar::fillAreasAux(discreteX);
	}

}
}
}
