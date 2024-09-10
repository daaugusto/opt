/*
 * Input.cpp
 *
 *  Created on: 03/02/2012
 *      Author: Eduardo Krempser
 */

#include "Input.h"

namespace opt{
	namespace base {
		//Here we initialize static variables
		Function* Input::function = 0;
		bool Input::normalized = false;

		//Basic parameters
		int Input::idFunction = 1;
		int Input::hybrid = 1; int Input::show = 0;
		int Input::dim = 2; int Input::idTest = 0; int Input::run = 0;
		int Input::gen = 10; int Input::currentIndividual = 0; int Input::seedValue = -1; int Input::popSize = 40; int Input::maxGen = 50;
		double Input::pDE = 0.5; double Input::pGA = 0.5;
		string Input::algorithm = "DE";
		string Input::tEval = "DEB";
		string Input::sm = "";
		string Input::smp = "2";
		string Input::sel = "Y";
		int Input::nap = 1;
		double Input::F = 0.5;
		string Input::sl = "NONE";

		//Bilevel
		int Input::level = 1;
		int Input::popSizeF=20; int Input::maxGenF = 50;
		int Input::napF = 1;
		int Input::recalc = 0;

		//Opeators
		vector<int> Input::opDE;
		vector<int> Input::opGA;

		//AOS parameters
		int Input::aos = 0;
		int Input::aos_de = -1;
		int Input::aos_ga = -1;

		double Input::aos_p_min = 0.01; double Input::aos_alpha = 0.8; double Input::aos_beta = 0.8; double Input::aos_v_scaling = 0.5; double Input::aos_v_gamma = 100; double Input::aos_decay = 0.5;
		int Input::aos_W = 50; int Input::aos_delta_fitness = 1; int Input::aos_type = 0; int Input::aos_norm = 0;
		//DE-AOS parameters
		double Input::aos_de_p_min = -1; double Input::aos_de_alpha = -1; double Input::aos_de_beta = -1; double Input::aos_de_v_scaling = -1; double Input::aos_de_v_gamma = -1; double Input::aos_de_decay = -1;
		int Input::aos_de_W = -1; int Input::aos_de_delta_fitness = -1; int Input::aos_de_type = -1; int Input::aos_de_norm = -1;
		//GA-Parameters
		double Input::aos_ga_p_min = -1; double Input::aos_ga_alpha = -1; double Input::aos_ga_beta = -1; double Input::aos_ga_v_scaling = -1; double Input::aos_ga_v_gamma = -1; double Input::aos_ga_decay = -1;
		int Input::aos_ga_W = -1; int Input::aos_ga_delta_fitness = -1; int Input::aos_ga_type = -1; int Input::aos_ga_norm = -1;

		//BBOB parameters
		string Input::path = "PUT_MY_BBOB_DATA_PATH";
		string Input::algname = "PUT ALGORITHM NAME";

		string Input::help(){
			ostringstream result;
			result << "\n\t\t#################################################";
			result << "\n\t\t#              Input Parameter                  #";
			result << "\n\t\t#################################################";
			result << "\n\t\t# -p      | Int Value    | Population size      #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -g      | Int Value    | Max generations      #";
//			result << "\n\t\t#-----------------------------------------------#";
//			result << "\n\t\t# -hybrid | None         | Use hybrid alg.      #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -f      | Int Value    | Code of Function     #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -pDE    | Double Value | DE probability       #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -pGA    | Double Value | GA probability       #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -eval   | String Value | Type of evaluate     #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -dim    | Int Value    | Function dimension   #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -t      | Int Value    | Id of test           #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -r      | Int Value    | Numb. of run         #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -s      | Int Value    | Seed value           #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -show   | None         | Show parcial results #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -alg    | String Value | Algorithm            #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -sm     | String Value | Surrogate Model      #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -smp    | Double Value | Parameter of surrog. #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -nap    | Int Value    | Numb. of approx. ind #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -sel    | String Value | Y, EI, PoI           #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -F      | Double Value | Parameter F of DE    #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -sl     | String Value | Alg. of the L. Search#";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -aos    | Int Value    | AOS Technique        #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -opDE   | Int Values   | DE variants          #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -opGA   | Int Values   | GA operators         #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -pF     | Int Value    | Follower Pop. size   #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -gF     | Int Value    | Follower Max gen.    #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -napF   | Int Value    | Follower N. app. ind.#";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -recalc | 0 or 1 value | Use recalc. strateg. #";
			result << "\n\t\t#-----------------------------------------------#";
			result << "\n\t\t# -h      | None         | This help            #";
			result << "\n\t\t#################################################";
			result << "\n";
			return result.str();
		}

