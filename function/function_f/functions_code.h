#ifndef FUNCTIONFCODE_H_
#define FUNCTIONFCODE_H_ 1

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include <limits>

//////////////////////////////////// DECLARACOES GLOBAIS
//# include <values.h>

#include "../../base/Tools.h"

using namespace opt::base;

namespace opt{
namespace function {
namespace function_f_code {


#define INF std::numeric_limits<double>::max()
#define EPS 1.0e-10
#define E  2.7182818284590452353602874713526625
#define PI 3.1415926535897932384626433832795029

class Functions_Code{
public:

/* Global variables that you are required to initialize */
  int nreal;					/* number of real variables */
  int nfunc;					/* number of basic functions */
  double bound;			/* required for plotting the function profiles for nreal=2 */
  int density;				/* density of grid points for plotting for nreal=2 */

/* Global variables being used in evaluation of various functions */
/* These are initalized in file def2.c */
  double C;
  double global_bias;
  double *trans_x;
  double *basic_f;
  double *temp_x1;
  double *temp_x2;
  double *temp_x3;
  double *temp_x4;
  double *weight;
  double *sigma;
  double *lambda;
  double *bias;
  double *norm_x;
  double *norm_f;
  long double **o;
  double **g;
  long double ***l;


// Auxillary function declarations
  double maximum (double, double);
  double minimum (double, double);
  double modulus (double*, int);
  double dot (double*, double*, int);
  double mean (double*, int);

// Basic funcion declarations
  double calc_ackley (double*);
  double calc_rastrigin (double*);
  double calc_weierstrass (double*);
  double calc_griewank (double*);
  double calc_sphere (double*);
  double calc_schwefel (double*);
  double calc_rosenbrock (double *x);
  double nc_schaffer (double, double);
  double nc_rastrigin (double*);

// Utility function declarations
  void allocate_memory();
  void initialize_f(int func);
  void transform (double*, int);
  void transform_norm (int);
  void calc_weight (double*);
  void free_memory();

// Benchmark function declaration
  double calc_benchmark_func(int func, double*);
  void calc_benchmark_norm();

// Function declarations for the random number generator
  void randomize();
  double randomperc();
  int rnd (int low, int high);
  double rndreal (double low, double high);
  void initrandomnormaldeviate();
  double noise (double mu, double sigma);
  double randomnormaldeviate();


// Test problem specific variable declarations
//Funcao 5
  double **A_f5;
  double *B_f5;

//Funcao 12
  double **A_f12;
  double **B_f12;
  double *alpha_f12;


  int rndcalcflag;
  double rndx1, rndx2;

  void initialize_f1();

  void initialize_f2();

  void initialize_f3();

  void initialize_f4();

  void initialize_f5();

  void initialize_f6();

  void initialize_f7();

  void initialize_f8();

  void initialize_f9();

  void initialize_f10();

  void initialize_f11();

  void initialize_f12();

  void initialize_f13();

  void initialize_f14();

  void initialize_f15();

  void initialize_f16();

  void initialize_f17();

  void initialize_f18();

  void initialize_f19();

  void initialize_f20();

  void initialize_f21();

  void initialize_f22();

  void initialize_f23();

  void initialize_f24();


///////////////////////////////// FAZ A CHAMADA PARA AS FUNCOES
  double calc_benchmark_func_f1(double *x);

  double calc_benchmark_func_f2(double *x);

  double calc_benchmark_func_f3(double *x);

  double calc_benchmark_func_f4(double *x);

  double calc_benchmark_func_f5(double *x);

  double calc_benchmark_func_f6(double *x);

  double calc_benchmark_func_f7(double *x);

  double calc_benchmark_func_f8(double *x);

  double calc_benchmark_func_f9(double *x);

  double calc_benchmark_func_f10(double *x);

  double calc_benchmark_func_f11(double *x);

  double calc_benchmark_func_f12(double *x);

  double calc_benchmark_func_f13(double *x);

  double calc_benchmark_func_f14(double *x);

  void calc_benchmark_norm_f15();

  double calc_benchmark_func_f15(double *x);

  void calc_benchmark_norm_f16();

  double calc_benchmark_func_f16(double *x);

  void calc_benchmark_norm_f17();

  double calc_benchmark_func_f17(double *x);

  void calc_benchmark_norm_f18();

  double calc_benchmark_func_f18(double *x);

  void calc_benchmark_norm_f19();

  double calc_benchmark_func_f19(double *x);

  void calc_benchmark_norm_f20();

  double calc_benchmark_func_f20(double *x);

  void calc_benchmark_norm_f21();

  double calc_benchmark_func_f21(double *x);

  void calc_benchmark_norm_f22();

  double calc_benchmark_func_f22(double *x);

  void calc_benchmark_norm_f23();

  double calc_benchmark_func_f23(double *x);

  void calc_benchmark_norm_f24();

  double calc_benchmark_func_f24(double *x);

};

}}}

#endif
