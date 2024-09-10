/*
 * Function_BLDE.h
 *
 *  Created on: 30/01/2019
 *      Author: Jaque
 */

#ifndef FUNCTION_SMD_H_
#define FUNCTION_SMD_H_

#include "Function.h"

#include "../base/Tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

namespace opt {
namespace function {

class Function_SMD : public Function{
private:
	int idFunction;
        // Leader variables: X = (x1,x2), Follower variables: Y = (y1,y2)
        // dim(x_1) = p;
        // dim(x_2) = r;
        // dim(y_1) = q;
        // dim(y_2) = r;
        // upper level: dim(X) = p + r
        // lower level: dim(y) = q + r or q + s + r (depends on the problem)
        int p, q, r, s;
        int DIML, DIMF;

protected:
	virtual void setBounds(); //Leader
        virtual void setBoundsF();

	double *vMin;//vMin[3];
	double *vMax;//vMax[3]; 
public:
	Function_SMD(int id);
	virtual ~Function_SMD();
	virtual void calc(const vector<double> valuesLeader, const vector<double> valuesFollower, double &fitness, vector<double> &constVal, int level); //level = 1 -> leader, 2 -> follower
	//virtual double convertToRealRange(int index, double val);

        int getN(); // DIML+DIMF
        int getDIML(); // leader's dimension
        int getDIMF(); // followers's dimension
	double getBoundMax(int index);
	double getBoundMin(int index);

	double getBoundMaxFollower(int index);
	double getBoundMinFollower(int index);

	//Functions
        //void smd1(double *x, double *f, int nx);
        //void smd1(double *ind, int d, int nivel, double *leader, double *follower, int funcao);
        void smd1(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);
        void smd2(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);
        void smd3(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);
        void smd4(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);
        void smd5(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);
        void smd6(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);
        void smd7(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);
        void smd8(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level);

};

} /* namespace function */
} /* namespace opt */
#endif /* FUNCTION_UNCONSTRAINED_H_ */
