/*
 * Individual.cpp
 *
 *  Created on: 06/02/2012
 *      Author: Eduardo Krempser
 */

#include "Individual.h"
#include "Tools.h"

namespace opt {
namespace base {
	// -- Construction methods --
	Individual::Individual() {
		this->evaluatedExact     = false;
		this->evaluatedSurrogate = false;

		this->constraints.clear();
		this->chromosome.clear();
		this->constraintsSurrogate.clear();

		this->infoParams.clear();
		this->infoExtra = "";
		this->infoOperator  = "";
		this->infoSurrogate = "";
	}

	Individual::~Individual() {
		// TODO Auto-generated destructor stub
	}

	//Initializes fitness values and creates gene values in [0, 1]
	void Individual::initialize(int dimension){
		for (int i = 0; i < dimension; i++){
			double value = Tools::initializeGene(i);
			this->chromosome.push_back(value);
		}
	}

	//Return the sum of the constraints (only unsatisfied constraint)
	double Individual::getSumConstraints() const{
		int dim = this->constraints.size();
		double sum = 0.0;
		for(int i = 0; i < dim; i++){
			if (this->constraints[i] > 0.0)
				sum += this->constraints[i];
		}
		return sum;
	}

	double Individual::getSumConstraintsSurrogate() const{
		int dim = this->constraintsSurrogate.size();
		double sum = 0.0;
		for(int i = 0; i < dim; i++){
			if (this->constraintsSurrogate[i] > 0.0)
				sum += this->constraintsSurrogate[i];
		}
		return sum;
	}

	//Return the sum of the constraints (all constraints)
	double Individual::getSumConstraintsAll() const{
		int dim = this->constraints.size();
		double sum = 0.0;
		for(int i = 0; i < dim; i++){
			sum += this->constraints[i];
		}
		return sum;
	}

	double Individual::getSumConstraintsSurrogateAll() const{
		int dim = this->constraintsSurrogate.size();
		double sum = 0.0;
		for(int i = 0; i < dim; i++){
			sum += this->constraintsSurrogate[i];
		}
		return sum;
	}

	//Return true if all constraints are less or equal than zero
	bool Individual::isValid() const{
		int dim = this->constraints.size();
		for(int i = 0; i < dim; i++){
			if (this->constraints[i] > 0)
				return false;
		}
		return true;
	}

	//Get separated values
	void Individual::setGene(int index, double value){
//cout << " add value pre " << value << endl;
		value = Tools::treatBasicBounds(value, index);
		if ((unsigned)index < chromosome.size()){
			this->chromosome[index] = value;
		} else {
			this->chromosome.push_back(value);
//cout << " add value " << value << endl;
		}
	}

	double Individual::getGene(int index) const{
		if ((unsigned)index >= this->chromosome.size())
			throw new Exception("The index is greater than the chromosome size -- Individual.cpp/getGene");

		return chromosome[index];
	}

	void Individual::setConstraint(int index, double value){
		if ((unsigned)index >= constraints.size()){
			this->constraints.push_back(value);
		} else {
			this->constraints[index] = value;
		}
	}

	double Individual::getConstraint(int index) const{
		if ((unsigned)index >= this->constraints.size()){
			return 0.0;
		} else {
			return this->constraints[index];
		}
	}

	void Individual::setInfoParam(string key, double value) {
		this->infoParams[key] = value;
	}

	double Individual::getInfoParam(string key) const{
		if (this->infoParams.find(key) == this->infoParams.end())
			throw new Exception("The key was not found in param list -- Individual.cpp/getInfoParam");

		return (double)this->infoParams.find(key)->second;
	}

	int Individual::getDimensions() const{
		return this->chromosome.size();
	}

	int Individual::getNConstraints() const{
		return this->constraints.size();
	}

	//--- Getter and Setter
	vector<double> Individual::getChromosome() const
	{
		return this->chromosome;
	}

	vector<double> Individual::getConstraints() const
	{
		return this->constraints;
	}

	vector<double> Individual::getConstraintsSurrogate() const
	{
		return this->constraintsSurrogate;
	}

	double Individual::getFitness() const
	{
		return this->fitness;
	}

	double Individual::getFitnessOriginal() const
	{
		return this->fitnessOriginal;
	}

	double Individual::getFitnessSurrogate() const
	{
		return this->fitnessSurrogate;
	}

	string Individual::getInfoExtra() const
	{
		return this->infoExtra;
	}

	string Individual::getInfoOperator() const
	{
		return this->infoOperator;
	}

	map<string, double> Individual::getInfoParams() const
	{
		return this->infoParams;
	}

	string Individual::getInfoSurrogate() const
	{
		return this->infoSurrogate;
	}

	void Individual::setChromosome(vector<double> chromosome)
	{
		this->chromosome = chromosome;
	}

	void Individual::setConstraints(vector<double> constraints)
	{
		this->constraints = constraints;
	}

	void Individual::setConstraintsSurrogate(vector<double> constraintsSurrogate)
	{
		this->constraintsSurrogate = constraintsSurrogate;
	}

	void Individual::setFitness(double fitness)
	{
		this->fitness = fitness;

		//Check the evaluated flag
		this->evaluatedExact = true;
	}

	void Individual::setFitnessOriginal(double fitnessOriginal)
	{
		this->fitnessOriginal = fitnessOriginal;

		//Check the evaluated flag
		this->evaluatedExact = true;
	}

	void Individual::setFitnessSurrogate(double fitnessSurrogate)
	{
		this->fitnessSurrogate = fitnessSurrogate;

		//Check the surrogate evaluated flag
		this->evaluatedSurrogate = true;
	}

	void Individual::setInfoExtra(string infoExtra)
	{
		this->infoExtra = infoExtra;
	}

	void Individual::setInfoOperator(string infoOperator)
	{
		this->infoOperator = infoOperator;
	}

	void Individual::setInfoParams(map<string, double> infoParams)
	{
		this->infoParams = infoParams;
	}

    bool Individual::isEvaluatedExact() const
    {
        return evaluatedExact;
    }

    bool Individual::isEvaluatedSurrogate() const
    {
        return evaluatedSurrogate;
    }

    void Individual::setEvaluatedExact(bool evaluatedExact)
    {
        this->evaluatedExact = evaluatedExact;
    }

    void Individual::setEvaluatedSurrogate(bool evaluatedSurrogate)
    {
        this->evaluatedSurrogate = evaluatedSurrogate;
    }

	void Individual::setInfoSurrogate(string infoSurrogate)
	{
		this->infoSurrogate = infoSurrogate;
	}
	// -- End of the Getter and Setter --



} /* namespace base */
}