		void Input::setParams(int argc, char *argv[]){
		  opDE.clear();
		  opGA.clear();
		  //Input parameters
		  for (int i = 0; i < argc; i++){
			//Pop size
			if ((strcmp(argv[i], "-p") == 0) && (i+1 < argc)){
			  popSize = atoi(argv[i+1]);
			}
			//Number of generation
			else if ((strcmp(argv[i], "-g") == 0) && (i+1 < argc)){
			  maxGen = atoi(argv[i+1]);
			}
			//Define the o use of hybrid algorithm
			else if ((strcmp(argv[i], "-hybrid") == 0)){
			  hybrid = 1;
			}
			//Define the function
			else if ((strcmp(argv[i], "-f") == 0) && (i+1 < argc)){
			  idFunction = atoi(argv[i+1]);
			}
			//DE probability (only non-hybrid case)
			else if ((strcmp(argv[i], "-pDE") == 0) && (i+1 < argc)){
			  pDE = atof(argv[i+1]);
			}
			//GA probability (only non-hybrid case)
			else if ((strcmp(argv[i], "-pGA") == 0) && (i+1 < argc)){
			  pGA = atof(argv[i+1]);
			}
			//Define the o use of APM
			else if ((strcmp(argv[i], "-eval") == 0) && (i+1 < argc)){
			  ostringstream val;
			  val << argv[i+1];
			  tEval = val.str();
			}
			//Dimension to the function
			else if ((strcmp(argv[i], "-dim") == 0) && (i+1 < argc)){
			  dim = atoi(argv[i+1]);
			}
			//Id of test
			else if ((strcmp(argv[i], "-t") == 0) && (i+1 < argc)){
			  idTest = atoi(argv[i+1]);
			}
			//Number of the run
			else if ((strcmp(argv[i], "-r") == 0) && (i+1 < argc)){
			  run = atoi(argv[i+1]);
			}
			//Seed value
			else if ((strcmp(argv[i], "-s") == 0) && (i+1 < argc)){
			  seedValue = atoi(argv[i+1]);
			}
			//Show results for each generation
			else if ((strcmp(argv[i], "-show") == 0)){
			  show = 1;
			}
			//Name of algorithm
			else if ((strcmp(argv[i], "-alg") == 0)){
			  ostringstream val;
			  val << argv[i+1];
			  algorithm = val.str();
			}
			//Help text
			else if ((strcmp(argv[i], "-h") == 0)){
			  cout << help();
			  exit(0);
			}
			//Surrogate model
			else if ((strcmp(argv[i], "-sm") == 0)){
			  ostringstream val;
			  val << argv[i+1];
			  sm = val.str();
			}
			//Number of approximated individuals by operator
			else if ((strcmp(argv[i], "-nap") == 0)){
			  nap = atoi(argv[i+1]);
			}
			//K value in Knn
			else if ((strcmp(argv[i], "-smp") == 0) && (i+1 < argc)){
			  ostringstream val;
			  val << argv[i+1];
			  smp = val.str();
			}
			//Type of selection by surrogate (EI: Expected Imp., PoI: Prob. Imp, Y: normal)
			else if ((strcmp(argv[i], "-sel") == 0) && (i+1 < argc)){
			  ostringstream val;
			  val << argv[i+1];
			  sel = val.str();
			}
			//Value to F parameter of the DE
			else if ((strcmp(argv[i], "-F") == 0)){
			  F = atof(argv[i+1]);
			}
			//Define the o use of Local Search Algorithm
			else if ((strcmp(argv[i], "-sl") == 0) && (i+1 < argc)){
			  ostringstream val;
			  val << argv[i+1];
			  sl = val.str();
			}
			//Follower DE' pop size
			else if ((strcmp(argv[i], "-pF") == 0) && (i+1 < argc)){
			  popSizeF = atoi(argv[i+1]);
			}
			//Follower DE' number of generation 
			else if ((strcmp(argv[i], "-gF") == 0) && (i+1 < argc)){
			  maxGenF = atoi(argv[i+1]);
			}
			//Follower DE' number of generated individuals in the aproximation
			else if ((strcmp(argv[i], "-napF") == 0) && (i+1 < argc)){
			  napF = atoi(argv[i+1]);
			}
			//Follower DE' number of generated individuals in the aproximation
			else if ((strcmp(argv[i], "-recalc") == 0) && (i+1 < argc)){
			  recalc = atoi(argv[i+1]);
			}
			//Number of the technique of the aos
			else if ((strcmp(argv[i], "-aos") == 0)){
			  aos = atoi(argv[i+1]);
			}
			//Values to AOS /////////////////////////////////
			else if ((strcmp(argv[i], "-aos_p_min") == 0)){
			  aos_p_min = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de") == 0)){
			  aos_de = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga") == 0)){
			  aos_ga = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_alpha") == 0)){
			  aos_alpha = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_beta") == 0)){
			  aos_beta = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_v_scaling") == 0)){
			  aos_v_scaling = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_v_gamma") == 0)){
			  aos_v_gamma = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_decay") == 0)){
			  aos_decay = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_W") == 0)){
			  aos_W = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_delta_fitness") == 0)){
			  aos_delta_fitness = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_type") == 0)){
			  aos_type = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_norm") == 0)){
			  aos_norm = atoi(argv[i+1]);
			}
			//AOS-DE
			else if ((strcmp(argv[i], "-aos_de_p_min") == 0)){
			  aos_de_p_min = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_alpha") == 0)){
			  aos_de_alpha = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_beta") == 0)){
			  aos_de_beta = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_v_scaling") == 0)){
			  aos_de_v_scaling = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_v_gamma") == 0)){
			  aos_de_v_gamma = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_decay") == 0)){
			  aos_de_decay = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_W") == 0)){
			  aos_de_W = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_delta_fitness") == 0)){
			  aos_de_delta_fitness = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_type") == 0)){
			  aos_de_type = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_de_norm") == 0)){
			  aos_de_norm = atoi(argv[i+1]);
			}
			//AOS-GA
			else if ((strcmp(argv[i], "-aos_ga_p_min") == 0)){
			  aos_ga_p_min = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_alpha") == 0)){
			  aos_ga_alpha = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_beta") == 0)){
			  aos_ga_beta = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_v_scaling") == 0)){
			  aos_ga_v_scaling = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_v_gamma") == 0)){
			  aos_ga_v_gamma = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_decay") == 0)){
			  aos_ga_decay = atof(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_W") == 0)){
			  aos_ga_W = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_delta_fitness") == 0)){
			  aos_ga_delta_fitness = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_type") == 0)){
			  aos_ga_type = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-aos_ga_norm") == 0)){
			  aos_ga_norm = atoi(argv[i+1]);
			}
			else if ((strcmp(argv[i], "-opDE") == 0)){
				int len = strlen(argv[i+1]);
				for (int l = 0; l < len; l++){
					char res[4];
					int j = 0;
					while(argv[i+1][l] != '-' && l < len){
						res[j++] = argv[i+1][l++];
					}
					res[j] = 0;
					opDE.push_back(atoi(res));
				}
			}
			else if ((strcmp(argv[i], "-opGA") == 0)){
				int len = strlen(argv[i+1]);
				for (int l = 0; l < len; l++){
					char res[4];
					int j = 0;
					while(argv[i+1][l] != '-' && l < len){
						res[j++] = argv[i+1][l++];
					}
					res[j] = 0;
					opGA.push_back(atoi(res));
				}
			}
			//BBOB parameters
			else if ((strcmp(argv[i], "-path") == 0) && (i+1 < argc)){
				 ostringstream val;
				  val << argv[i+1];
				  path = val.str();
			}
			else if ((strcmp(argv[i], "-algname") == 0) && (i+1 < argc)){
				 ostringstream val;
				  val << argv[i+1];
				  algname = val.str();
			}
			///////////////////////////////////////////////// end parameters
		  }
		}

	} /* namespace base */
}
