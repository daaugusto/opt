/*
 * Function_Unconstrained.cpp
 *
 *  Created on: 30/01/2019
 *      Author: Jaqueline Angelo
 */

#include "Function_SMD.h"

namespace opt {
namespace function { 

Function_SMD::Function_SMD(int id) {
	idFunction = id;

    if (Input::dim == 10){
	 //Dimensao total = 10
	 DIML = 5;
	 DIMF = 5;

	vMin = new double[5];
	vMax = new double[5];
    } else if (Input::dim == 20){
	 //Dimensao total = 20
	 DIML = 10;
	 DIMF = 10;

	vMin = new double[10];
	vMax = new double[10];
    } else {
	 //Dimensao total = 5
	 DIML = 2;
	 DIMF = 3;

	vMin = new double[3];
	vMax = new double[3];
    }
    int DIM  = DIML+DIMF;


    //!O valor otimo de todas as funcoes eh zero (leader)!
    this->knowBest = 0;

    // problems 1006 (-10006)
    if (idFunction == -10006) {
            if ( DIM == 5 ){ // DIML = 2, DIMF = 3
                p = 1;
                r = 1;
                q = 1;
                s = 1;
            } else if ( DIM == 10 ){ //DIML = DIMF = 5
                p = 3;
                r = 2;   
                q = 1;
                s = 2;
            } else if ( DIM == 20 ){ //DIML = DIMF = 10
                p = 5;
                r = 5;
                q = 3;
                s = 2;
            }
    // problems 1001-1005,1007,1008  (-10001 : -10005, -10007, -10008)
    } else {
            s = 0;
            if ( DIM == 5 ){ // DIML = 2, DIMF = 3
                p = 1;
                r = 1;
                q = 2;
            } else if ( DIM == 10 ){ //DIML = DIMF = 5
                p = 3;
                r = 2;
                q = 3;
            } else if ( DIM == 20 ){ //DIML = DIMF = 10
                p = 5;
                r = 5;
                q = 5;
            }
    }


    //Define the bounds
    setBounds();
    setBoundsF();
}

Function_SMD::~Function_SMD() {
}

int Function_SMD::getN(){
        return (this->DIML + this->DIMF); // leader + follower
}

int Function_SMD::getDIML(){
        return this->DIML; // leader
}

int Function_SMD::getDIMF(){
        return this->DIMF; // follower
}

double Function_SMD::getBoundMax(int index){
	return boundMax[index];
}

double Function_SMD::getBoundMin(int index){
	return boundMin[index];
}

double Function_SMD::getBoundMaxFollower(int index){
	return vMax[index];
}

double Function_SMD::getBoundMinFollower(int index){
	return vMin[index];
}

//Define the bounds of the variables
void Function_SMD::setBounds(){ //Leader
	boundMin.clear();
	boundMax.clear();
        switch(idFunction){
                case -10001:{ //1001
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                } break;
                case -10002:{ //1002
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(1.0);
                    }
                } break;
                case -10003:{ //1003
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                } break;
                case -10004:{ //1004
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-1.0);
                        boundMax.push_back(1.0);
                    }
                } break;
                case -10005:{ //1005
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                } break;
                case -10006:{ //1006
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                } break;
                case -10007:{ //1007
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(1.0);
                    }
                } break;
                case -10008:{//1008
                    for (int i = 0; i < this->p ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                    for (int i = p; i < (this->p + this->r) ; i++){
                        boundMin.push_back(-5.0);
                        boundMax.push_back(10.0);
                    }
                } break;
        }
}

