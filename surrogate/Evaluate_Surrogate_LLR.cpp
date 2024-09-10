
/*
 * Evaluate_Surrogate_LLR.cpp
 *
 *  Created on: 05/10/2012
 *      Author: Heder S. Bernardino
 */

#include <algorithm>
#include <cmath>
#include <limits>
#include "algebra/Eigen/Dense"
#include "Evaluate_Surrogate_LLR.h"

using namespace Eigen;
using namespace std;

namespace opt {
    namespace surrogate {


		Evaluate_Surrogate_LLR::Evaluate_Surrogate_LLR(Function *func_, double weightParameter_):Evaluate_Surrogate(func_), dimension( func_->getNDimensions() ), weightParameter( weightParameter_ ) {
            this->setKey(SURROGATE_LLR);
            //cout << "Dimension: " << this->dimension << endl;
//            cout << "Weighted: " << this->weighted << endl;

            //trial
//            MatrixXd A( 3, 2 );
//            MatrixXd b( 3, 1 );
//            double point = 1.0;
//
//            A( 0, 0 ) = 0;
//            A( 0, 1 ) = 1;
//            A( 1, 0 ) = 1.5;
//            A( 1, 1 ) = 1;
//            A( 2, 0 ) = 3;
//            A( 2, 1 ) = 1;
//
//            b( 0, 0 ) = sin( A( 0, 0 ) ) ;
//            b( 1, 0 ) = sin( A( 1, 0 ) ) ;
//            b( 2, 0 ) = sin( A( 2, 0 ) ) ;
//
//            for(int i =0; i<3; i++) {
//                double w = 1/abs( A(i, 0) - point );
//                b(i, 0) *= w;
//                for(int j =0; j<2; j++) {
//                    A(i, j) *= w;
//                    cout << A(i, j) << " ";
//                }
//                cout << b(i, 0) << endl;
//            }
//
//            b = A.transpose() * b;
//            A = A.transpose() * A;
//
//
//            //Nao resolve o sistema linear direto
//            FullPivHouseholderQR<MatrixXd> qr = A.fullPivHouseholderQr( );
//            MatrixXd x = qr.solve( b );
//            //Resolve o sistema linear direto
//            //MatrixXd x = A.jacobiSvd( ComputeThinU | ComputeThinV ).solve( b );
//
//            cout << "Model: " << x(0, 0) << "x + " << x( 1, 0 ) << endl;
//
//            exit( 0 );

        }

        Evaluate_Surrogate_LLR::~Evaluate_Surrogate_LLR() {

        }

        double Evaluate_Surrogate_LLR::calculateDistances( vector< pair <double, IndividualPtr> > database, IndividualPtr &individual ) {

			double distance;
			double difference;
			vector<double> chromosome = individual->getChromosome( );
			vector<double> tmpChromosome;

			int ind = 0;
            for ( vector< pair <double, IndividualPtr> >::iterator it = this->database.begin( ); it != this->database.end( ); ++it ) {
            	//cout << "Ind: " << ind << endl;
				distance = 0;
				tmpChromosome = (*it).second->getChromosome( );
				//calculating Euclildean distance
				for(int i=0; i< this->dimension; i++) {
					//cout << "calculate the distance between " << chromosome[ i ] << " and " << tmpChromosome[ i ] << " at dimension " << i << endl;
					difference = chromosome[ i ] - tmpChromosome[ i ];
					distance += difference * difference;
				}
				//cout << "total distance to individual " << ind << ": " << distance << endl;
				ind ++;
				(*it).first = sqrt( distance );
            }

        }

		bool Evaluate_Surrogate_LLR::sortPair(pair<double, IndividualPtr> i,pair<double, IndividualPtr> j) {
            return i.first < j.first;
        }

