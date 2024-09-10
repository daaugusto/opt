/*
 * File:   F111Truss200Bar.cpp
 * Author: Heder S. Bernardino
 *
 * Created on October 17, 2014, 16:00
 */

#include <cmath>
#include <memory.h>
#include "F111Truss200Bar.h"

using namespace std;

namespace opt {
namespace function {
namespace truss {

    F111Truss200Bar::F111Truss200Bar(): Truss_Bar_Structure_Static_Problem(29, NULL, 10000, 1, 600, 200, 0.283, 10000, 0.0, "input200.dat", 0.1, 30.0) {

    }

    F111Truss200Bar::F111Truss200Bar(const F111Truss200Bar& orig): Truss_Bar_Structure_Static_Problem(orig) {

    }

    F111Truss200Bar::~F111Truss200Bar() {

    }

	/*void F111Truss200Bar::evaluation(void* vector, void* values) {

		TrussBarStructureStaticProblem::evaluation(vector, values);

        double* val = (double*) values;

		int i=this->getNLCase()*this->getNumberOfBars();
		int max = i+12;

		for(; i< max; i++) {
            val[i+1+12] = abs( ( this->getStressDisplacementAux()[ i+this->getNumberOfDisplacements() ] ) ) / this->getDisplacementConstraint() - 1;
        }

    }*/

