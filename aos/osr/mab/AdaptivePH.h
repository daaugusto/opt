

#ifndef ADAPTIVEPH_H_
#define ADAPTIVEPH_H_

#define C_delta		.15

#include "stdio.h"
#include "stdlib.h"

//#include <eo>
//#include <ga.h>

//DISABLED FOR THE MOMENT (see function GetGamma()).
class AdaptivePH{
public:
	//e.g. in the (1/2; 1; 3/2) case, lower is 0 and upper is 2, then step is 1/2. Starting from the lower, I build the sequence.
	AdaptivePH(unsigned _n_ops, double _v_gamma, unsigned _n_gamma=1, double lower_gamma=0, double upper_gamma=2, double _epsilon=0.1){
		n_ops=_n_ops;
		v_gamma=_v_gamma;
		n_gamma=_n_gamma;
		epsilon=_epsilon;
		times=0;
		restart=0;
		double step=(upper_gamma-lower_gamma)/((double)n_gamma+1.0);

		multiply_gm = new double[n_gamma];
		times_gm = new int[n_gamma];
		expectation_gm = new double[n_gamma];
		for(unsigned i=0; i<n_gamma; i++){
			multiply_gm[i]=lower_gamma+(((double)i+1.0)*step);
			times_gm[i]=0;
			expectation_gm[i]=0;
		}

		times_op = new int[n_ops];
		expectation_op = new double[n_ops];
		cumm_diff_op = new double[n_ops];
		max_cumm_diff_op = new double[n_ops];
		for(unsigned i=0; i<n_ops; i++){
			times_op[i]=0;
			expectation_op[i]=0;
			cumm_diff_op[i]=0;
			max_cumm_diff_op[i]=0;
		}
	}

	void Restart(){

		//reset all the info for the gammas that would have triggered this restart (including the chosen_gamma)
		//(###) for the others, the estimations are kept, to be verified
		for(int i=0; i<=chosen_gamma; i++){
			times_gm[i]=0;
			expectation_gm[i]=0;
		}

		//reset all the info about all the operators
		for(unsigned i=0; i<n_ops; i++){
			times_op[i]=0;
			expectation_op[i]=0;
			cumm_diff_op[i]=0;
			max_cumm_diff_op[i]=0;
		}
	}

	int HasOptionNotTried()
	{
		int sum=0;
		for(unsigned i=0; i<n_gamma; i++)
			if(times_gm[i]==0)
				sum++;
		return sum;
	}

	void SelectGamma(){
		chosen_gamma=0;
		return;

		chosen_gamma=-1;
		char flag;
		//if there is still any that was not used yet, select between them
		int count = HasOptionNotTried();
		if (count){
			flag='A';
			  int i = 5;//(int) (rng.uniform() * count);
				for (unsigned j=0; j < n_gamma; j++) {
					int k = (i + j) % count;
					//if (lst_option[k]->getTimes() == 0)
					if (times_gm[k]==0){
						chosen_gamma=k;
						break;
					}
				}
		}
		//else, epsilon chance of randomly select between the gamma values
		else if (count==3){//rng.flip(epsilon)){
			flag='B';
			chosen_gamma=0;//rng.random(n_gamma);
		}
		//else, the known-to-be-the-best one
		else{
			flag='C';
			double qmax=-1;
			int imax=-1;
			for(unsigned i=0; i<n_gamma; i++)
				if(expectation_gm[i]>qmax){
					qmax=expectation_gm[i];
					imax=i;
				}
			chosen_gamma=imax;
		}

		//just avoiding problems
		if(chosen_gamma==-1){
			printf(" We are in big trouble: %c \n", flag);
			exit(1);
		}
	}

	double GetGamma(int which){
		//DISABLED FOR THE MOMENT
		//return multiply_gm[which]*v_gamma;
		return v_gamma;
	}

	bool CheckPH(int op, double reward){

		//updates the general information
		expectation_op[op] = ((double)times_op[op] * expectation_op[op] + reward)/((double)times_op[op] + 1);
		times_op[op]++;

		//compute the cumulated difference between the instant reward and the average
		cumm_diff_op[op] += (reward - expectation_op[op] + C_delta);
		if (fabs(cumm_diff_op[op]) > max_cumm_diff_op[op]) max_cumm_diff_op[op] = fabs(cumm_diff_op[op]);
		double diff = fabs(max_cumm_diff_op[op] - fabs(cumm_diff_op[op]));

		//for each gamma, if it wouldn't trigger a restart, update its estimation (and keep it)
		for(unsigned i=0; i<n_gamma; i++){
			if (diff <= GetGamma(i)) {
				expectation_gm[i]= ((double)times_gm[i] * expectation_gm[i] + reward)/((double)times_gm[i] + 1);
				times_gm[i]++;
			}
		}

		//selects the chosen_gamma
		SelectGamma();

		if(diff > GetGamma(chosen_gamma)) restart=1;
		else restart=0;

		/*cout << times << " " << restart << " " << GetGamma(chosen_gamma) << " ";
		for(unsigned i=0; i<n_ops; i++)
			cout << times_op[i] << " " << expectation_op[i] << " " << cumm_diff_op[i] << " " << max_cumm_diff_op[i] << " " << diff << " " << GetGamma(chosen_gamma);
		cout << endl;
		plot 'upa' u 1:($2*1600) w l t 'Restart', 'upa' u 1:6 w l t 'm1', 'upa' u 1:7 w l 'M1',  'upa' u 1:8 w l t 'M1-m1', 'upa' u 1:11 w l t 'm2', 'upa' u 1:12 w l t 'M2', 'upa' u 1:13 w l t 'M2-m2'
		*/

		times++;
		//if M_T is larger than the chosen_gamma, there is a change, restart!
		if(diff > GetGamma(chosen_gamma))
			return 1;
		return 0;

	}

	double getCummDiff(int op){
		return cumm_diff_op[op];
	}

	double getMaxCummDiff(int op){
		return max_cumm_diff_op[op];
	}

protected:
	int times;
	bool restart;
	unsigned n_ops;
	unsigned n_gamma;
	double v_gamma;
	int chosen_gamma;
	double epsilon;
	int * times_gm;
	double * expectation_gm;
	double * multiply_gm;
	int * times_op;
	double * expectation_op;
	double * cumm_diff_op;
	double * max_cumm_diff_op;
};

#endif /* ADAPTIVEPH_H_ */
