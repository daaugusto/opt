/*
 * AOS.cpp
 *
 *  Created on: 15/02/2012
 *      Author: Eduardo Krempser
 */

#include "AOS.h"

namespace opt {
namespace aos {

AOS::AOS(int n_operators, std::string alg) {
	//Number of operators
	this->n_operators = n_operators;

	///AOS parameters
	if (alg.compare("DE") == 0){//if (alg == "DE")
		this->p_min =             Input::aos_de_p_min == -1         ? Input::aos_p_min         : Input::aos_de_p_min;
		this->alpha =             Input::aos_de_alpha == -1         ? Input::aos_alpha         : Input::aos_de_alpha;
		this->beta =              Input::aos_de_beta == -1          ? Input::aos_beta          : Input::aos_de_beta;
		this->v_scaling =         Input::aos_de_v_scaling == -1     ? Input::aos_v_scaling     : Input::aos_de_v_scaling;
		this->v_gamma =           Input::aos_de_v_gamma == -1       ? Input::aos_v_gamma       : Input::aos_de_v_gamma;
		this->decay =             Input::aos_de_decay == -1         ? Input::aos_decay         : Input::aos_de_decay;
		this->W =                 Input::aos_de_W == -1             ? Input::aos_W             : Input::aos_de_W;
		this->aos_delta_fitness = Input::aos_de_delta_fitness == -1 ? Input::aos_delta_fitness : Input::aos_de_delta_fitness;
		this->aos_type =          Input::aos_de_type == -1          ? Input::aos_type          : Input::aos_de_type;
		this->aos_norm =          Input::aos_de_norm == -1          ? Input::aos_norm          : Input::aos_de_norm;
		this->AOS_technique =     Input::aos_de == -1               ? Input::aos               : Input::aos_de;
	} else if (alg.compare("GA") == 0 || alg.compare("GA_MT") == 0 || alg.compare("GA_CX") == 0){
		this->p_min =             Input::aos_ga_p_min == -1         ? Input::aos_p_min         : Input::aos_ga_p_min;
		this->alpha =             Input::aos_ga_alpha == -1         ? Input::aos_alpha         : Input::aos_ga_alpha;
		this->beta =              Input::aos_ga_beta == -1          ? Input::aos_beta          : Input::aos_ga_beta;
		this->v_scaling =         Input::aos_ga_v_scaling == -1     ? Input::aos_v_scaling     : Input::aos_ga_v_scaling;
		this->v_gamma =           Input::aos_ga_v_gamma == -1       ? Input::aos_v_gamma       : Input::aos_ga_v_gamma;
		this->decay =             Input::aos_ga_decay == -1         ? Input::aos_decay         : Input::aos_ga_decay;
		this->W =                 Input::aos_ga_W == -1             ? Input::aos_W             : Input::aos_ga_W;
		this->aos_delta_fitness = Input::aos_ga_delta_fitness == -1 ? Input::aos_delta_fitness : Input::aos_ga_delta_fitness;
		this->aos_type =          Input::aos_ga_type == -1          ? Input::aos_type          : Input::aos_ga_type;
		this->aos_norm =          Input::aos_ga_norm == -1          ? Input::aos_norm          : Input::aos_ga_norm;
		this->AOS_technique =     Input::aos_ga == -1               ? Input::aos               : Input::aos_ga;
	} else {
		this->p_min =             Input::aos_p_min;
		this->alpha =             Input::aos_alpha;
		this->beta =              Input::aos_beta;
		this->v_scaling =         Input::aos_v_scaling;
		this->v_gamma =           Input::aos_v_gamma;
		this->decay =             Input::aos_decay;
		this->W =                 Input::aos_W;
		this->aos_delta_fitness = Input::aos_delta_fitness;
		this->aos_type =          Input::aos_type;
		this->aos_norm =          Input::aos_norm;
		this->AOS_technique =     Input::aos;
	}

	// OperatorSelection
	switch(this->AOS_technique){
		case 0:{
			this->aos = new ProbMatching(n_operators, outputFile, p_min, alpha);
			this->aos->credit = new CreditAssignment*[this->n_operators]; //(1 FIFO window of size W per operator)
				for(unsigned j=0; j<this->n_operators; j++)
					this->aos->credit[j] = new CreditAssignment(this->W, 1, C_EXT, 0);
		} break;
		case 1:{
			this->aos = new AdaptPursuit(n_operators, outputFile, p_min, alpha, beta);
			this->aos->credit = new CreditAssignment*[this->n_operators]; //(1 FIFO window of size W per operator)
				for(unsigned j=0; j<this->n_operators; j++)
					this->aos->credit[j] = new CreditAssignment(this->W, 1, C_EXT, 0);
		} break;
		case 2:{
			this->aos = new BanditAlone(n_operators, outputFile, user, v_scaling);
			this->aos->credit = new CreditAssignment*[this->n_operators]; //(1 FIFO window of size W per operator)
				for(unsigned j=0; j<this->n_operators; j++)
					this->aos->credit[j] = new CreditAssignment(this->W, 1, C_EXT, 0);
		} break;
		case 3:{
			this->aos = new BanditRestart(n_operators, outputFile, user, v_scaling, v_gamma);
			this->aos->credit = new CreditAssignment*[this->n_operators]; //(1 FIFO window of size W per operator)
				for(unsigned j=0; j<this->n_operators; j++)
					this->aos->credit[j] = new CreditAssignment(this->W, 1, C_EXT, 0);
		} break;
		case 4:{
			this->aos = new Uniform(n_operators, outputFile);
			this->aos->credit = new CreditAssignment*[this->n_operators]; //(1 FIFO window of size W per operator)
				for(unsigned j=0; j<this->n_operators; j++)
					this->aos->credit[j] = new CreditAssignment(this->W, 1, C_EXT, 0);
		} break;
		case 5:{
			this->aos = new AUCBandit(n_operators, outputFile, user, v_scaling); //AUC
			this->aos->credit = new CreditAssignment*[1]; //(1 FIFO window of size W for all operators)
				this->aos->credit[0] = new AUCCredit(this->W, 1, this->n_operators, false, false, 0, this->decay); // AUC 1xAll v2
		} break;
		case 6:{
			this->aos = new AUCBandit(n_operators, outputFile, user, v_scaling); //AUC
			this->aos->credit = new CreditAssignment*[1]; //(1 FIFO window of size W for all operators)
				this->aos->credit[0] = new SUMCredit(this->W, 1, this->n_operators, false, false, 0, this->decay); // SUM
		} break;
	}

}

AOS::~AOS() {
	delete aos;
}

int AOS::SelectOperator(){
	return aos->SelectOperator();
}

void AOS::addReward(int index, double reward){
	aos->addReward((unsigned)index, reward);
}

double AOS::ApplyReward(int index){
	return aos->ApplyReward((unsigned)index);
}

} /* namespace aos */
} /* namespace opt */
