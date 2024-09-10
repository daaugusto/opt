/*
 * File:   F114Truss960BarDiscrete.cpp
 * Author: Heder S. Bernardino
 *
 * Created on October 24, 2014, 14:00 PM
 */

#include "F114Truss960BarDiscrete.h"
#include <iostream>

using namespace std;

namespace opt {
namespace function {
namespace truss {

    F114Truss960BarDiscrete::F114Truss960BarDiscrete(): F113Truss960Bar() {
        double** b = (double**)this->bounds;
        for (int i = 0; i < dimension; i++) {
            b[i][0] = 0.0;
            b[i][1] = F114Truss960BarDiscrete::DATA_TABLE_LENGTH;
        }
        this->dataTable = new double[F114Truss960BarDiscrete::DATA_TABLE_LENGTH];
        this->dataTable[0] = 1;
        for(int i=1; i<F114Truss960BarDiscrete::DATA_TABLE_LENGTH; i++) {
            this->dataTable[i] = this->dataTable[i-1] + 1.0;
			//cout << this->dataTable[i] << endl;
        }
		this->discreteX = new double[ this->dimension ];
    }

    F114Truss960BarDiscrete::F114Truss960BarDiscrete(const F114Truss960BarDiscrete& orig): F113Truss960Bar(orig) {

    }

    F114Truss960BarDiscrete::~F114Truss960BarDiscrete() {
        delete[] this->dataTable;
		delete[] this->discreteX;
    }

    void F114Truss960BarDiscrete::fillAreasAux(double* x) {

		int index;
		for (int i = 0; i < this->dimension; i++) {
			index = (int) x[i];
			discreteX[i] = index < F114Truss960BarDiscrete::DATA_TABLE_LENGTH? this->dataTable[ index ]: this->dataTable[ F114Truss960BarDiscrete::DATA_TABLE_LENGTH-1 ];
			//cout << discreteX[i] << endl;
		}
		F113Truss960Bar::fillAreasAux(discreteX);
	}

}
}
}
