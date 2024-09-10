# Opt

C/C++ code to metaheuristics and metamodel applications.

Example run command:
./Opt -alg SMDE -eval APM -F 0.5 -s 1 -sm LLR -smp 1 -nap 4 -opDE 0-1-2-5 -f 49 -p 50 -g 200


Example for bilevel version - BLDE with surrogate models 
./Opt -alg BLDE -eval BLDE -F 0.5 -s 1 -sm KNN -smp 3 -nap 5 -opDE 2 -f -10001 -p 20 -g 50 -pF 50 -gF 100 -s -1


for more information use:
./Opt -h