void Function_SMD::setBoundsF(){ //Follower
        switch(idFunction){
                case -10001:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0; 
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                        vMin[i] = - M_PI/2 + 0.000000000001;
                        vMax[i] = M_PI/2 - 0.000000000001; 
                    }
                } break;
                case -10002:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                       	vMin[i] =  0.000000000001;
                        vMax[i] =  M_E ;
                    }
                } break;
                case -10003:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                        vMin[i] = - M_PI/2 + 0.000000000001;
                        vMax[i] = M_PI/2 - 0.000000000001;
                    }
                } break;
                case -10004:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                        vMin[i] =  0.000000000001;
                        vMax[i] =  M_E ;
                    }
                } break;
                case -10005:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                } break;
                case -10006:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    vMin[q+r] = -5.0;
                    vMax[q+r] = 10.0;
                } break;
                case -10007:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                        vMin[i] =  0.000000000001;
                        vMax[i] = M_E ;
                    }
                } break;
                case -10008:{
                    for (int i = 0; i < this->q ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                    for (int i = q; i < (this->q + this->r) ; i++){
                        vMin[i] = -5.0;
                        vMax[i] = 10.0;
                    }
                } break;
        }
}

//SMD1
void Function_SMD::smd1(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;

        if (level == 1){

            for (int i = 0; i < this->p; i++){
                F1 += leader[i]*leader[i];
            }
            for (int i = 0; i < this->q; i++){
                F2 += follower[i]*follower[i];
            }
            j = this->p;
            for (int i = 0; i < this->r; i++){
                F3 += leader[j]*leader[j];
                j++;
            }
            j = this->p;
            w = this->q;
            for (int i = 0; i < this->r; i++){
                F3 += (leader[j] - tan(follower[w]))*(leader[j] - tan(follower[w]));
                j++; w++;
            }

            fitness = F1 + F2 + F3;

        } else if (level == 2){

            for (int i = 0; i < this->p; i++){
                F1 += leader[i]*leader[i];
            }
            for (int i = 0; i < this->q; i++){
                F2 += follower[i]*follower[i];
            }
            j = this->p;
            w = this->q;
            for (int i = 0; i < this->r; i++){
                F3 += (leader[j] - tan(follower[w]))*(leader[j] - tan(follower[w]));
                j++; w++;
            }

            fitness = F1 + F2 + F3;

        }
}

void Function_SMD::smd2(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;

        if (level == 1){

            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            for (int i = 0 ; i < this->q ; i++){
                F2 += (follower[i]*follower[i]);
            }
            F2 = -F2;
            j = this->p;
            w = this->q;
            double sum = 0.0; double sum2 = 0.0;
            for (int i = 0 ; i < this->r ; i++){
                sum += ( leader[j]*leader[j] );
                sum2 += ((leader[j]-log(follower[w]))*(leader[j]-log(follower[w])));
                j++; w++;
            }
            F3 = sum-sum2;

            fitness = F1 + F2 + F3;

        } else if (level == 2){

            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            for (int i = 0 ; i < this->q ; i++){
                F2 += (follower[i]*follower[i]);
            }
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                F3 += ((leader[j] - log(follower[w]))*(leader[j] - log(follower[w])));
                j++; w++;
            }

            fitness = F1 + F2 + F3;

        }

}

void Function_SMD::smd3(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;

        if (level == 1){

            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            for (int i = 0 ; i < this->q ; i++){
                F2 += (follower[i]*follower[i]);
            }
            double sum = 0.0; double sum2 = 0.0;
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                sum += (leader[j]*leader[j]);
                sum2 += ( ((leader[j]*leader[j])-tan(follower[w]))*((leader[j]*leader[j])-tan(follower[w])) );
                j++; w++;
            }
            F3 = sum+sum2;

            fitness = F1 + F2 + F3;

        } else if (level == 2){

            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            F2 = q;
            for (int i = 0 ; i < this->q ; i++){
                F2 += ( (follower[i]*follower[i]) - cos( 2*M_PI*follower[i] ));
            }
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                F3 += (((leader[j]*leader[j])-tan(follower[w]))*((leader[j]*leader[j])-tan(follower[w])));
                j++; w++;
            }

            fitness = F1 + F2 + F3;

        }

}