        double Evaluate_Surrogate_LLR::calcFitness(IndividualPtr &individual){
            this->nEval = this->nEval + 1;

            int currentDimension = dimension + 1; //+1 is because of the displacement of the model with respect to the origin (0,0)
            int nCols = currentDimension;

            //cout << "nEval: " << nEval << endl;
			//cout << "Database size: " << this->database.size() << "\tDimension: " << this->dimension << endl;
            //when the surrogate model is called and has less than dimension records in the database

            this->calculateDistances( this->database, individual );
			sort( this->database.begin(), this->database.end(), Evaluate_Surrogate_LLR::sortPair );

			if ( this->database.size() == 0 ) {
				individual->setFitnessSurrogate( numeric_limits<double>::max() );
				return numeric_limits<double>::max();
			} else if ( this->database.size() < currentDimension || this->database[ 0 ].first == 0 ) {
            	individual->setFitnessSurrogate( this->database[ 0 ].second->getFitness( ) );
				return this->database[ 0 ].second->getFitness( );
            } else {
                //cout << "Database size: " << this->database.size() << "\tDimension: " << this->dimension << endl;

				//cout << "Smaller distance: " << this->database[ 0 ].first << endl;
				//cout << "Larger distance: " << this->database[ this->database.size() -1 ].first << endl;

				//TODO -- to verify errors (if they happen)
				int i;
                int j;
				double fitness = 0.0;
				MatrixXd* A = new MatrixXd(currentDimension, nCols );
				MatrixXd* b = new MatrixXd(currentDimension, 1);
				//fill A and b
				if ( this->weightParameter > 0 ) {
                    this->fillWeighted( A, b, this->database, currentDimension, nCols );
				} else {
				    this->fill( A, b, this->database, currentDimension, nCols );
				}

				//decomposition
                FullPivHouseholderQR<MatrixXd> qr = (A->transpose() * (*A)).fullPivHouseholderQr( );
                //control the errors
                while ( qr.rank() < nCols && currentDimension < this->database.size() ) {
                    //TODO - to improve ?
                    delete A;
                    delete b;

                    A = new MatrixXd(currentDimension, nCols );
                    b = new MatrixXd(currentDimension, 1);
                    //fill A and b
                    if ( this->weightParameter ) {
                        this->fillWeighted( A, b, this->database, currentDimension, nCols );
                    } else {
                        this->fill( A, b, this->database, currentDimension, nCols );
                    }
                    //decomposition
                    //qr = A->fullPivHouseholderQr( );
                    //to solve the linear system
                    qr = (A->transpose() * (*A)).fullPivHouseholderQr( );

                    //cout << qr.rank() << " | " << currentDimension << endl;

                    //currentDimension++;
                    currentDimension = currentDimension < nCols*2? currentDimension+1: currentDimension*2;
                }

                if ( currentDimension >= this->database.size() ) {
                	delete A;
                	delete b;
                	individual->setFitnessSurrogate( this->database[ 0 ].second->getFitness( ) );
                    return this->database[ 0 ].second->getFitness( );
                }

				//wrong
                //MatrixXd x = qr.solve( *b );
                //to solve linear system
                MatrixXd x = qr.solve( A->transpose()*(*b) );
                //alternatives to solve the linear system
                //MatrixXd x = A->jacobiSvd( ComputeThinU | ComputeThinV ).solve( *b );

//                for (j=0; j<2; j++) {
//                    cout << "Ab ("<< j<<"):\t";
//                    for( i=0; i<dimension; i++) {
//                        cout << (*A)(j, i) << " ";
//                    }
//                    cout << endl;
//                }

                delete A;
                delete b;

//                double modelError = 0;
//                fitness = 0.0;
//                vector<double> c = this->database[ 0 ].second->getChromosome( );
//                for(j=0; j< this->dimension; j++) {
//                    fitness += x( j, 0 ) * c[ j ];
//                }
//                fitness += x( j, 0 );
//                modelError += (fitness - this->database[ 0 ].second->getFitness());
//                cout << "Smaller distance-> Distance: " << this->database[ 0 ].first << " | Predicted: " << fitness << " | Fitness: " << this->database[ 0 ].second->getFitness() << " | Model error: " << modelError << endl;
//                modelError = 0;
//                fitness = 0.0;
//                c = this->database[ currentDimension-1 ].second->getChromosome( );
//                for(j=0; j< this->dimension; j++) {
//                    fitness += x( j, 0 ) * c[ j ];
//                }
//                fitness += x( j, 0 );
//                modelError += (fitness - this->database[ currentDimension-1 ].second->getFitness());
//                cout << "Larger distance in the model-> Distance: " << this->database[ currentDimension-1 ].first << " | Predicted: " << fitness << " | Fitness: " << this->database[ currentDimension-1 ].second->getFitness() << " | Model error: " << modelError << endl;
//                modelError = 0;
//                fitness = 0.0;
//                c = this->database[ this->database.size()-1 ].second->getChromosome( );
//                for(j=0; j< this->dimension; j++) {
//                    fitness += x( j, 0 ) * c[ j ];
//                }
//                fitness += x( j, 0 );
//                modelError += (fitness - this->database[ this->database.size()-1 ].second->getFitness());
//                cout << "Larger distance-> Distance: " << this->database[ this->database.size()-1 ].first << " | Predicted: " << fitness << " | Fitness: " << this->database[ this->database.size()-1 ].second->getFitness() << " | Model error: " << modelError << endl;

                //Calculate approximation
                vector<double> chromosome = individual->getChromosome( );
                fitness = 0.0;
                for(i=0; i<dimension; i++) {
                    fitness += x( i, 0 ) * chromosome[ i ];
                    //cout << "x( " << i<< ", 0 ) * chromosome[ " << i << " ] = " << x( i, 0 ) << "*" << chromosome[ i ] << "=" << (x( i, 0 ) * chromosome[ i ]) << endl;
                }
                fitness += x( i, 0 );
                //cout << "x( " << i<< ", 0 ) * 1 = " << x( i, 0 ) << endl;

//                cout << currentDimension << " | " << fitness << endl;


				//return
                //cout << "Fitness: " << fitness << endl;
				individual->setFitnessSurrogate(fitness);
				return fitness;
            }
        }

