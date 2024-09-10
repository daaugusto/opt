/*
 * includes.h
 *
 *  Created on: 03/02/2012
 *      Author: Eduardo Krempser
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

//General
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

//Base
#include "base/Input.h"
#include "base/Tools.h"
#include "base/Individual.h"
#include "base/Exception.h"

//Functions
#include "function/Function.h"
#include "function/Function_F.h"
#include "function/Function_G.h"
#include "function/Function_Unconstrained.h"
#include "function/Function_BBOB.h"
#include "function/Function_Mechanic.h"
#include "function/Function_Truss.h"
#include "function/Function_SMD.h"

//Evaluates
#include "evaluate/Evaluate.h"
#include "evaluate/Evaluate_APM.h"
#include "evaluate/Evaluate_APM_Damping.h"
#include "evaluate/Evaluate_APM_Monotonic.h"
#include "evaluate/Evaluate_Deb.h"
#include "evaluate/Evaluate_BLDE.h"

//Operators
#include "operator/Operator.h"
#include "operator/Operator_CX_1X.h"
#include "operator/Operator_CX_BLXa.h"
#include "operator/Operator_CX_SBX.h"
#include "operator/Operator_CX_Uniform.h"
#include "operator/Operator_MT_Delta.h"
#include "operator/Operator_MT_NonUniform.h"
#include "operator/Operator_MT_Rand.h"
#include "operator/Operator_MT_DE_Best.h"
#include "operator/Operator_MT_DE_Current_Rand.h"
#include "operator/Operator_MT_DE_Rand_Best.h"
#include "operator/Operator_MT_DE_Rand.h"
#include "operator/Operator_MT_DE_Rand2.h"
#include "operator/Operator_MT_DE_Current_Best.h"

//Algorithms
#include "algorithm/Algorithm.h"
#include "algorithm/Algorithm_DE.h"
#include "algorithm/Algorithm_GA.h"

//AOS
#include "aos/AOS.h"

//Hybrid AOS
#include "hybridAOS/Algorithm_DE_AOS.h"
#include "hybridAOS/Algorithm_GA_AOS.h"
#include "hybridAOS/Algorithm_Hybrid_AOS.h"
#include "hybridAOS/Algorithm_HybridOp_AOS.h"


//Surrogate model
#include "surrogate/Evaluate_Surrogate.h"
#include "surrogate/Evaluate_Surrogate_NN.h"
#include "surrogate/Evaluate_Surrogate_LWR.h"
#include "surrogate/Evaluate_Surrogate_LLR.h"
#include "surrogate/Evaluate_Surrogate_RBF.h"

//DE with surrogate model
#include "smde/Algorithm_SMDE.h"
//Surrogate with adaptive K-nn
#include "smde/Algorithm_SMDE_aKnn.h"
//DE with local search and surrogate model
#include "slsde/Algorithm_SLSDE.h"
//DE with ensemble surrogate model
#include "esmde/Algorithm_ESMDE.h"

//DE for bilevel problem
#include "blde/Algorithm_BLDE.h"

#endif /* INCLUDES_H_ */
