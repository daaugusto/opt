/*
 * Problem.cpp
 *
 *  Modify on: 18/05/2012 based in file Problem.cpp
 *      Author: Eduardo Krempser
 */

/*
 * File:   Problem.cpp
 * Author: hedersb
 *
 * Created on November 19, 2010, 10:43 AM
 */

#include "Problem.h"

namespace opt {
namespace function {
namespace truss {

Problem::Problem(int dimension, void* bounds, int maxNumberObjectiveFunctionEvaluations, int numberObjectives, int numberConstraints) {
        this->dimension = dimension;
        this->numberObjectiveFunctionEvaluations = 0;
        this->maxNumberObjectiveFunctionEvaluations = maxNumberObjectiveFunctionEvaluations;
        this->bounds = bounds;
        this->numberObjectives = numberObjectives;
        this->numberConstraints = numberConstraints;
    }

    Problem::Problem(const Problem& orig) {
        this->dimension = orig.dimension;
        this->numberObjectiveFunctionEvaluations = orig.numberObjectiveFunctionEvaluations;
        this->maxNumberObjectiveFunctionEvaluations = orig.maxNumberObjectiveFunctionEvaluations;
        this->bounds = orig.bounds;
        this->numberObjectives = orig.numberObjectives;
        this->numberConstraints = orig.numberConstraints;
    }

    Problem::~Problem() {

    }

    void Problem::evaluate(void* vector, void* values) {
        numberObjectiveFunctionEvaluations++;
        this->evaluation(vector, values);
    }

    int Problem::getDimension() const {
        return this->dimension;
    }

    int Problem::getNumberObjectiveFunctionEvaluations() const {
        return this->numberObjectiveFunctionEvaluations;
    }

    int Problem::getMaxNumberObjectiveFunctionEvaluations() const {
        return this->maxNumberObjectiveFunctionEvaluations;
    }

    void* Problem::getBounds() const {
        return this->bounds;
    }

    int Problem::getNumberObjectives() const {
        return this->numberObjectives;
    }

    int Problem::getNumberConstraints() const {
        return this->numberConstraints;
    }

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
