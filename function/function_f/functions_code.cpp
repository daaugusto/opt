#include "functions_code.h"

namespace opt{
namespace function {
namespace function_f_code {

/* Function to return the maximum of two variables */
double Functions_Code::maximum (double a, double b)
{
    if (a>b)
    {
        return(a);
    }
    return (b);
}

/* Function to return the minimum of two variables */
double Functions_Code::minimum (double a, double b)
{
    if (a<b)
    {
        return (a);
    }
    return (b);
}

/* Function to return the modulus of a vector */
double Functions_Code::modulus (double *x, int n)
{
    int i;
    double res;
    res = 0.0;
    for (i=0; i<n; i++)
    {
        res += x[i]*x[i];
    }
    return (sqrt(res));
}

/* Function to return the dot product of two vecors */
double Functions_Code::dot (double *a, double *b, int n)
{
    int i;
    double res;
    res = 0.0;
    for (i=0; i<n; i++)
    {
        res += a[i]*b[i];
    }
    return (res);
}

/* Function to return the mean of n variables */
double Functions_Code::mean (double *x, int n)
{
    int i;
    double res;
    res = 0.0;
    for (i=0; i<n; i++)
    {
        res += x[i];
    }
    return (res/(double)n);
}


////////////////////////////////// TRATAMENTO DE VALORES ALEATORIOS

/* Get seed number for random and start it up */
void Functions_Code::randomize()
{
//    init_sprng(SEED,SPRNG_DEFAULT);
//    srand(time(NULL));
    return;
}

/* Fetch a single random number between 0.0 and 1.0 */
double Functions_Code::randomperc()
{
//    return (sprng());
      return Tools::newRand(0.0, 1.0);
}

/* Fetch a single random integer between low and high including the bounds */
int Functions_Code::rnd (int low, int high)
{
/*    int res;
    if (low >= high)
    {
        res = low;
    }
    else
    {
        res = low + (randomperc()*(high-low+1));
        if (res > high)
        {
            res = high;
        }
    }
    return (res);
*/
	int res = (int)Tools::newRand(low, high);
}

/* Fetch a single random real number between low and high including the bounds */
double Functions_Code::rndreal (double low, double high)
{
//    return (low + (high-low)*randomperc());
	return Tools::newRand(low, high);
}

/* Initialize the randome generator for normal distribution */
void Functions_Code::initrandomnormaldeviate()
{
    rndcalcflag = 1;
    return;
}

/* Compute the noise */
double Functions_Code::randomnormaldeviate()
{
    double t;
    if(rndcalcflag)
    {
        rndx1 = sqrt(- 2.0*log(randomperc()));
        t = 6.2831853072*randomperc();
        rndx2 = sin(t);
        rndcalcflag = 0;
        return(rndx1*cos(t));
    }
    else
    {
        rndcalcflag = 1;
        return(rndx1*rndx2);
    }
}

/* Return the noise value */
double Functions_Code::noise (double mu, double sigma)
{
    return((randomnormaldeviate()*sigma) + mu);
}

////////////////////////////////// FUNCOES OBJETIVO

/* Code to evaluate ackley's function */
double Functions_Code::calc_ackley (double *x)
{
    int i;
    double sum1, sum2, res;
    sum1 = 0.0;
    sum2 = 0.0;
    for (i=0; i<nreal; i++)
    {
        sum1 += x[i]*x[i];
        sum2 += cos(2.0*PI*x[i]);
    }
    sum1 = -0.2*sqrt(sum1/nreal);
    sum2 /= nreal;
    res = 20.0 + E - 20.0*exp(sum1) - exp(sum2);
    return (res);
}

/* Code to evaluate rastrigin's function */
double Functions_Code::calc_rastrigin (double *x)
{
    int i;
    double res;
    res = 0.0;
    for (i=0; i<nreal; i++)
    {
        res += (x[i]*x[i] - 10.0*cos(2.0*PI*x[i]) + 10.0);
    }
    return (res);
}

/* Code to evaluate weierstrass's function */
double Functions_Code::calc_weierstrass (double *x)
{
    int i, j;
    double res;
    double sum;
    double a, b;
    int k_max;
    a = 0.5;
    b = 3.0;
    k_max = 20;
    res = 0.0;
    for (i=0; i<nreal; i++)
    {
        sum = 0.0;
        for (j=0; j<=k_max; j++)
        {
            sum += pow(a,j)*cos(2.0*PI*pow(b,j)*(x[i]+0.5));
        }
        res += sum;
    }
    return (res);
}

/* Code to evaluate griewank's function */
double Functions_Code::calc_griewank (double *x)
{
    int i;
    double s, p;
    double res;
    s = 0.0;
    p = 1.0;
    for (i=0; i<nreal; i++)
    {
        s += x[i]*x[i];
        p *= cos(x[i]/sqrt(1.0+i));
    }
    res = 1.0 + s/4000.0 - p;
    return (res);
}

/* code to evaluate sphere function */
double Functions_Code::calc_sphere (double *x)
{
    int i;
    double res;
    res = 0.0;
    for (i=0; i<nreal; i++)
    {
        res += x[i]*x[i];
    }
    return (res);
}

/* Code to evaluate schwefel's function */
double Functions_Code::calc_schwefel (double *x)
{
    int i, j;
    double sum1, sum2;
    sum1 = 0.0;
    for (i=0; i<nreal; i++)
    {
        sum2 = 0.0;
        for (j=0; j<=i; j++)
        {
            sum2 += x[j];
        }
        sum1 += sum2*sum2;
    }
    return (sum1);
}

/* Code to evaluate rosenbrock's function */
double Functions_Code::calc_rosenbrock (double *x)
{
    int i;
    double res;
    res = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        res += 100.0*pow((x[i]*x[i]-x[i+1]),2.0) + 1.0*pow((x[i]-1.0),2.0);
    }
    return (res);
}

/* Code to evaluate schaffer's function and rounding-off variables */
double Functions_Code::nc_schaffer (double x, double y)
{
    int i;
    int a;
    double b;
    double res;
    double temp1, temp2;
    double t1[2], t2[2];
    t1[0] = x;
    t1[1] = y;
    for (i=0; i<2; i++)
    {
        if (fabs(t1[i]) >= 0.5)
        {
            res = 2.0*t1[i];
            a = res;
            b = fabs(res-a);
            if (b<0.5)
            {
                t2[i] = a/2.0;
            }
            else
            {
                if (res<=0.0)
                {
                    t2[i] = (a-1.0)/2.0;
                }
                else
                {
                    t2[i] = (a+1.0)/2.0;
                }
            }
        }
        else
        {
            t2[i] = t1[i];
        }
    }
    temp1 = pow((sin(sqrt(pow(t2[0],2.0)+pow(t2[1],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(t2[0],2.0)+pow(t2[1],2.0));
    res = 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    return (res);
}

/* Code to evaluate rastrigin's function and rounding-off variables */
double Functions_Code::nc_rastrigin (double *x)
{
    int i;
    int a;
    double b;
    double res;
    for (i=0; i<nreal; i++)
    {
        if (fabs(x[i]) >= 0.5)
        {
            res = 2.0*x[i];
            a = res;
            b = fabs(res-a);
            if (b<0.5)
            {
                temp_x4[i] = a/2.0;
            }
            else
            {
                if (res<=0.0)
                {
                    temp_x4[i] = (a-1.0)/2.0;
                }
                else
                {
                    temp_x4[i] = (a+1.0)/2.0;
                }
            }
        }
        else
        {
            temp_x4[i] = x[i];
        }
    }
    res = 0.0;
    for (i=0; i<nreal; i++)
    {
        res += (temp_x4[i]*temp_x4[i] - 10.0*cos(2.0*PI*temp_x4[i]) + 10.0);
    }
    return (res);
}

//////////////////////////////////////// MANIPULA MEMORIA

/* Code to allocate memory to global variables being used in evaluation of functions */
void Functions_Code::allocate_memory ()
{
    int i, j, k;
    norm_x = (double *)malloc(nreal*sizeof(double));
    norm_f = (double *)malloc(nfunc*sizeof(double));
    trans_x = (double *)malloc(nreal*sizeof(double));
    basic_f = (double *)malloc(nfunc*sizeof(double));
    temp_x1 = (double *)malloc(nreal*sizeof(double));
    temp_x2 = (double *)malloc(nreal*sizeof(double));
    temp_x3 = (double *)malloc(nreal*sizeof(double));
    temp_x4 = (double *)malloc(nreal*sizeof(double));
    weight = (double *)malloc(nfunc*sizeof(double));
    sigma = (double *)malloc(nfunc*sizeof(double));
    lambda = (double *)malloc(nfunc*sizeof(double));
    bias = (double *)malloc(nfunc*sizeof(double));
    o = (long double **)malloc(nfunc*sizeof(long double));
    l = (long double ***)malloc(nfunc*sizeof(long double));
    g = (double **)malloc(nreal*sizeof(double));
    for (i=0; i<nfunc; i++)
    {
        o[i] = (long double *)malloc(nreal*sizeof(long double));
        l[i] = (long double **)malloc(nreal*sizeof(long double));
    }
    for (i=0; i<nreal; i++)
    {
        g[i] = (double *)malloc(nreal*sizeof(double));
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            l[i][j] = (long double *)malloc(nreal*sizeof(long double));
        }
    }
    /* Do some trivial (common) initialization here itself */
	C = 2000.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 5.0;
        trans_x[i] = 0.0;
        temp_x1[i] = 0.0;
        temp_x2[i] = 0.0;
        temp_x3[i] = 0.0;
        temp_x4[i] = 0.0;
        for (j=0; j<nreal; j++)
        {
            if (i==j)
            {
                g[i][j]=1.0;
            }
            else
            {
                g[i][j]=0.0;
            }
        }
    }
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] = 0.0;
        norm_f[i] = 0.0;
        weight[i] = 1.0/(double)nfunc;
        sigma[i] = 1.0;
        lambda[i] = 1.0;
        bias[i] = 100.0*(double)i;
        for (j=0; j<nreal; j++)
        {
            o[i][j] = 0.0;
            for (k=0; k<nreal; k++)
            {
                if (j==k)
                {
                    l[i][j][k] = 1.0;
                }
                else
                {
                    l[i][j][k] = 0.0;
                }
            }
        }
    }
    return;
}

/* Code to transform a variable vector based on function index 'count' */
void Functions_Code::transform (double *x, int count)
{
    int i, j;
    for (i=0; i<nreal; i++)
    {
        temp_x1[i] = x[i] - o[count][i];
    }
    for (i=0; i<nreal; i++)
    {
        temp_x2[i] = temp_x1[i]/lambda[count];
    }
    for (j=0; j<nreal; j++)
    {
        temp_x3[j] = 0.0;
        for (i=0; i<nreal; i++)
        {
            temp_x3[j] += g[i][j]*temp_x2[i];
        }
    }
    for (j=0; j<nreal; j++)
    {
        trans_x[j] = 0.0;
        for (i=0; i<nreal; i++)
        {
            trans_x[j] += l[count][i][j]*temp_x3[i];
        }
    }
    return;
}

/* Code to transform a vector (with elements 5.0) based on function index 'count' */
void Functions_Code::transform_norm (int count)
{
    int i, j;
    for (i=0; i<nreal; i++)
    {
        temp_x2[i] = 5.0/lambda[count];
    }
    for (j=0; j<nreal; j++)
    {
        temp_x3[j] = 0.0;
        for (i=0; i<nreal; i++)
        {
            temp_x3[j] += g[i][j]*temp_x2[i];
        }
    }
    for (j=0; j<nreal; j++)
    {
        trans_x[j] = 0.0;
        for (i=0; i<nreal; i++)
        {
            trans_x[j] += l[count][i][j]*temp_x3[i];
        }
    }
    return;
}

/* Code to compute the weights for a variable vector */
void Functions_Code::calc_weight (double *x)
{
    int i, j;
    double sum;
    double max;
    max = -INF;
    for (i=0; i<nfunc; i++)
    {
        sum = 0.0;
        for (j=0; j<nreal; j++)
        {
            sum += (x[j]-o[i][j])*(x[j]-o[i][j]);
        }
        weight[i] = exp(-(sum)/(2.0*nreal*sigma[i]*sigma[i]));
        max = maximum(max,weight[i]);
    }
    sum = 0.0;
    for (i=0; i<nfunc; i++)
    {
        if (weight[i]!=max)
        {
            weight[i] *= (1.0 - pow(max,10.0));
        }
        sum += weight[i];
    }
    if (sum==0.0)
    {
        for (i=0; i<nfunc; i++)
        {
            weight[i] = 1.0/(double)nfunc;
        }
    }
    else
    {
        for (i=0; i<nfunc; i++)
        {
            weight[i] /= sum;
        }
    }
    return;
}

/* Code to free the allocated memory */
void Functions_Code::free_memory()
{
    int i, j;
    free (norm_x);
    free (norm_f);
    free (trans_x);
    free (basic_f);
    free (temp_x1);
    free (temp_x2);
    free (temp_x3);
    free (temp_x4);
    free (weight);
    free (sigma);
    free (lambda);
    free (bias);
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            free (l[i][j]);
        }
    }
    for (i=0; i<nfunc; i++)
    {
        free (o[i]);
        free (l[i]);
    }
    for (i=0; i<nreal; i++)
    {
        free (g[i]);
    }
    free (o);
    free (l);
    free (g);
    return;
}

