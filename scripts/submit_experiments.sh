#$ -S /bin/bash

#problems=(-10 -25 -60 -72 -942)
problems=(-200 -201)
fs=("0.5" "0.6" "0.7" "0.8" "0.9" "1")

for problem in ${problems[@]}; do
	for f in ${fs[@]}; do
		for seed in {1..30}; do
			#metamodels
			qsub run_experiment.sh $problem "KNN" 2 "0-1-2-5" $f $seed
			qsub run_experiment.sh $problem "RNN" "0.001" "0-1-2-5" $f $seed
			qsub run_experiment.sh $problem "LLR" 0 "0-1-2-5" $f $seed
			qsub run_experiment.sh $problem "LLR" 1 "0-1-2-5" $f $seed
			qsub run_experiment.sh $problem "RBF" 1 "0-1-2-5" $f $seed
			#DE variants
			qsub run_experiment.sh $problem "KNN" 2 "0" $f $seed
			qsub run_experiment.sh $problem "KNN" 2 "1" $f $seed
			qsub run_experiment.sh $problem "KNN" 2 "2" $f $seed
			qsub run_experiment.sh $problem "KNN" 2 "5" $f $seed
		done
	done
done