void Function_SMD::smd4(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;

        if (level == 1){
            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            double sum = 0.0;
            for (int i = 0 ; i < this->q ; i++){
                sum += (follower[i]*follower[i]);
            }
            F2 = -sum;
            sum = 0.0; double sum2 = 0.0;
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                sum += (leader[j]*leader[j]);
                sum2 += ( (fabs(leader[j])-log(1+follower[w]))*(fabs(leader[j])-log(1+follower[w])) );
                j++; w++;
            }
            F3 = sum - sum2;
            fitness = F1 + F2 + F3;
        } else if (level == 2){

            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            F2 = q;
            for (int i = 0 ; i < this->q ; i++){
                F2 += ( (follower[i]*follower[i]) - cos( 2*M_PI*follower[i] ));
            }
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                F3 += ((fabs(leader[j])-log(1+follower[w]))*(fabs(leader[j])-log(1+follower[w])));
                j++; w++;
            }

            fitness = F1 + F2 + F3;

        }

}

void Function_SMD::smd5(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;

        if (level == 1){

            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            double sum = 0.0;
            for (int i = 0 ; i < this->q-1 ; i++){
                sum += ( ((follower[i+1] - (follower[i]*follower[i]))*(follower[i+1] - (follower[i]*follower[i]))) + ( (follower[i]-1)*(follower[i]-1) ) );
            }
            F2 = -sum;
            sum = 0.0; double sum2 = 0.0;
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                sum += ( leader[j]*leader[j] );
                sum2 += ( (fabs(leader[j])-(follower[w]*follower[w]))*(fabs(leader[j])-(follower[w]*follower[w])));
                j++; w++;
            }
            F3 = sum - sum2;

            fitness = F1 + F2 + F3;

        } else if (level == 2){

             for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            for (int i = 0 ; i < this->q-1 ; i++){
                F2 += ( ((follower[i+1]-(follower[i]*follower[i]))*(follower[i+1]-(follower[i]*follower[i]))) + ((follower[i]-1)*(follower[i]-1)) );
            }
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                F3 += ( (fabs(leader[j])-(follower[w]*follower[w]))*(fabs(leader[j])-(follower[w]*follower[w])));
                j++; w++;
            }

            fitness = F1 + F2 + F3;

        }

}

void Function_SMD::smd6(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;

        if (level == 1){

            for (int i = 0 ; i < this->p ; i++){
                F1 += (leader[i]*leader[i]);
            }
            double sum = 0.0; double sum2 = 0.0;
            for (int i = 0 ; i < this->q ; i++){
                sum += ( follower[i]*follower[i] );
            }
            for (int i = this->q ; i < this->q+this->s ; i++){
                sum2 += ( follower[i]*follower[i] );
            }
            F2 = - sum + sum2;
            sum = 0.0; sum2 = 0.0;
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                sum += ( leader[j]*leader[j] );
                sum2 += (( leader[j]-follower[w+this->s] )*( leader[j]-follower[w+this->s] ));
                j++; w++;
            }
            F3 = sum - sum2;

            fitness = F1 + F2 + F3;

        } else if (level == 2){

            for (int i = 0 ; i < this->p ; i++){
                F1 += ( leader[i]*leader[i] );
            }
            double sum = 0.0; double sum2 = 0.0;
            for (int i = 0 ; i < this->q ; i++){
                sum += ( (follower[i]*follower[i]) );
            }
            // !! O 'SUM2' FOI ALTERADO DA REF ORIGINAL !!!!!!!!
            for (int i = this->q ; i < this->q+this->s; i = i+2){
                sum2 += ( (follower[i+1] - follower[i])*(follower[i+1] - follower[i]) );
            }
            F2 =  sum + sum2;
            j = this->p;
            w = this->q;
            for (int i = 0 ; i < this->r ; i++){
                F3 += (( leader[j]-follower[w+this->s] )*( leader[j]-follower[w+this->s] ));
                j++; w++;
            }

            fitness = F1 + F2 + F3;


        }

}