//////////////////////////////////////// INICIALIZA FUNCOES
void Functions_Code::initialize_f1()
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/sphere_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'sphere_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}


void Functions_Code::initialize_f2()
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/schwefel_102_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'schwefel_102_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}

void Functions_Code::initialize_f3()
{
    int i, j;
    FILE *fpt;
    if (nreal==2) fpt = fopen("input_data/elliptic_M_D2.txt","r");
    if (nreal==10) fpt = fopen("input_data/elliptic_M_D10.txt","r");
    if (nreal==30) fpt = fopen("input_data/elliptic_M_D30.txt","r");
    if (nreal==50) fpt = fopen("input_data/elliptic_M_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(1);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&g[i][j]);
           //printf("\n G[%d][%d] = %LE",i+1,j+1,g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/high_cond_elliptic_rot_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'high_cond_elliptic_rot_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}


void Functions_Code::initialize_f4()
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/schwefel_102_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'schwefel_102_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -450.0;
    return;
}

void Functions_Code::initialize_f5()
{
    int i, j;
    int index;
    FILE *fpt;
    char c;
    A_f5 = (double **)malloc(nreal*sizeof(double));
    for (i=0; i<nreal; i++)
    {
        A_f5[i] = (double *)malloc(nreal*sizeof(double));
    }
    B_f5 = (double *)malloc(nreal*sizeof(double));
    fpt = fopen("input_data/schwefel_206_data.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&A_f5[i][j]);
           //printf("\n A[%d][%d] = %LE",i+1,j+1,A_f5[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
    }
    fclose(fpt);
    if (nreal%4==0)
    {
        index = nreal/4;
    }
    else
    {
        index = nreal/4 + 1;
    }
    for (i=0; i<index; i++)
    {
        o[0][i] = -100.0;
    }
    index = (3*nreal)/4 - 1;
    for (i=index; i<nreal; i++)
    {
        o[0][i] = 100.0;
    }
    for (i=0; i<nreal; i++)
    {
        B_f5[i] = 0.0;
        for (j=0; j<nreal; j++)
        {
            B_f5[i] += A_f5[i][j]*o[0][j];
        }
    }
    bias[0] = -310.0;
    return;
}

void Functions_Code::initialize_f6()
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/rosenbrock_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'rosenbrock_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
            o[i][j] -= 1.0;
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = 390.0;
    return;
}

