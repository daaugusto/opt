/*
 * Individual.h
 *
 *  Created on: 06/02/2012
 *      Author: Eduardo Krempser
 */
#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include "Exception.h"


#include <vector>
#include <map>
#include <string>
#include <memory>
using namespace std;
//using namespace std::tr1;

#include "Input.h"

namespace opt {
	namespace base {

		class Individual {
			private:
				//Values of the variables
				vector<double> chromosome;

				//--- Fitness options ---
				//Final Fitness -- with penalty, if necessary
				double fitness;
				//Fitness -- without penalty (useful to APM update)
				double fitnessOriginal;
				//Approximated fitness -- to surrogate model
				double fitnessSurrogate;

				//--- Constraints options ---
				//Exact constraints
				vector<double> constraints;
				//Approximated constraints -- to surrogate model
				vector<double> constraintsSurrogate;

				//Flags to exact and approximate evaluation
				bool evaluatedExact;
				bool evaluatedSurrogate;

				//Extra informations
				string infoOperator;
				string infoSurrogate;
				map<string, double> infoParams;
				string infoExtra;
			public:
				Individual();
				virtual ~Individual();

				//Initializes fitness values and creates gene values in [0, 1]
				void initialize(int dimension);
				//Return the sum of the constraints
				double getSumConstraints() const;
				double getSumConstraintsSurrogate() const;
				//Return the sum of the constraints for all constraints
				double getSumConstraintsAll() const;
				double getSumConstraintsSurrogateAll() const;
				//Return true if all constraints are less or equal than zero
				bool isValid() const;

				//Get separated values
				void   setGene(int index, double value);
				double getGene(int index) const;
				void   setConstraint(int index, double value);
				double getConstraint(int index) const;
				void   setInfoParam(string key, double value);
				double getInfoParam(string key) const;

				int getDimensions() const;
				int getNConstraints() const;

				// -- Getter and Setter
				vector<double> getChromosome() const;
				vector<double> getConstraints() const;
				vector<double> getConstraintsSurrogate() const;
				double getFitness() const;
				double getFitnessOriginal() const;
				double getFitnessSurrogate() const;
				string getInfoExtra() const;
				string getInfoOperator() const;
				map<string, double> getInfoParams() const;
				string getInfoSurrogate() const;
				bool isEvaluatedExact() const;
				bool isEvaluatedSurrogate() const;
				void setChromosome(vector<double> chromosome);
				void setConstraints(vector<double> constraints);
				void setConstraintsSurrogate(vector<double> constraintsSurrogate);
				void setFitness(double fitness);
				void setFitnessOriginal(double fitnessOriginal);
				void setFitnessSurrogate(double fitnessSurrogate);
				void setInfoExtra(string infoExtra);
				void setInfoOperator(string infoOperator);
				void setInfoParams(map<string, double> infoParams);
				void setInfoSurrogate(string infoSurrogate);
				void setEvaluatedExact(bool evaluatedExact);
				void setEvaluatedSurrogate(bool evaluatedSurrogate);
				// -- End of the Getter and Setter --

		};

	    typedef shared_ptr<Individual> IndividualPtr;

	} /* namespace base */
}
#endif /* INDIVIDUAL_H_ */