void Function_SMD::smd7(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;

        if (level == 1){

            double sum = 0.0;
            double prod = 1.0;
            for (int i = 0; i < this->p; i++){
                sum += ( leader[i]*leader[i] );
                prod *= ( cos(leader[i]/sqrt(i+1)) );
            }
            F1 = 1 + ((1/400) * sum) - prod;
            sum = 0.0;
            for (int i = 0; i < this->q; i++){
                sum += ( follower[i]*follower[i] );
            }
            F2 = -sum;
            sum = 0.0; double sum2 = 0.0;
            j = this->p;
            w = this->q;
            for (int i = 0; i < this->r; i++){
                sum += ( leader[j]*leader[j] );
                sum2 += ( (leader[j]-log(follower[w]))*(leader[j]-log(follower[w])) );
                j++; w++;
            }
            F3 = sum - sum2;
            fitness = F1 + F2 + F3;
        } else if (level == 2){

            for (int i = 0; i < this->p; i++){
                F1 += ( leader[i]*leader[i]*leader[i] );
            }
            for (int i = 0; i < this->q; i++){
                F2 += ( follower[i]*follower[i] );
            }
            j = this->p;
            w = this->q;
            for (int i = 0; i < this->r; i++){
                F3 += ((leader[j]-log(follower[w]))*(leader[j]-log(follower[w])));
                j++; w++;
            }
            fitness = F1 + F2 + F3;
        }

}

void Function_SMD::smd8(const vector<double> leader, const vector<double> follower, double &fitness, vector<double> &constVal, int level){

        double F1 = 0, F2 = 0, F3 = 0;
        int j, w;
        if (level == 1){

            double sum = 0.0; double sum2 = 0.0;
            for (int i = 0; i < this->p ; i++){
                sum += ( leader[i]*leader[i] );
                sum2 += ( cos(2*M_PI*leader[i]) );
            }
            F1 = (20 + M_E - (20 * exp(-0.2 * sqrt((1/p)*sum))) - exp((1/p)*sum2));
            sum = 0.0;
            for (int i = 0; i < this->q-1 ; i++){ //Alterei de q para q-1
                sum += ( ( (follower[i+1]-(follower[i]*follower[i]))*(follower[i+1]-(follower[i]*follower[i])) ) + ((follower[i]-1)*(follower[i]-1)));
            }
            F2 = -sum;
            sum = 0.0; sum2 = 0.0;
            j = this->p;
            w = this->q;
            for (int i = 0; i < this->r; i++){
                sum += ( (leader[j]*leader[j]) );
                sum2 += ( (leader[j]-(follower[w]*follower[w]*follower[w]))*(leader[j]-(follower[w]*follower[w]*follower[w])) );
                j++; w++;
            }
            F3 = sum - sum2;

            fitness = F1 + F2 + F3;

        } else if (level == 2){

            for (int i = 0 ; i < this->p ; i++){
                F1 += fabs(leader[i]);
            }
            for (int i = 0 ; i < this->q - 1; i++){ //ALTEREI DE q para q - 1
                F2 += ( ((follower[i+1]-(follower[i]*follower[i]))*(follower[i+1]-(follower[i]*follower[i]))) + ((follower[i]-1)*(follower[i]-1)) );
            }
            j = this->p;
            w = this->q;
            for (int i = 0; i < this->r; i++){
                F3 += ( (leader[j]-(follower[w]*follower[w]*follower[w]))*(leader[j]-(follower[w]*follower[w]*follower[w])) );
                j++; w++;
            }
            fitness = F1 + F2 + F3;

        }

}

void Function_SMD::calc(const vector<double> valuesLeader, const vector<double> valuesFollower, double &fitness, vector<double> &constVal, int level){
    switch(idFunction){
            case -10001:{ //1001
                smd1(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
            case -10002:{//1002
                smd2(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
            case -10003:{//1003
                smd3(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
            case -10004:{//1004
                smd4(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
            case -10005:{//1005
                smd5(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
            case -10006:{//1006
                smd6(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
            case -10007:{//1007
                smd7(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
            case -10008:{//1008
                smd8(valuesLeader, valuesFollower, fitness, constVal, level);
                break;
            }
    }
}

} /* namespace function */
} /* namespace opt */