void Functions_Code::initialize_f7()
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/griewank_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/griewank_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/griewank_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/griewank_M_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(1);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&g[i][j]);
           //printf("\n G[%d][%d] = %LE",i+1,j+1,g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/griewank_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'griewank_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -180.0;
    return;
}

void Functions_Code::initialize_f8()
{
    int i, j;
    int index;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/ackley_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/ackley_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/ackley_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/ackley_M_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(1);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&g[i][j]);
           //printf("\n M[%d][%d] = %LE",i+1,j+1,g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/ackley_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'ackley_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    index = nreal/2;
    for (i=1; i<=index; i++)
    {
        o[0][2*i-2] = -32.0;
    }
    bias[0] = -140.0;
    return;
}

void Functions_Code::initialize_f9()
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/rastrigin_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'rastrigin_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -330.0;
    return;
}

void Functions_Code::initialize_f10()
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/rastrigin_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/rastrigin_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/rastrigin_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/rastrigin_M_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(1);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&g[i][j]);
           //printf("\n M[%d][%d] = %LE",i+1,j+1,g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/rastrigin_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'rastrigin_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -330.0;
    return;
}

void Functions_Code::initialize_f11()
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/weierstrass_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/weierstrass_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/weierstrass_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/weierstrass_M_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(1);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&g[i][j]);
           //printf("\n M[%d][%d] = %LE",i+1,j+1,g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/weierstrass_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'weierstrass_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = 90.0;
    return;
}