    void F111Truss200Bar::fillAreasAux(double* x) {

		this->getAreasAux()[1 - 1] = x[ 1 - 1 ];
       this->getAreasAux()[2 - 1] = x[ 1 - 1 ];
       this->getAreasAux()[3 - 1] = x[ 1 - 1 ];
       this->getAreasAux()[4 - 1] = x[ 1 - 1 ];

       this->getAreasAux()[5 - 1] = x[ 2 - 1 ];
       this->getAreasAux()[8 - 1] = x[ 2 - 1 ];
       this->getAreasAux()[11 - 1]= x[ 2 - 1 ];
       this->getAreasAux()[14 - 1]= x[ 2 - 1 ];
       this->getAreasAux()[17 - 1]= x[ 2 - 1 ];

       this->getAreasAux()[19 - 1]= x[ 3 - 1 ];
       this->getAreasAux()[20 - 1]= x[ 3 - 1 ];
       this->getAreasAux()[21 - 1]= x[ 3 - 1 ];
       this->getAreasAux()[22 - 1]= x[ 3 - 1 ];
       this->getAreasAux()[23 - 1]= x[ 3 - 1 ];
       this->getAreasAux()[24 - 1]= x[ 3 - 1 ];

       this->getAreasAux()[18 - 1]= x[ 4 - 1 ];
       this->getAreasAux()[25 - 1]= x[ 4 - 1 ];
       this->getAreasAux()[56 - 1]= x[ 4 - 1 ];
       this->getAreasAux()[63 - 1]= x[ 4 - 1 ];
       this->getAreasAux()[94 - 1]= x[ 4 - 1 ];
       this->getAreasAux()[101 - 1] = x[ 4 - 1 ];
       this->getAreasAux()[132 - 1] = x[ 4 - 1 ];
       this->getAreasAux()[139 - 1] = x[ 4 - 1 ];
       this->getAreasAux()[170 - 1] = x[ 4 - 1 ];
       this->getAreasAux()[177 - 1] = x[ 4 - 1 ];

       this->getAreasAux()[26 - 1]= x[ 5 - 1 ];
       this->getAreasAux()[29 - 1]= x[ 5 - 1 ];
       this->getAreasAux()[32 - 1]= x[ 5 - 1 ];
       this->getAreasAux()[35 - 1]= x[ 5 - 1 ];
       this->getAreasAux()[38 - 1]= x[ 5 - 1 ];

       this->getAreasAux()[6 - 1] = x[ 6 - 1 ];
       this->getAreasAux()[7 - 1] = x[ 6 - 1 ];
       this->getAreasAux()[9 - 1] = x[ 6 - 1 ];
       this->getAreasAux()[10 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[12 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[13 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[15 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[16 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[27 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[28 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[30 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[31 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[33 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[34 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[36 - 1]= x[ 6 - 1 ];
       this->getAreasAux()[37 - 1]= x[ 6 - 1 ];

       this->getAreasAux()[39 - 1]= x[ 7 - 1 ];
       this->getAreasAux()[40 - 1]= x[ 7 - 1 ];
       this->getAreasAux()[41 - 1]= x[ 7 - 1 ];
       this->getAreasAux()[42 - 1]= x[ 7 - 1 ];

       this->getAreasAux()[43 - 1]= x[ 8 - 1 ];
       this->getAreasAux()[46 - 1]= x[ 8 - 1 ];
       this->getAreasAux()[49 - 1]= x[ 8 - 1 ];
       this->getAreasAux()[52 - 1]= x[ 8 - 1 ];
       this->getAreasAux()[55 - 1]= x[ 8 - 1 ];

       this->getAreasAux()[57 - 1]= x[ 9 - 1 ];
       this->getAreasAux()[58 - 1]= x[ 9 - 1 ];
       this->getAreasAux()[59 - 1]= x[ 9 - 1 ];
       this->getAreasAux()[60 - 1]= x[ 9 - 1 ];
       this->getAreasAux()[61 - 1]= x[ 9 - 1 ];
       this->getAreasAux()[62 - 1]= x[ 9 - 1 ];

       this->getAreasAux()[64 - 1]= x[ 10 - 1 ];
       this->getAreasAux()[67 - 1]= x[ 10 - 1 ];
       this->getAreasAux()[70 - 1]= x[ 10 - 1 ];
       this->getAreasAux()[73 - 1]= x[ 10 - 1 ];
       this->getAreasAux()[76 - 1]= x[ 10 - 1 ];

       this->getAreasAux()[44 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[45 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[47 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[48 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[50 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[51 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[53 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[54 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[65 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[66 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[68 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[69 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[71 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[72 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[74 - 1]= x[ 11 - 1 ];
       this->getAreasAux()[75 - 1]= x[ 11 - 1 ];

       this->getAreasAux()[77 - 1]= x[ 12 - 1 ];
       this->getAreasAux()[78 - 1]= x[ 12 - 1 ];
       this->getAreasAux()[79 - 1]= x[ 12 - 1 ];
       this->getAreasAux()[80 - 1]= x[ 12 - 1 ];

       this->getAreasAux()[81 - 1]= x[ 13 - 1 ];
       this->getAreasAux()[84 - 1]= x[ 13 - 1 ];
       this->getAreasAux()[87 - 1]= x[ 13 - 1 ];
       this->getAreasAux()[90 - 1]= x[ 13 - 1 ];
       this->getAreasAux()[93 - 1]= x[ 13 - 1 ];

       this->getAreasAux()[95 - 1]= x[ 14 - 1 ];
       this->getAreasAux()[96 - 1]= x[ 14 - 1 ];
       this->getAreasAux()[97 - 1]= x[ 14 - 1 ];
       this->getAreasAux()[98 - 1]= x[ 14 - 1 ];
       this->getAreasAux()[99 - 1]= x[ 14 - 1 ];
       this->getAreasAux()[100 - 1] = x[ 14 - 1 ];

       this->getAreasAux()[102 - 1] = x[ 15 - 1 ];
       this->getAreasAux()[105 - 1] = x[ 15 - 1 ];
       this->getAreasAux()[108 - 1] = x[ 15 - 1 ];
       this->getAreasAux()[111 - 1] = x[ 15 - 1 ];
       this->getAreasAux()[114 - 1] = x[ 15 - 1 ];

       this->getAreasAux()[82 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[83 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[85 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[86 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[88 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[89 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[91 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[92 - 1]= x[ 16 - 1 ];
       this->getAreasAux()[103 - 1] = x[ 16 - 1 ];
       this->getAreasAux()[104 - 1] = x[ 16 - 1 ];
       this->getAreasAux()[106 - 1] = x[ 16 - 1 ];
       this->getAreasAux()[107 - 1] = x[ 16 - 1 ];
       this->getAreasAux()[109 - 1] = x[ 16 - 1 ];
       this->getAreasAux()[110 - 1] = x[ 16 - 1 ];
       this->getAreasAux()[112 - 1] = x[ 16 - 1 ];
       this->getAreasAux()[113 - 1] = x[ 16 - 1 ];

       this->getAreasAux()[115 - 1] = x[ 17 - 1 ];
       this->getAreasAux()[116 - 1] = x[ 17 - 1 ];
       this->getAreasAux()[117 - 1] = x[ 17 - 1 ];
       this->getAreasAux()[118 - 1] = x[ 17 - 1 ];

       this->getAreasAux()[119 - 1] = x[ 18 - 1 ];
       this->getAreasAux()[122 - 1] = x[ 18 - 1 ];
       this->getAreasAux()[125 - 1] = x[ 18 - 1 ];
       this->getAreasAux()[128 - 1] = x[ 18 - 1 ];
       this->getAreasAux()[131 - 1] = x[ 18 - 1 ];

       this->getAreasAux()[133 - 1] = x[ 19 - 1 ];
       this->getAreasAux()[134 - 1] = x[ 19 - 1 ];
	 this->getAreasAux()[135 - 1] = x[ 19 - 1 ];
	 this->getAreasAux()[136 - 1] = x[ 19 - 1 ];
       this->getAreasAux()[137 - 1] = x[ 19 - 1 ];
       this->getAreasAux()[138 - 1] = x[ 19 - 1 ];

       this->getAreasAux()[140 - 1] = x[ 20 - 1 ];
       this->getAreasAux()[143 - 1] = x[ 20 - 1 ];
       this->getAreasAux()[146 - 1] = x[ 20 - 1 ];
       this->getAreasAux()[149 - 1] = x[ 20 - 1 ];
       this->getAreasAux()[152 - 1] = x[ 20 - 1 ];

       this->getAreasAux()[120 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[121 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[123 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[124 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[126 - 1] = x[ 21 - 1 ];
	 this->getAreasAux()[127 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[129 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[130 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[141 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[142 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[144 - 1] = x[ 21 - 1 ];
	 this->getAreasAux()[145 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[147 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[148 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[150 - 1] = x[ 21 - 1 ];
       this->getAreasAux()[151 - 1] = x[ 21 - 1 ];

       this->getAreasAux()[153 - 1] = x[ 22 - 1 ];
       this->getAreasAux()[154 - 1] = x[ 22 - 1 ];
       this->getAreasAux()[155 - 1] = x[ 22 - 1 ];
       this->getAreasAux()[156 - 1] = x[ 22 - 1 ];

       this->getAreasAux()[157 - 1] = x[ 23 - 1 ];
       this->getAreasAux()[160 - 1] = x[ 23 - 1 ];
       this->getAreasAux()[163 - 1] = x[ 23 - 1 ];
       this->getAreasAux()[166 - 1] = x[ 23 - 1 ];
       this->getAreasAux()[169 - 1] = x[ 23 - 1 ];

       this->getAreasAux()[171 - 1] = x[ 24 - 1 ];
       this->getAreasAux()[172 - 1] = x[ 24 - 1 ];
       this->getAreasAux()[173 - 1] = x[ 24 - 1 ];
       this->getAreasAux()[174 - 1] = x[ 24 - 1 ];
       this->getAreasAux()[175 - 1] = x[ 24 - 1 ];
       this->getAreasAux()[176 - 1] = x[ 24 - 1 ];

       this->getAreasAux()[178 - 1] = x[ 25 - 1 ];
       this->getAreasAux()[181 - 1] = x[ 25 - 1 ];
       this->getAreasAux()[184 - 1] = x[ 25 - 1 ];
       this->getAreasAux()[187 - 1] = x[ 25 - 1 ];
       this->getAreasAux()[190 - 1] = x[ 25 - 1 ];

       this->getAreasAux()[158 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[159 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[161 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[162 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[164 - 1] = x[ 26 - 1 ];
	 this->getAreasAux()[165 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[167 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[168 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[179 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[180 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[182 - 1] = x[ 26 - 1 ];
	 this->getAreasAux()[183 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[185 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[186 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[188 - 1] = x[ 26 - 1 ];
       this->getAreasAux()[189 - 1] = x[ 26 - 1 ];

       this->getAreasAux()[191 - 1] = x[ 27 - 1 ];
       this->getAreasAux()[192 - 1] = x[ 27 - 1 ];
       this->getAreasAux()[193 - 1] = x[ 27 - 1 ];
       this->getAreasAux()[194 - 1] = x[ 27 - 1 ];

       this->getAreasAux()[195 - 1] = x[ 28 - 1 ];
       this->getAreasAux()[197 - 1] = x[ 28 - 1 ];
       this->getAreasAux()[198 - 1] = x[ 28 - 1 ];
       this->getAreasAux()[200 - 1] = x[ 28 - 1 ];

       this->getAreasAux()[196 - 1] = x[ 29 - 1 ];
       this->getAreasAux()[199 - 1] = x[ 29 - 1 ];

	}

}
}
}

