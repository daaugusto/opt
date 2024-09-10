/*
 * KDTree.h
 *
 *  Created on: 17/04/2012
 *      Author: krempser
 */

#ifndef KDTREE_H_
#define KDTREE_H_

#include "../../base/Individual.h"
#include "../../function/Function.h"
#include "../../evaluate/Evaluate.h"
using namespace std;
using namespace opt::base;
using namespace opt::function;
using namespace opt::evaluate;

namespace opt {
namespace surrogate {
namespace kdtree {

	struct no{
		IndividualPtr ind;
		no* left;
		no* right;
	};

	class KDTree {
	public:
		no** found;
		double *distFound;
		int nFound;
		no** foundK;
		double *distFoundK;
		int nFoundK;
	private:
		no* root;
		int treeDepth;
		int dimension;
		Function *function;
	public:
		virtual ~KDTree();
		KDTree(int dim, Function *func);

		void insert(IndividualPtr x);

		void build(no *p, no **r, int depth);

		void printRec(no *r, int space);

		void print();

		float distance(no *p1, no *p2);

		void includeFoundPoint(no *p, double dist);

		void includeFoundPointK(no *r, no *p, int k, double dist);

		//r root, p the searched point, range the near distance wanted
		void searchRec(no *r, no* p, int depth, float range, int k);

		void search(IndividualPtr x, float range, int k = 1);

		double distance(IndividualPtr ind1, IndividualPtr ind2);

		//Update fitness information (k - values em APM)
		void update(Evaluate *eval);
		void updateRec(Evaluate *eval, no *r);
	};

} /* namespace kdtree */
} /* namespace surrogate */
} /* namespace opt */
#endif /* KDTREE_H_ */