void Functions_Code::initialize_f12()
{
    int i, j;
    FILE *fpt;
    char c;
    A_f12 = (double **)malloc(nreal*sizeof(double));
    B_f12 = (double **)malloc(nreal*sizeof(double));
    alpha_f12 = (double *)malloc(nreal*sizeof(double));
    for (i=0; i<nreal; i++)
    {
        A_f12[i] = (double *)malloc(nreal*sizeof(double));
        B_f12[i] = (double *)malloc(nreal*sizeof(double));
    }
    fpt = fopen("input_data/schwefel_213_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'schwefel_213_data.txt' for reading \n");
        exit(1);
    }
    /* Reading A */
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&A_f12[i][j]);
           //printf("\n A[%d][%d] = %LE",i+1,j+1,A_f12[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
    }
    if (i!=100)
    {
        for (i=nreal; i<100; i++)
        {
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while(c!='\n');
        }
    }
    /* Reading B */
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&B_f12[i][j]);
           //printf("\n B[%d][%d] = %LE",i+1,j+1,B_f12[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
    }
    if (i!=100)
    {
        for (i=nreal; i<100; i++)
        {
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while(c!='\n');
        }
    }
    /* Reading alpha */
    for (i=0; i<nreal; i++)
    {
        fscanf(fpt,"%f",&alpha_f12[i]);
       //printf("\n alpha[%d] = %LE",i+1,alpha_f12[i]);
    }
    fclose(fpt);
    bias[0] = -460.0;
    return;
}

void Functions_Code::initialize_f13()
{
    int i, j;
    FILE *fpt;
    fpt = fopen("input_data/EF8F2_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'EF8F2_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
            o[i][j] -= 1.0;
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -130.0;
    return;
}

void Functions_Code::initialize_f14()
{
    int i, j;
    FILE *fpt;
    if (nreal==2)    fpt = fopen("input_data/E_ScafferF6_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/E_ScafferF6_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/E_ScafferF6_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/E_ScafferF6_M_D50.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file for reading \n");
        exit(1);
    }
    for (i=0; i<nreal; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%f",&g[i][j]);
           //printf("\n M[%d][%d] = %LE",i+1,j+1,g[i][j]);
        }
    }
    fclose(fpt);
    fpt = fopen("input_data/E_ScafferF6_func_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'E_ScafferF6_func_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
    }
    fclose(fpt);
    bias[0] = -300.0;
    return;
}

void Functions_Code::initialize_f15()
{
    int i, j;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func1_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func1_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    lambda[0] = 1.0;
    lambda[1] = 1.0;
    lambda[2] = 10.0;
    lambda[3] = 10.0;
    lambda[4] = 1.0/12.0;
    lambda[5] = 1.0/12.0;
    lambda[6] = 5.0/32.0;
    lambda[7] = 5.0/32.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 120.0;
    return;
}

void Functions_Code::initialize_f16()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func1_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func1_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
//           printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func1_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func1_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func1_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func1_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    lambda[0] = 1.0;
    lambda[1] = 1.0;
    lambda[2] = 10.0;
    lambda[3] = 10.0;
    lambda[4] = 1.0/12.0;
    lambda[5] = 1.0/12.0;
    lambda[6] = 5.0/32.0;
    lambda[7] = 5.0/32.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 120.0;
    return;
}

void Functions_Code::initialize_f17()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func1_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func1_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func1_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func1_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func1_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func1_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    lambda[0] = 1.0;
    lambda[1] = 1.0;
    lambda[2] = 10.0;
    lambda[3] = 10.0;
    lambda[4] = 1.0/12.0;
    lambda[5] = 1.0/12.0;
    lambda[6] = 5.0/32.0;
    lambda[7] = 5.0/32.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 120.0;
    return;
}

void Functions_Code::initialize_f18()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func2_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func2_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func2_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func2_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func2_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func2_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    for (i=0; i<nreal; i++)
    {
        o[nfunc-1][i] = 0.0;
    }
    sigma[0] = 1.0;
    sigma[1] = 2.0;
    sigma[2] = 1.5;
    sigma[3] = 1.5;
    sigma[4] = 1.0;
    sigma[5] = 1.0;
    sigma[6] = 1.5;
    sigma[7] = 1.5;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 5.0/16.0;
    lambda[1] = 5.0/32.0;
    lambda[2] = 2.0;
    lambda[3] = 1.0;
    lambda[4] = 1.0/10.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 20.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/6.0;
    lambda[9] = 1.0/12.0;
    global_bias = 10.0;
    return;
}

void Functions_Code::initialize_f19()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func2_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func2_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func2_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func2_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func2_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func2_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    for (i=0; i<nreal; i++)
    {
        o[nfunc-1][i] = 0.0;
    }
    sigma[0] = 0.1;
    sigma[1] = 2.0;
    sigma[2] = 1.5;
    sigma[3] = 1.5;
    sigma[4] = 1.0;
    sigma[5] = 1.0;
    sigma[6] = 1.5;
    sigma[7] = 1.5;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 0.5/32.0;
    lambda[1] = 5.0/32.0;
    lambda[2] = 2.0;
    lambda[3] = 1.0;
    lambda[4] = 1.0/10.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 20.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/6.0;
    lambda[9] = 1.0/12.0;
    global_bias = 10.0;
    return;
}

void Functions_Code::initialize_f20()
{
    int i, j, k;
    int index;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func2_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func2_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    index = nreal/2;
    for (i=1; i<=index; i++)
    {
        o[0][2*i-1] = 5.0;
    }
    if (nreal==2)    fpt = fopen("input_data/hybrid_func2_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func2_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func2_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func2_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    for (i=0; i<nreal; i++)
    {
        o[nfunc-1][i] = 0.0;
    }
    sigma[0] = 1.0;
    sigma[1] = 2.0;
    sigma[2] = 1.5;
    sigma[3] = 1.5;
    sigma[4] = 1.0;
    sigma[5] = 1.0;
    sigma[6] = 1.5;
    sigma[7] = 1.5;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 5.0/16.0;
    lambda[1] = 5.0/32.0;
    lambda[2] = 2.0;
    lambda[3] = 1.0;
    lambda[4] = 1.0/10.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 20.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/6.0;
    lambda[9] = 1.0/12.0;
    global_bias = 10.0;
    return;
}

void Functions_Code::initialize_f21()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func3_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func3_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func3_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func3_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func3_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func3_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    sigma[0] = 1.0;
    sigma[1] = 1.0;
    sigma[2] = 1.0;
    sigma[3] = 1.0;
    sigma[4] = 1.0;
    sigma[5] = 2.0;
    sigma[6] = 2.0;
    sigma[7] = 2.0;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 1.0/4.0;
    lambda[1] = 1.0/20.0;
    lambda[2] = 5.0;
    lambda[3] = 1.0;
    lambda[4] = 5.0;
    lambda[5] = 1.0;
    lambda[6] = 50.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/8.0;
    lambda[9] = 1.0/40.0;
    global_bias = 360.0;
    return;
}

