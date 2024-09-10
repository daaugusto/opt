#$ -S /bin/bash
#$ -q linux.q
#----------------------------------------------------------
# Parameters:
# 1- problem (function)
# 2- metamodel
# 3- smp
# 4- opDE
# 5- seed
#----------------------------------------------------------

fs=("0.5" "0.6" "0.7" "0.8" "0.9" "1")

p=50
g=300

nap=4

if [ $4 == "0-1-2-5" ]; then 
	nap=4
else
	nap=1
fi

for f in ${fs[@]}; do

	../bin/Release/opt -alg SMDE -eval APM -F $f -s $5 -sm $2 -smp $3 -nap $nap -opDE $4 -f $1 -p $p -g $g | bzip2 -9 -c > de_metamodel_apm_${1}_${2}_${3}_${4}_${5}_${nap}_${6}.out.bz2

done
