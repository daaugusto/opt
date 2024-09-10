
/*
 * Evaluate_Surrogate_LLR.h
 *
 *  Created on: 05/10/2012
 *      Author: Heder S. Bernardino
 */

#ifndef EVALUATE_SURROGATE_LLR_H
#define EVALUATE_SURROGATE_LLR_H

#include <vector>
#include <utility>
#include "Evaluate_Surrogate.h"
#include "kdtree/KDTree.h"
using namespace std;
using namespace opt::surrogate;
using namespace opt::surrogate::kdtree;

namespace opt {
    namespace surrogate {

        class Evaluate_Surrogate_LLR: public Evaluate_Surrogate {
            private:
                vector< pair<double, IndividualPtr> > database;
                double weightParameter;
                int dimension;
                static bool sortPair(pair<double, IndividualPtr> i, pair<double, IndividualPtr> j);
                void fill(MatrixXd* A, MatrixXd* b, vector< pair <double, IndividualPtr> > database, int nLines, int nCols);
                void fillWeighted(MatrixXd* A, MatrixXd* b, vector< pair <double, IndividualPtr> > database, int nLines, int nCols);
            public:
                Evaluate_Surrogate_LLR(Function *func_, double weightParameter_);
                virtual ~Evaluate_Surrogate_LLR();

                virtual double calcFitness(IndividualPtr &ind);
                double calculateDistances( vector< pair <double, IndividualPtr> > database, IndividualPtr &individual );
                void insert(IndividualPtr individual);
                virtual void update( Evaluate* eval );

        };

    } /* namespace surrogate */
} /* namespace opt */
#endif /* EVALUATE_SURROGATE_LLR_H */