void Functions_Code::initialize_f22()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func3_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func3_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func3_HM_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func3_HM_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func3_HM_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func3_HM_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    sigma[0] = 1.0;
    sigma[1] = 1.0;
    sigma[2] = 1.0;
    sigma[3] = 1.0;
    sigma[4] = 1.0;
    sigma[5] = 2.0;
    sigma[6] = 2.0;
    sigma[7] = 2.0;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 1.0/4.0;
    lambda[1] = 1.0/20.0;
    lambda[2] = 5.0;
    lambda[3] = 1.0;
    lambda[4] = 5.0;
    lambda[5] = 1.0;
    lambda[6] = 50.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/8.0;
    lambda[9] = 1.0/40.0;
    global_bias = 360.0;
    return;
}

void Functions_Code::initialize_f23()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func3_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func3_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
           //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func3_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func3_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func3_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func3_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
               //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
                /*printf("\n got here \n");*/
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    sigma[0] = 1.0;
    sigma[1] = 1.0;
    sigma[2] = 1.0;
    sigma[3] = 1.0;
    sigma[4] = 1.0;
    sigma[5] = 2.0;
    sigma[6] = 2.0;
    sigma[7] = 2.0;
    sigma[8] = 2.0;
    sigma[9] = 2.0;
    lambda[0] = 1.0/4.0;
    lambda[1] = 1.0/20.0;
    lambda[2] = 5.0;
    lambda[3] = 1.0;
    lambda[4] = 5.0;
    lambda[5] = 1.0;
    lambda[6] = 50.0;
    lambda[7] = 10.0;
    lambda[8] = 1.0/8.0;
    lambda[9] = 1.0/40.0;
    global_bias = 360.0;
    return;
}

void Functions_Code::initialize_f24()
{
    int i, j, k;
    FILE *fpt;
    char c;
    fpt = fopen("input_data/hybrid_func4_data.txt","r");
    if (fpt==NULL)
    {
        fprintf(stderr,"\n Error: Cannot open input file 'hybrid_func4_data.txt' for reading \n");
        exit(1);
    }
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            fscanf(fpt,"%Lf",&o[i][j]);
            //printf("\n O[%d][%d] = %LE",i+1,j+1,o[i][j]);
        }
        do
        {
            fscanf(fpt,"%c",&c);
        }
        while (c!='\n');
       //printf("\n");
    }
    fclose(fpt);
    if (nreal==2)    fpt = fopen("input_data/hybrid_func4_M_D2.txt","r");
    if (nreal==10)    fpt = fopen("input_data/hybrid_func4_M_D10.txt","r");
    if (nreal==30)    fpt = fopen("input_data/hybrid_func4_M_D30.txt","r");
    if (nreal==50)    fpt = fopen("input_data/hybrid_func4_M_D50.txt","r");
    for (i=0; i<nfunc; i++)
    {
        for (j=0; j<nreal; j++)
        {
            for (k=0; k<nreal; k++)
            {
                fscanf(fpt,"%Lf",&l[i][j][k]);
                //printf("\n M[%d][%d][%d] = %LE",i+1,j+1,k+1,l[i][j][k]);
            }
            do
            {
                fscanf(fpt,"%c",&c);
            }
            while (c!='\n');
        }
       //printf("\n");
    }
    fclose(fpt);
    for (i=0; i<nfunc; i++)
    {
        sigma[i] = 2.0;
    }
    lambda[0] = 10.0;
    lambda[1] = 1.0/4.0;
    lambda[2] = 1.0;
    lambda[3] = 5.0/32.0;
    lambda[4] = 1.0;
    lambda[5] = 1.0/20.0;
    lambda[6] = 1.0/10.0;
    lambda[7] = 1.0;
    lambda[8] = 1.0/20.0;
    lambda[9] = 1.0/20.0;
    global_bias = 260.0;
    return;
}



