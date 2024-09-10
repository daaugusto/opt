
#ifndef ADAPTIVEOPERATORSELECTION_H_
#define ADAPTIVEOPERATORSELECTION_H_

//definition of OSR techniques indexes
#define T_ProbMatching 1
#define T_AdaptPursuit 2
#define T_BanditAlone 3
#define T_BanditRestart 4
#define T_AUCBanditPlus 5 //rank-based
#define T_Uniform 6

//definition of CAS techniques indexes
#define C_EXT 0
#define C_AVG 1
#define C_INST 2
#define C_SUM 9
#define C_SUM_CUT 10
#define C_SUM_PLUS 12
#define C_AUC 19
#define C_AUC_CUT 20
#define C_AUC_PLUS 21

// the includes for OSR
#include "osr/ProbMatching.h"
#include "osr/AdaptPursuit.h"
#include "osr/BanditAlone.h"
#include "osr/BanditRestart.h"
#include "osr/Uniform.h"
#include "osr/AUCBandit.h"

// the includes for CAS
#include "cas/CreditAssignment.h"
#include "cas/AUCCredit.h"
#include "cas/SUMCredit.h"


#endif /* ADAPTIVEOPERATORSELECTION_H_ */
