/*
 * Operator.h
 *
 *  Created on: 08/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <string>
#include <iostream>
#include <vector>
#include "../base/Individual.h"
#include "../base/Tools.h"
#include "../base/Input.h"
using namespace opt::base;
using namespace std;

//Define index operator
#define OP_GA_CX_1X           0
#define OP_GA_CX_BLXa         1
#define OP_GA_CX_SBX          2
#define OP_GA_CX_UNIFORM      3
#define OP_GA_MT_DELTA        4
#define OP_GA_MT_NONUNIFORM   5
#define OP_GA_MT_RAND         6

#define OP_GA_SIZE            7

#define OP_DE_MT_BEST         0
#define OP_DE_MT_CURRENT_RAND 1
#define OP_DE_MT_RAND         2
#define OP_DE_MT_RAND_BEST    3
#define OP_DE_MT_RAND2        4
#define OP_DE_MT_CURRENT_BEST 5


#define OP_DE_SIZE            6

namespace opt {
namespace operators {

	class Operator {
		private:
			//Identification of operator
			string key;
			//Identification of the type (mutation, recombination, ...)
			string type;
			//Number  of offspring to each parent
			int nOffspring;
			//Minimal Number of parents
			int nParent;
		public:
			Operator();
			virtual ~Operator();

			int getNParent();
			int getNOffspring();
			string getKey();
			string getType();
			void setType(string t);
			void setKey(string k);
			void setNParent(int n);
			void setNOffspring(int n);

			//Return the size of offspring
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring);
			//Apply operator with setted parameter
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param);
			//Apply operator with the index of the parents
			virtual int apply(vector<IndividualPtr> parent, vector<IndividualPtr> &offspring, double param, vector<int> index);
			//Select parents with the same mechanism of the application
			virtual vector<int> selectParents(vector<IndividualPtr> pop);
	};

} /* namespace operators */
} /* namespace opt */
#endif /* OPERATOR_H_ */
