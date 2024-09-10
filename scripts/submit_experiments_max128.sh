#$ -S /bin/bash

#problems=(-10 -25 -60 -72 -942)
problems=(-200 -201)


for problem in ${problems[@]}; do

	for seed in {1..5}; do
	
		#metamodels
		qsub run_experiment_fs_seed_${seed}.sh $problem "KNN" 2 "0-1-2-5"
		qsub run_experiment_fs_seed_${seed}.sh $problem "RNN" "0.001" "0-1-2-5"
		qsub run_experiment_fs_seed_${seed}.sh $problem "LLR" 0 "0-1-2-5"
		qsub run_experiment_fs_seed_${seed}.sh $problem "LLR" 1 "0-1-2-5"
		qsub run_experiment_fs_seed_${seed}.sh $problem "RBF" 1 "0-1-2-5"
		#DE variants
		qsub run_experiment_fs_seed_${seed}.sh $problem "KNN" 2 "0"
		qsub run_experiment_fs_seed_${seed}.sh $problem "KNN" 2 "1"
		qsub run_experiment_fs_seed_${seed}.sh $problem "KNN" 2 "2"
		qsub run_experiment_fs_seed_${seed}.sh $problem "KNN" 2 "5"
	
	done
		
done

