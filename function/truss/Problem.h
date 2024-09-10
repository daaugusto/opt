/*
 * Problem.h
 *
 *  Modify on: 18/05/2012 based in file Problem.h
 *      Author: Eduardo Krempser
 */

/*
 * File:   Problem.h
 * Author: hedersb
 *
 * Created on November 19, 2010, 10:43 AM
 */



#ifndef PROBLEM_H_
#define PROBLEM_H_

#include <memory>
using namespace std;

namespace opt {
namespace function {
namespace truss {

class Problem {
public:
    Problem(int dimension, void* bounds, int maxNumberObjectiveFunctionEvaluations, int numberObjectives, int numberConstraints);
    Problem(const Problem& orig);
    virtual ~Problem();
    void evaluate(void* vector, void* values);
    int getNumberObjectiveFunctionEvaluations() const;
    int getMaxNumberObjectiveFunctionEvaluations() const;
    void* getBounds() const;
    int getNumberObjectives() const;
    int getNumberConstraints() const;
    int getDimension() const;
protected:
    int dimension;
    virtual void evaluation(void* vector, void* values) = 0;
    int numberObjectiveFunctionEvaluations;
    int maxNumberObjectiveFunctionEvaluations;
    void* bounds;
    int numberObjectives;
    int numberConstraints;
};

typedef shared_ptr<Problem> ProblemPtr;


} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* PROBLEM_H_ */
