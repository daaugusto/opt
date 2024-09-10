/*
 * AOS.h
 *
 *  Created on: 15/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef AOS_H_
#define AOS_H_

#include "AdaptiveOperatorSelection.h"
#include "../base/Input.h"
#include <string>
using namespace opt::base;

namespace opt {
namespace aos {

	class AOS {
		public:
			int AOS_technique;
			unsigned n_techniques;
			unsigned n_operators;
			string outputFile;
			double p_min, alpha, beta;
			double v_scaling, v_gamma, decay;
			int W;
			int aos_delta_fitness, aos_type, aos_norm;
			bool user;
			OperatorSelection *aos;

			AOS(int n_operators, std::string alg = "ALL");
			virtual ~AOS();
			int SelectOperator();
			void addReward(int index, double reward);
			double ApplyReward(int index);
	};

} /* namespace aos */
} /* namespace opt */
#endif /* AOS_H_ */
