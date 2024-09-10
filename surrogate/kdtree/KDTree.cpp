/*
 * KDTree.cpp
 *
 *  Created on: 17/04/2012
 *      Author: Eduardo Krempser
 */

#include "KDTree.h"
#include "math.h"
#include "stdlib.h"


namespace opt {
namespace surrogate {
namespace kdtree {

KDTree::KDTree(int dim, Function *func){
	root  = 0;
	treeDepth = 0;
	found = 0;
	nFound = 0;
	foundK = 0;
	nFoundK = 0;

	dimension = dim;
	function = func;
}

void KDTree::insert(IndividualPtr x){
	no *point = new no;

	point->ind = x;

	//09/08/2012
	/*for (int i = 0; i < function->getNDimensions(); i++){
		x->setGene(i, function->convertToRealRange(i, x->getGene(i)));
	}*/

	point->left  = 0;
	point->right = 0;

	build(point, &root, 0);
}

void KDTree::build(no *p, no **r, int depth){

	if (root == 0){
		root = p;
		treeDepth = 1;
	} else if (*r == 0){
		*r = p;
		if (treeDepth < depth) treeDepth = depth;
	} else {
		int path = depth%dimension;
		int equal = 1;
		equal = 0;
		double dist = distance((*r)->ind, p->ind);
		if (dist < 0.000001) equal = 1;
		if (equal){
			//If equal values the point is discarded
			return;
		} else if (p->ind->getGene(path) <= (*r)->ind->getGene(path)){
			build(p, &((*r)->left), depth+1);
		} else {
			build(p, &((*r)->right), depth+1);
		}
	}
}

void KDTree::printRec(no *r, int space){
	if (r == 0) return;
	cout << "\n";
	for(int i = 0; i < space; i++) cout << " ";
	for(int i = 0; i < dimension; i++){
		cout << "x[" << i << "]: " << r->ind->getGene(i) << " ";
	}
	printRec(r->left, space + 2);
	printRec(r->right, space + 2);
}

void KDTree::print(){
	printRec(root, 0);
	cout << "\n";
}

float KDTree::distance(no *p1, no *p2){
	float result = 0;
	for(int i = 0; i < dimension; i++){
		result +=  pow(p1->ind->getGene(i) - p2->ind->getGene(i), 2);
	}
	return sqrt(result);
}

double KDTree::distance(IndividualPtr ind1, IndividualPtr ind2){
	no *point1 = new no;
	point1->ind = ind1;
	point1->left  = 0;
	point1->right = 0;

	no *point2 = new no;
	point2->ind = ind2;
	point2->left  = 0;
	point2->right = 0;

	return distance(point1, point2);
}


void KDTree::includeFoundPoint(no *p, double dist){
	if (nFound == 0){
		found = (no**)malloc(sizeof(no*));
		distFound = (double*)malloc(sizeof(double));
		//found = new no*;
		found[0] = p;
		distFound[0] = dist;
		nFound = 1;
	} else {
		nFound++;
		found = (no**)realloc(found, nFound*(sizeof(no*)));
		distFound = (double*)realloc(distFound, nFound*(sizeof(double)));
		found[nFound - 1] = p;
		distFound[nFound - 1] = dist;
	}
}

void KDTree::includeFoundPointK(no *r, no *p, int k, double dist){
	if (foundK == 0 || nFoundK == 0){
		foundK = new no*[k];
		distFoundK = new double[k];
		for(int i = 0; i < k; i++)
			foundK[i] = 0;
		nFoundK = 0;
	}
	if (nFoundK < k){
		foundK[nFoundK] = r;
		distFoundK[nFoundK] = dist;
		nFoundK++;
	} else {
		int iWorstDist = 0;
		for(int i = 1; i < k; i++){
			if (distFoundK[i] > distFoundK[iWorstDist]){
				iWorstDist = i;
			} 
			if (distFoundK[i] == dist){
				return;
			}
		}
		if (dist < distFoundK[iWorstDist]){
			foundK[iWorstDist] = r;
			distFoundK[iWorstDist] = dist;
		}
	}
}

//r root, p the searched point, range the near distance wanted
void KDTree::searchRec(no *r, no* p, int depth, float range, int k){
	//Define if kd-tree will be used (1)
	int USE_LIMITED_SEARCH = 0;

	if (r == 0){
		//no point found
		return;
	}

	int path = depth%dimension;
	int left = 0;
	//Percorre em busca da folha
	if (p->ind->getGene(path) <= r->ind->getGene(path) ){
		searchRec(r->left, p, depth+1, range, k);
		left = 1;
	} else {
		searchRec(r->right, p, depth+1, range, k);
	}
	//Voltando das folhas, verifica a necessidade de buscar na outra subarvore
	float min, max;
	min = p->ind->getGene(path) - range;
	max = p->ind->getGene(path) + range;
	if (left){
		if (USE_LIMITED_SEARCH == 1){
			if ((min <= r->ind->getGene(path)) && (max >= r->ind->getGene(path))){
				searchRec(r->right, p, depth+1, range, k);
			}
		} else {
			searchRec(r->right, p, depth+1, range, k);
		}
	} else {
		if (USE_LIMITED_SEARCH == 1){
			if ((min <= r->ind->getGene(path)) && (max >= r->ind->getGene(path))){
				searchRec(r->left, p, depth+1, range, k);
			}
		} else {
			searchRec(r->left, p, depth+1, range, k);
		}
	}

	double dist = distance(r, p);
	if (dist <= range){
		includeFoundPoint(r, dist);
	}
	includeFoundPointK(r, p, k, dist);
}

void KDTree::search(IndividualPtr x, float range, int k){
	if (nFound > 0)  free(found);
	if (nFoundK > 0) delete []foundK;
	nFound  = 0;
	nFoundK = 0;
	no *point = new no;

	/*for (int i = 0; i < function->getNDimensions(); i++){
		x->setGene(i, function->convertToRealRange(i, x->getGene(i)));
	}*/

	point->ind = x;
	point->left  = 0;
	point->right = 0;


	//Search
	searchRec(root, point, 0, range, k);
}

KDTree::~KDTree() {
	if (nFound > 0) delete []found;
	if (nFoundK > 0) delete []foundK;
}



void KDTree::update(Evaluate *eval){
	updateRec(eval, root);
}

void KDTree::updateRec(Evaluate *eval, no *r){
	if (r == 0){
		return;
	}
	eval->calcFitness(r->ind, true);
	updateRec(eval, r->left);
	updateRec(eval, r->right);
}

} /* namespace kdtree */
} /* namespace surrogate */
} /* namespace opt */