///////////////////////////////// FAZ A CHAMADA PARA AS FUNCOES
double Functions_Code::calc_benchmark_func_f1(double *x)
{
	//printf("\noi\n");
    double res;
    transform (x, 0);
	//printf("\n %f %f %f %f\n", x[0], x[1], trans_x[0], trans_x[1]);
    basic_f[0] = calc_sphere (trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f2(double *x)
{
    double res;
    transform (x, 0);
    basic_f[0] = calc_schwefel (trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f3(double *x)
{
    int i;
    double res;
    transform (x, 0);
    basic_f[0] = 0.0;
    for (i=0; i<nreal; i++)
    {
        basic_f[0] += trans_x[i]*trans_x[i]*pow(1.0e6,i/(nreal-1.0));
    }
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f4(double *x)
{
    double res;
    transform (x, 0);
    basic_f[0] = calc_schwefel(trans_x)*(1.0 + 0.4*fabs(randomnormaldeviate()));
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f5(double *x)
{
    int i, j;
    double res;
    basic_f[0] = -INF;
    for (i=0; i<nreal; i++)
    {
        res=0.0;
        for (j=0; j<nreal; j++)
        {
            res += A_f5[i][j]*x[j];
        }
        res = fabs(res-B_f5[i]);
        if (basic_f[0] < res)
        {
            basic_f[0] = res;
        }
    }
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f6(double *x)
{
    double res;
    transform (x, 0);
    basic_f[0] = calc_rosenbrock(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f7(double *x)
{
    double res;
    transform (x, 0);
    basic_f[0] = calc_griewank(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f8(double *x)
{
    double res;
    transform (x, 0);
    basic_f[0] = calc_ackley(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f9(double *x)
{
    double res;
    transform (x, 0);
    basic_f[0] = calc_rastrigin(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f10(double *x)
{
    double res;
    transform (x, 0);
    basic_f[0] = calc_rastrigin(trans_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f11(double *x)
{
    int i;
    double res;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 0);
    basic_f[0] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f12(double *x)
{
    double res;
    double sum1, sum2;
    int i, j;
    basic_f[0] = 0.0;
    for (i=0; i<nreal; i++)
    {
        sum1 = 0.0;
        sum2 = 0.0;
        for (j=0; j<nreal; j++)
        {
            sum1 += A_f12[i][j]*sin(alpha_f12[j]) + B_f12[i][j]*cos(alpha_f12[j]);
            sum2 += A_f12[i][j]*sin(x[j]) + B_f12[i][j]*cos(x[j]);
        }
        basic_f[0] += pow((sum1-sum2),2.0);
    }
    res = basic_f[0] + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f13(double *x)
{
    int i;
    double temp;
    double res;
    transform(x,0);
    res = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        res += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    res += (temp*temp)/4000.0 - cos(temp) + 1.0 + bias[0];
    return (res);
}

double Functions_Code::calc_benchmark_func_f14(double *x)
{
    int i;
    double temp1, temp2;
    double res;
    transform(x,0);
    res = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        res += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    res += 0.5 + (temp1-0.5)/(pow(temp2,2.0)) + bias[0];
    return (res);
}

void Functions_Code::calc_benchmark_norm_f15()
{
    int i;
    transform_norm (0);    norm_f[0] = calc_rastrigin(trans_x);
    transform_norm (1);    norm_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (2);    norm_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (3);    norm_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (4);    norm_f[4] = calc_griewank(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);    norm_f[6] = calc_ackley(trans_x);
    transform_norm (7);    norm_f[7] = calc_ackley(trans_x);
    transform_norm (8);    norm_f[8] = calc_sphere(trans_x);
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f15(double *x)
{
    int i;
    double res;
    transform (x, 0);    basic_f[0] = calc_rastrigin(trans_x);
    transform (x, 1);    basic_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 2);    basic_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 3);    basic_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 4);    basic_f[4] = calc_griewank(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);
    transform (x, 6);    basic_f[6] = calc_ackley(trans_x);
    transform (x, 7);    basic_f[7] = calc_ackley(trans_x);
    transform (x, 8);    basic_f[8] = calc_sphere(trans_x);
    transform (x, 9);    basic_f[9] = calc_sphere(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f16()
{
    int i;
    transform_norm (0);    norm_f[0] = calc_rastrigin(trans_x);
    transform_norm (1);    norm_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (2);    norm_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (3);    norm_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (4);    norm_f[4] = calc_griewank(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);    norm_f[6] = calc_ackley(trans_x);
    transform_norm (7);    norm_f[7] = calc_ackley(trans_x);
    transform_norm (8);    norm_f[8] = calc_sphere(trans_x);
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f16(double *x)
{
    int i;
    double res;
    transform (x, 0);    basic_f[0] = calc_rastrigin(trans_x);
    transform (x, 1);    basic_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 2);    basic_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 3);    basic_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 4);    basic_f[4] = calc_griewank(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);
    transform (x, 6);    basic_f[6] = calc_ackley(trans_x);
    transform (x, 7);    basic_f[7] = calc_ackley(trans_x);
    transform (x, 8);    basic_f[8] = calc_sphere(trans_x);
    transform (x, 9);    basic_f[9] = calc_sphere(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f17()
{
    int i;
    transform_norm (0);    norm_f[0] = calc_rastrigin(trans_x);
    transform_norm (1);    norm_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (2);    norm_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (3);    norm_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (4);    norm_f[4] = calc_griewank(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);    norm_f[6] = calc_ackley(trans_x);
    transform_norm (7);    norm_f[7] = calc_ackley(trans_x);
    transform_norm (8);    norm_f[8] = calc_sphere(trans_x);
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f17(double *x)
{
    int i;
    double res;
    transform (x, 0);    basic_f[0] = calc_rastrigin(trans_x);
    transform (x, 1);    basic_f[1] = calc_rastrigin(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 2);    basic_f[2] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 3);    basic_f[3] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 4);    basic_f[4] = calc_griewank(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);
    transform (x, 6);    basic_f[6] = calc_ackley(trans_x);
    transform (x, 7);    basic_f[7] = calc_ackley(trans_x);
    transform (x, 8);    basic_f[8] = calc_sphere(trans_x);
    transform (x, 9);    basic_f[9] = calc_sphere(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = 0.0;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    res = res*(1.0 + 0.2*fabs(randomnormaldeviate())) + global_bias;
    return (res);
}

void Functions_Code::calc_benchmark_norm_f18()
{
    int i;
    transform_norm (0);    norm_f[0] = calc_ackley(trans_x);
    transform_norm (1);    norm_f[1] = calc_ackley(trans_x);
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm (4);    norm_f[4] = calc_sphere(trans_x);
    transform_norm (5);    norm_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f18(double *x)
{
    int i;
    double res;
    transform (x, 0);    basic_f[0] = calc_ackley(trans_x);
    transform (x, 1);    basic_f[1] = calc_ackley(trans_x);
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);    basic_f[4] = calc_sphere(trans_x);
    transform (x, 5);    basic_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f19()
{
    int i;
    transform_norm (0);    norm_f[0] = calc_ackley(trans_x);
    transform_norm (1);    norm_f[1] = calc_ackley(trans_x);
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm (4);    norm_f[4] = calc_sphere(trans_x);
    transform_norm (5);    norm_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f19(double *x)
{
    int i;
    double res;
    transform (x, 0);    basic_f[0] = calc_ackley(trans_x);
    transform (x, 1);    basic_f[1] = calc_ackley(trans_x);
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);    basic_f[4] = calc_sphere(trans_x);
    transform (x, 5);    basic_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f20()
{
    int i;
    transform_norm (0);    norm_f[0] = calc_ackley(trans_x);
    transform_norm (1);    norm_f[1] = calc_ackley(trans_x);
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm (4);    norm_f[4] = calc_sphere(trans_x);
    transform_norm (5);    norm_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f20(double *x)
{
    int i;
    double res;
    transform (x, 0);    basic_f[0] = calc_ackley(trans_x);
    transform (x, 1);    basic_f[1] = calc_ackley(trans_x);
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);    basic_f[4] = calc_sphere(trans_x);
    transform (x, 5);    basic_f[5] = calc_sphere(trans_x);
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f21()
{
    int i;
    double temp1, temp2, temp;
    transform_norm (0);
    norm_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm(4);
    norm_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm(5);
    norm_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f21(double *x)
{
    int i;
    double temp1, temp2, temp;
    double res;
    transform (x, 0);
    basic_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);
    basic_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform(x, 5);
    basic_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f22()
{
    int i;
    double temp1, temp2, temp;
    transform_norm (0);
    norm_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm(4);
    norm_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm(5);
    norm_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f22(double *x)
{
    int i;
    double temp1, temp2, temp;
    double res;
    transform (x, 0);
    basic_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (x, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (x, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (x, 4);
    basic_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform(x, 5);
    basic_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (x, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (x, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (x, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f23()
{
    int i;
    double temp1, temp2, temp;
    transform_norm (0);
    norm_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);    norm_f[2] = calc_rastrigin(trans_x);
    transform_norm (3);    norm_f[3] = calc_rastrigin(trans_x);
    transform_norm(4);
    norm_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm(5);
    norm_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (6);    norm_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (7);    norm_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (8);    norm_f[8] = calc_griewank(trans_x);
    transform_norm (9);    norm_f[9] = calc_griewank(trans_x);
    return;
}

double Functions_Code::calc_benchmark_func_f23(double *x)
{
    int i;
    double temp1, temp2, temp;
    double res;
    int a;
    double b;
    for (i=0; i<nreal; i++)
    {
        if (fabs(x[i]-o[0][i]) >= 0.5)
        {
            res = 2.0*x[i];
            a = res;
            b = fabs(res-a);
            if (b<0.5)
            {
                temp_x4[i] = a/2.0;
            }
            else
            {
                if (res<=0.0)
                {
                    temp_x4[i] = (a-1.0)/2.0;
                }
                else
                {
                    temp_x4[i] = (a+1.0)/2.0;
                }
            }
        }
        else
        {
            temp_x4[i] = x[i];
        }
    }
    transform (temp_x4, 0);
    basic_f[0] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[0] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (temp_x4, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform (temp_x4, 2);    basic_f[2] = calc_rastrigin(trans_x);
    transform (temp_x4, 3);    basic_f[3] = calc_rastrigin(trans_x);
    transform (temp_x4, 4);
    basic_f[4] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[4] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform(temp_x4, 5);
    basic_f[5] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[5] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform (temp_x4, 6);    basic_f[6] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (temp_x4, 7);    basic_f[7] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform (temp_x4, 8);    basic_f[8] = calc_griewank(trans_x);
    transform (temp_x4, 9);    basic_f[9] = calc_griewank(trans_x);
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(temp_x4);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}

void Functions_Code::calc_benchmark_norm_f24()
{
    int i;
    double temp1, temp2, temp;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    transform_norm (0);    norm_f[0] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);
    transform_norm (1);
    norm_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    norm_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    transform_norm (2);
    norm_f[2] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        norm_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    norm_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    transform_norm (3);    norm_f[3] = calc_ackley(trans_x);
    transform_norm (4);    norm_f[4] = calc_rastrigin(trans_x);
    transform_norm (5);    norm_f[5] = calc_griewank(trans_x);
    transform_norm (6);
    norm_f[6] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        norm_f[6] += nc_schaffer(trans_x[i], trans_x[i+1]);
    }
    norm_f[6] += nc_schaffer(trans_x[nreal-1], trans_x[0]);
    transform_norm(7);    norm_f[7] = nc_rastrigin(trans_x);
    transform_norm (8);
    norm_f[8] = 0.0;
    for (i=0; i<nreal; i++)
    {
        norm_f[8] += trans_x[i]*trans_x[i]*pow(1.0e6,i/(nreal-1.0));
    }
    transform_norm (9);    norm_f[9] = calc_sphere(trans_x)*(1.0 + 0.1*fabs(randomnormaldeviate()));
    return;
}

double Functions_Code::calc_benchmark_func_f24(double *x)
{
    int i;
    double temp1, temp2, temp;
    double res;
    for (i=0; i<nreal; i++)
    {
        norm_x[i] = 0.0;
    }
    /* First function */
    transform (x, 0);    basic_f[0] = calc_weierstrass(trans_x) - calc_weierstrass(norm_x);

    /* Second function */
    transform (x, 1);
    basic_f[1] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp1 = pow((sin(sqrt(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0)))),2.0);
        temp2 = 1.0 + 0.001*(pow(trans_x[i],2.0)+pow(trans_x[i+1],2.0));
        basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));
    }
    temp1 = pow((sin(sqrt(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0)))),2.0);
    temp2 = 1.0 + 0.001*(pow(trans_x[nreal-1],2.0)+pow(trans_x[0],2.0));
    basic_f[1] += 0.5 + (temp1-0.5)/(pow(temp2,2.0));

    /* Third Function */
    transform (x, 2);
    basic_f[2] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        temp = 100.0*pow((trans_x[i]*trans_x[i]-trans_x[i+1]),2.0) + 1.0*pow((trans_x[i]-1.0),2.0);
        basic_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;
    }
    temp = 100.0*pow((trans_x[nreal-1]*trans_x[nreal-1]-trans_x[0]),2.0) + 1.0*pow((trans_x[nreal-1]-1.0),2.0);
    basic_f[2] += (temp*temp)/4000.0 - cos(temp) + 1.0;

    transform (x, 3);    basic_f[3] = calc_ackley(trans_x);
    transform (x, 4);    basic_f[4] = calc_rastrigin(trans_x);
    transform (x, 5);    basic_f[5] = calc_griewank(trans_x);

    /* Seventh Function */
    transform (x, 6);
    basic_f[6] = 0.0;
    for (i=0; i<nreal-1; i++)
    {
        basic_f[6] += nc_schaffer(trans_x[i], trans_x[i+1]);
    }
    basic_f[6] += nc_schaffer(trans_x[nreal-1], trans_x[0]);

    transform (x, 7);    basic_f[7] = nc_rastrigin(trans_x);

    transform (x, 8);
    basic_f[8] = 0.0;
    for (i=0; i<nreal; i++)
    {
        basic_f[8] += trans_x[i]*trans_x[i]*pow(1.0e6,i/(nreal-1.0));
    }
    transform (x, 9);    basic_f[9] = (calc_sphere(trans_x))*(1.0 + 0.1*fabs(randomnormaldeviate()));
    for (i=0; i<nfunc; i++)
    {
        basic_f[i] *= C/norm_f[i];
    }
    calc_weight(x);
    res = global_bias;
    for (i=0; i<nfunc; i++)
    {
        res += weight[i]*(basic_f[i]+bias[i]);
    }
    return (res);
}


//Inicializa a funcao correta
void Functions_Code::initialize_f(int func){
	switch(func){
		case 1:
			initialize_f1();
		break;
		case 2:
			initialize_f2();
		break;
		case 3:
			initialize_f3();
		break;
		case 4:
			initialize_f4();
		break;
		case 5:
			initialize_f5();
		break;
		case 6:
			initialize_f6();
		break;
		case 7:
			initialize_f7();
		break;
		case 8:
			initialize_f8();
		break;
		case 9:
			initialize_f9();
		break;
		case 10:
			initialize_f10();
		break;
		case 11:
			initialize_f11();
		break;
		case 12:
			initialize_f12();
		break;
		case 13:
			initialize_f13();
		break;
		case 14:
			initialize_f14();
		break;
		case 15:
			initialize_f15();
		break;
		case 16:
			initialize_f16();
		break;
		case 17:
			initialize_f17();
		break;
		case 18:
			initialize_f18();
		break;
		case 19:
			initialize_f19();
		break;
		case 20:
			initialize_f20();
		break;
		case 21:
			initialize_f21();
		break;
		case 22:
			initialize_f22();
		break;
		case 23:
			initialize_f23();
		break;
		case 24:
			initialize_f24();
		break;
		case 25:
			initialize_f24();
		break;
	}
}

//Faz a chamada da correta funcao para o calculo da aptidao
//Inicializa a funcao correta
double Functions_Code::calc_benchmark_func(int func, double *x){
	switch(func){
		case 1:
			return calc_benchmark_func_f1(x);
		break;
		case 2:
			return calc_benchmark_func_f2(x);
		break;
		case 3:
			return calc_benchmark_func_f3(x);
		break;
		case 4:
			return calc_benchmark_func_f4(x);
		break;
		case 5:
			return calc_benchmark_func_f5(x);
		break;
		case 6:
			return calc_benchmark_func_f6(x);
		break;
		case 7:
			return calc_benchmark_func_f7(x);
		break;
		case 8:
			return calc_benchmark_func_f8(x);
		break;
		case 9:
			return calc_benchmark_func_f9(x);
		break;
		case 10:
			return calc_benchmark_func_f10(x);
		break;
		case 11:
			return calc_benchmark_func_f11(x);
		break;
		case 12:
			return calc_benchmark_func_f12(x);
		break;
		case 13:
			return calc_benchmark_func_f13(x);
		break;
		case 14:
			return calc_benchmark_func_f14(x);
		break;
		case 15:
			return calc_benchmark_func_f15(x);
		break;
		case 16:
			return calc_benchmark_func_f16(x);
		break;
		case 17:
			return calc_benchmark_func_f17(x);
		break;
		case 18:
			return calc_benchmark_func_f18(x);
		break;
		case 19:
			return calc_benchmark_func_f19(x);
		break;
		case 20:
			return calc_benchmark_func_f20(x);
		break;
		case 21:
			return calc_benchmark_func_f21(x);
		break;
		case 22:
			return calc_benchmark_func_f22(x);
		break;
		case 23:
			return calc_benchmark_func_f23(x);
		break;
		case 24:
			return calc_benchmark_func_f24(x);
		break;
		case 25:
			return calc_benchmark_func_f24(x);
		break;
	}
	return 0;
}

////////////////////////////////// MAIN
/*int main(){
	double *x;
	double f;
	int i;
	nreal = 2;
	nfunc = 1;
	allocate_memory();

	//recupera a funcao a ser otimizada
	int func;
	printf("\nNumero da funcao: ");
	scanf("%d", &func);

	initialize(func);
	x = (double *)malloc(nreal*sizeof(double));
	for (i=0; i<nreal; i++)
	{
		printf("\n Enter the value of variable x[%d] : ",i+1);
		scanf("%f",&x[i]);
	}
	f = calc_benchmark_func(func, x);
	printf("\n Objective value = %1.15LE",f);

	// Routine to free the memory allocated at run time
	free_memory();

	free (x);
	printf("\n");
}*/

}}}
