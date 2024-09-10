/*
 * Truss_Bar_Structure_Static_Simulator.h
 *
 *  Modify on: 18/05/2012 based in file TrussBarStructureStaticProblem.h
 *      Author: Eduardo Krempser
 */

/*
 * File:   TrussBarStructureStaticProblem.h
 * Author: Heder S. Bernardino
 *
 * Created on September 11, 2011, 10:11 AM
 */


#ifndef TRUSS_BAR_STRUCTURE_STATIC_PROBLEM_H_
#define TRUSS_BAR_STRUCTURE_STATIC_PROBLEM_H_

#include "Problem.h"
#include "math.h"
#include "simulator/Truss_Bar_Structure_Static_Simulator.h"
using namespace std;
using namespace opt::function::truss::simulator;

namespace opt {
namespace function {
namespace truss {

class Truss_Bar_Structure_Static_Problem : public Problem{
public:
		Truss_Bar_Structure_Static_Problem(int dimension, void* bounds, int maxNumberObjectiveFunctionEvaluations, int numberObjectives, int numberConstraints, int numberOfBars, double gamma, double stressConstraint, double displacementConstraint, /*int numberOfDisplacementConstraints,*/ string inputFileName, double lowerBound, double upperBound);
		Truss_Bar_Structure_Static_Problem(const Truss_Bar_Structure_Static_Problem& orig);
		virtual ~Truss_Bar_Structure_Static_Problem();
		virtual void evaluation(void* vector, void* values);
		int const getNumberOfBars();
		int const getNLCase();
		double const getDisplacementConstraint();
	protected:
		/*
		 * Return an integer array containing information about how to group the bars of the structure.
		 * NULL is indicated to the cases in which there is not grouping, that is, when the number of bars is equals to the number of groups.
		 */
		virtual int* const getGrouping();
		/*
		 * Create a array with the areas of the bars using the grouping.
		 * It is important highlight that the method 'createGrouping' should be used here.
		 */
		virtual void fillAreasAux(double* x);
		/*
		 * Return the array with the cross-section areas.
		 */
		double* const getAreasAux();
		double* const getStressDisplacementAux();
		/*
		 * Calculate the number of displacements.
		 */
		int getNumberOfDisplacements();
		Truss_Bar_Structure_Static_Simulator_Ptr const getSimulator();
	private:
		/*
		 * Simulator used to calculate the weight, stresses and displacements of the structure.
		 */
		Truss_Bar_Structure_Static_Simulator_Ptr simulator;
		/*
		 * Number of bars of the structure.
		 */
		int numberOfBars;
		/*
		 * Specific weight of the bar's material.
		 */
		double gamma;
		/*
		 * Maximum stress allowed in the bars.
		 */
		double stressConstraint;
		/*
		 * Maximum displacement allowed for the nodes.
		 */
		double displacementConstraint;
		/*
		 * Number of nodes where displacements can happen.
		 */
		int numberOfDisplacements;
		/*
		 * Variable to archive the stresses and displacements.
		 */
		double* stressDisplacementAux;
		/*
		 * Variable to archive the cross-sectional area of the bars.
		 */
		double* areasAux;
		//variables with data from input file
		int numnp_cpp;
		int numeg_cpp;
		int nlcase_cpp;
		int modex_cpp;
		int* node_n_cpp;
		int** node_id_cpp;
		double** node_position_cpp;
		int* ll_cpp;
		int* loads_n_cpp;
		int** loads_node_cpp;
		int** loads_direction_cpp;
		double** loads_cpp;
		int elements_npar_1;
		int elements_npar_2;
		int elements_npar_3;
		int* element_id_cpp;
		double* element_cpp;
		double* element_extra_cpp; //this information is not used by stap
		int* m_cpp;
		int* ii_cpp;
		int* jj_cpp;
		int* mtyp_cpp;
		int* kg_cpp;

		/*
		 * Load information about the structure from a file.
		 */
		void readFile(string fileName);

	};

} /* namespace truss */
} /* namespace function */
} /* namespace opt */
#endif /* TRUSS_BAR_STRUCTURE_STATIC_PROBLEM_H_ */