        void Evaluate_Surrogate_LLR::fill(MatrixXd* A, MatrixXd* b, vector< pair <double, IndividualPtr> > database, int nLines, int nCols) {
            int j;
            nCols--;
            for(int i=0; i<nLines; i++) {
                vector<double> chromosome = this->database[ i ].second->getChromosome( );
                (*b)( i, 0 ) = this->database[ i ].second->getFitness( );
                for(j=0; j<nCols; j++) {
                    (*A)( i, j ) = chromosome[ j ];
                }
                (*A)( i, j ) = 1;
            }
        }

        void Evaluate_Surrogate_LLR::fillWeighted(MatrixXd* A, MatrixXd* b, vector< pair <double, IndividualPtr> > database, int nLines, int nCols) {
            int j;
            nCols--;
            double weighted;

            for(int i=0; i<nLines; i++) {
                vector<double> chromosome = this->database[ i ].second->getChromosome( );

				//padrao
//                weighted = 1.0 / this->database[ i ].first;
                //melhor -- equacao 9 em Geographically Weighted Regression: A Method for Exploring Spatial Nonstationarity
//                double beta = 10;
//                weighted = exp( -beta * this->database[ i ].first * this->database[ i ].first );

				double alpha = this->weightParameter;
				double D = this->database[ nLines-1 ].first;
                weighted = ( exp( -pow( (alpha*this->database[ i ].first) / D, 2 ) ) - exp( -alpha*alpha ) ) / ( 1 - exp( -alpha*alpha ) );

                (*b)( i, 0 ) = this->database[ i ].second->getFitness( ) * weighted;
                //cout << i <<  " | weight: " << weighted << endl;
                for(j=0; j<nCols; j++) {
                    (*A)( i, j ) = chromosome[ j ] * weighted;
                }
                (*A)( i, j ) = weighted;
            }
        }

        void Evaluate_Surrogate_LLR::insert(IndividualPtr ind){
            this->database.push_back( pair<double, IndividualPtr>(0.0, ind) );
        }

        void Evaluate_Surrogate_LLR::update( Evaluate* eval ) {
            for(int i=0; i< this->database.size(); i++) {
                eval->calcFitness( this->database[ i ].second, true );
            }
        }


    } /* namespace surrogate */
} /* namespace opt */
